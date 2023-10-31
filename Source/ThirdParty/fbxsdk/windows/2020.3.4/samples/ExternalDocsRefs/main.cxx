/****************************************************************************************

   Copyright (C) 2022 Autodesk, Inc.
   All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.

****************************************************************************************/

#include <fbxsdk.h>

#include "../Common/Common.h"

/////////////////////////////////////////////////////////////////////////
//
// This example shows how to use sub-documents in the scene that will be 
// saved as separate FBX files that are referenced by the main file.
// 
// Although referencing external FBX files is not too difficult, there are 
// strict rules that must be followed in order to generate files that can be 
// properly read and resolved. For this reason, external references of FBX 
// files is not wildely promoted and most products that support FBX files 
// do not enable this feature by default, therefore, reading such files
// will, most likely, result in incomplete data.
// 
// The FBX SDK will set an error status indicating that external references
// were not resolved. 
//
// This example also shows how to enable the FbxExternalDocRefListener to 
// resolve these documents when reading the file. There is no penality in 
// always binding the listener to the main scene since an event is only 
// emitted if referenced files are detected. Alternatively, if the listener
// is not binded, the reading of the file will result in unresolved objects.
//
// The example illustrates how to:
//        1) create sub-documents
//        3) create materials in a sub-document
//        4) create a plane in the main scene and one in a sub-document
//        5) reference materials from the sub-document
//        6) export the sub documents as .FBX files (ASCII mode)
//        7) export the main scene in a .FBX file (ASCII mode)
//
/////////////////////////////////////////////////////////////////////////

// reference cloning from the FbxObject (enabling OBJ_CLONE) will not clone all the connections so
// it must be used only when we know it is safe to ignore extra connected object(s) or explicit code
// is written to manually walk the connection and clone the attached objects.
// 
// If you enable OBJ_CLONE, the materials created by this sample will skip assigning a texture
// file to the diffuse property. If it was left in the code, the clone would 'fail' to maintain
// this connection
// 
//#define OBJ_CLONE 1

// Create a plane mesh. 
FbxNode* CreatePlane(FbxDocument* pDocument, const char* pName)
{
    int i;
    FbxMesh* lMesh = FbxMesh::Create(pDocument, pName);
    FbxVector4 lNormalYPos(0, 1, 0);

    // Create control points.
    lMesh->InitControlPoints(9);
    FbxVector4* lControlPoints = lMesh->GetControlPoints();

    lControlPoints[0] = FbxVector4(-50, 0, -50);
    lControlPoints[1] = FbxVector4(0, 0, -50);
    lControlPoints[2] = FbxVector4(50, 0, -50);
    lControlPoints[3] = FbxVector4(-50, 0, 0);
    lControlPoints[4] = FbxVector4(0, 0, 0);
    lControlPoints[5] = FbxVector4(50, 0, 0);
    lControlPoints[6] = FbxVector4(-50, 0, 50);
    lControlPoints[7] = FbxVector4(0, 0, 50);
    lControlPoints[8] = FbxVector4(50, 0, 50);

    // We want to have one normal for each vertex (or control point),
    // so we set the mapping mode to eByControlPoint.
    FbxGeometryElementNormal* lElementNormal = lMesh->CreateElementNormal();
    lElementNormal->SetMappingMode(FbxGeometryElement::eByControlPoint);
    lElementNormal->SetReferenceMode(FbxGeometryElement::eDirect);
    for (int i = 0; i < lMesh->GetControlPointsCount(); i++)
    {
        lElementNormal->GetDirectArray().Add(lNormalYPos);
    }

    // Array of polygon vertices.
    int lPolygonVertices[4][4] = { { 0, 3, 4, 1}, {1, 4, 5, 2}, {3, 6, 7, 4}, {4, 7, 8, 5} };

    // Create UV for Diffuse channel.
    FbxGeometryElementUV* lUVDiffuseElement = lMesh->CreateElementUV("DiffuseUV");
    FBX_ASSERT(lUVDiffuseElement != NULL);
    lUVDiffuseElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
    lUVDiffuseElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);
    for (int i = 0; i < lMesh->GetControlPointsCount(); i++)
    {
        FbxVector2 v((50 + lControlPoints[i][0]) / 100.0, (50 + lControlPoints[i][2])/100.0);
        lUVDiffuseElement->GetDirectArray().Add(v);
    }

    //Now we have set the UVs as eIndexToDirect reference and in eByPolygonVertex  mapping mode
    //we must update the size of the index array.
    lUVDiffuseElement->GetIndexArray().SetCount(16);

    // Create polygons. Assign texture and texture UV indices.
    int id = 0;
    for (i = 0; i < 4; i++)
    {
        lMesh->BeginPolygon(-1, -1, -1, false);
        for (int j = 0; j < 4; j++)
        {
            // Control point index
            lMesh->AddPolygon(lPolygonVertices[i][j]);

            // update the index array of the UVs that map the texture to the face
            lUVDiffuseElement->GetIndexArray().SetAt(id++, lPolygonVertices[i][j]);
        }
        lMesh->EndPolygon();
    }

    // create a FbxNode
    FbxNode* lNode = FbxNode::Create(pDocument, pName);

    // set the node attribute
    lNode->SetNodeAttribute(lMesh);

    // set the shading mode to view texture
    lNode->SetShadingMode(FbxNode::eTextureShading);

    // Set material mapping.
    FbxGeometryElementMaterial* lMaterialElement = lMesh->CreateElementMaterial();
    lMaterialElement->SetMappingMode(FbxGeometryElement::eByPolygon);
    lMaterialElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);
    if (!lMesh->GetElementMaterial(0))
        return NULL;

    // 4 polygons -> 4 materials
    lMaterialElement->GetIndexArray().SetCount(lMesh->GetPolygonCount());
    for (i = 0; i < lMesh->GetPolygonCount(); ++i)
        lMaterialElement->GetIndexArray().SetAt(i, i);

    return lNode;
}

// Create a document containing 'nbMaterials' simple phong materials that will, later be assigned to the planes faces
FbxDocument* CreateMatDocument(FbxString pFolder, FbxManager* pManager, const char* documentName, int nbMaterials)
{
    FbxScene* lMatDocument = FbxScene::Create(pManager, documentName);

    // create document info
    FbxDocumentInfo* lDocInfo = FbxDocumentInfo::Create(pManager, "DocInfo");
    lDocInfo->mTitle = "Sub document for materials";
    lDocInfo->mSubject = "Illustrates the creation of sub-FbxDocument with materials.";
    lDocInfo->mAuthor = "FBX SDK";

    // add the documentInfo
    lMatDocument->SetDocumentInfo(lDocInfo);

    // this document just contains materials
    FbxString lShadingName = "Phong";
    FbxString lMaterialName;

    float _R[8] = { 1,1,1,1,0,0,0,0 };
    float _G[8] = { 0,0,1,1,1,0,1,0 };
    float _B[8] = { 0,1,0,1,0,1,1,0 };
    int i;

    for (i = 0; i < nbMaterials && nbMaterials <= 8; i++)
    {
        double r = _R[i];
        double g = _G[i];
        double b = _B[i];
        
        lMaterialName = FbxString("Mat") + i;
        FbxSurfacePhong* lMaterial = FbxSurfacePhong::Create(pManager, lMaterialName.Buffer());
        lMatDocument->AddMember(lMaterial);

        lMaterial->Diffuse.Set(FbxDouble3(r, g, b));
        lMaterial->DiffuseFactor.Set(1.);
#ifndef OBJ_CLONE
        FbxString file = FbxPathUtils::Bind(pFolder.Buffer(), "a_texture.jpg");
        if (i != nbMaterials)
        {
            FbxFileTexture* lTexture = FbxFileTexture::Create(pManager, "texture");
            lMatDocument->AddMember(lTexture);

            // Set texture properties.
            if (!FbxFileUtils::Exist(file.Buffer()))
                FBXSDK_printf("WARNING: texture file '%s' cannot be located.\n", file.Buffer());

            lTexture->SetFileName(file.Buffer()); // Resource file is in current directory.
            lTexture->SetTextureUse(FbxTexture::eStandard);
            lTexture->SetMappingType(FbxTexture::eUV);
            lTexture->SetMaterialUse(FbxFileTexture::eModelMaterial);
            lTexture->UVSet.Set("DiffuseUV");

            // we connect the texture to the material DiffuseColor property
            lMaterial->Diffuse.ConnectSrcObject(lTexture);
        }
#endif
    }

    // make sure we connect the corresponding videos used by the Textures
    if (lMatDocument)
        lMatDocument->ConnectVideos();

    return lMatDocument;
}

// Reference the materials defined in 'pFromDoc'
void AddMaterials(FbxNode* pNode, FbxDocument* pFromDoc, int start, int end, FbxCloneManager& pCloneManager, FbxCloneManager::CloneSetElement& pOptions, FbxDocument* pDestDoc)
{
    if (pOptions.mType != FbxObject::eReferenceClone || pCloneManager.sMaximumCloneDepth == -1)
        FBXSDK_printf("WARNING: requested a cloning operation that is not ReferenceClone\n");

    if (pFromDoc)
    {
#ifdef OBJ_CLONE
        // this method of reference cloning is still viable if we know for sure that
        // there are no connections to follow. Otherwise, we must use the CloneManager.
        for (int j = start; j < end; j++)
        {
            FbxSurfaceMaterial* lMat = pFromDoc->GetSrcObject<FbxSurfaceMaterial>(j);
            if (lMat)
            {
                FbxSurfaceMaterial* lClonedMat = FbxCast<FbxSurfaceMaterial>(lMat->Clone(FbxObject::eReferenceClone, pDestDoc));
                if (lClonedMat) pNode->AddMaterial(lClonedMat);
            }
        }
#else
        FbxCloneManager::CloneSet cloneSet;
        // reference clone the materials from the lMatDocument to the main scene.
        // Objects defined in sub-documents also need to exist in the main scene in order
        // to have the references correctly written to the file. We can achieve this
        // by reference cloning them to limit the memory footprint.
        for (int j = start; j < end; j++)
        {
            FbxSurfaceMaterial* lMat = pFromDoc->GetSrcObject<FbxSurfaceMaterial>(j);
            if (lMat)
            {
                cloneSet.Insert((FbxObject*)lMat, pOptions);
                pCloneManager.AddDependents(cloneSet, lMat, pOptions, FbxCriteria::ObjectType(FbxObject::ClassId));
            }
        }
        // because materials can have dependencies (textures), we use the FbxCloneManager to
        // clone them so we can properly follow the connections (FbxObject::Clone() does not).
        // The clones will be attached to the 'pDestDoc' document.
        if (pCloneManager.Clone(cloneSet, pDestDoc))
        {
            // access the clones
            FbxCloneManager::CloneSet::RecordType* lIterator = cloneSet.Minimum();
            while (lIterator)
            {
                FbxObject* lClonedObject = lIterator->GetValue().mObjectClone;
                FbxSurfaceMaterial* lClonedMat = FbxCast<FbxSurfaceMaterial>(lClonedObject);

                // attach the 'cloned' material to the incoming node (pNode must also be attached to 'pDestDoc')
                if (lClonedMat) pNode->AddMaterial(lClonedMat);
                lIterator = lIterator->Successor();
            }
        }
#endif
    }
}

// Write everything belonging to 'pDoc' to the external FBX file located in 'pFolder'
// Note that in the case EXP_FBX_COLLAPSE_EXTERNALS is set to True, all the sub-documents
// are automatically 'collapsed' into the main scene ('pScene') therefore, no need to write
// externa files.
bool WriteToExternalFile(FbxString& pFolder, const FbxString& pSuffix, FbxDocument* pDoc, FbxManager* pSdkManager, FbxScene* pScene)
{
    bool lResult = true;

    // save the sub-document to a separate file
    FbxString name = pDoc->GetName();
    FbxString fullName = name + pSuffix + ".fbx";
    FbxString fileName = FbxPathUtils::Bind(pFolder.Buffer(), fullName.Buffer());

    // Only write pDoc to an external file if we don't ask to collapse it in the main scene
    if (!(*(pSdkManager->GetIOSettings())).GetBoolProp(EXP_FBX_COLLAPSE_EXTERNALS, true))
    {
        int lFormat = pSdkManager->GetIOPluginRegistry()->FindWriterIDByDescription("FBX ascii (*.fbx)");
        lResult = SaveScene(pSdkManager, pDoc, fileName.Buffer(), lFormat);
    }

    // make sure we define the Url in the docInfo otherwise the files cannot be correctly referenced
    FbxDocumentInfo* lDocInfo = pDoc->GetDocumentInfo();
    if (lDocInfo) lDocInfo->SetUrl(fileName.Buffer());

    // Mandatory step: create a reference to the file in the main scene
    FbxSceneReference* ref = FbxSceneReference::Create(pScene, name.Buffer());
    ref->ReferenceFilePath = fileName;
    ref->ReferenceNodeName = name.Buffer();
    ref->IsLoaded = false;
    return lResult;
}

// utility function to print out the current objects to the console to see
// how the scene is constructed
void printObj(FbxObject* pObj, int indent)
{
    #define INDENT() for (int i = 0; i < indent; i++) FBXSDK_printf(" ");
    FbxObject* referencing = pObj->GetReferenceTo();

    if (referencing)
    {
        FbxString refName;
        FbxDocument* doc = referencing->GetDstObject<FbxDocument>();
        if (doc) {
            refName = doc->GetName();
            refName += ":";
        }
        refName += referencing->GetName();
        INDENT();
        FBXSDK_printf("%s is RefClone of %s [%s]\n", pObj->GetName(), refName.Buffer(), pObj->GetClassId().GetName());
    }
    else 
    {
        INDENT();
        FBXSDK_printf("%s [%s]\n", pObj->GetName(), pObj->GetClassId().GetName());
    }

    FbxProperty p = pObj->GetFirstProperty();
    while (p.IsValid())
    {
        for (int i = 0; i < p.GetSrcObjectCount(); i++)
        {
            FbxObject* o = p.GetSrcObject(i);
            printObj(o, indent + 3);
        }
        p = pObj->GetNextProperty(p);
    }
    for (int i = 0; i < pObj->GetSrcObjectCount(); i++)
    {
        FbxObject* obj = pObj->GetSrcObject(i);
        printObj(obj, indent + 3);
    }
}

void printScene(FbxScene* pScene)
{
    FBXSDK_printf("\n===========\n");
    FBXSDK_printf("nb objects on scene (%s)=%d\n", pScene->GetName(), pScene->GetSrcObjectCount());
    printObj(pScene->GetRootNode(), 0);
}

//===================================================================================================
//
int main(int argc, char** argv)
{    
    FbxManager* lSdkManager = NULL;
    FbxScene* lScene = NULL;
    bool lResult = true;

    // Prepare the FBX SDK.
	//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
	lSdkManager = FbxManager::Create();
	if (!lSdkManager)
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);

	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	lScene = FbxScene::Create(lSdkManager, "MainScene");
	if (!lScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		exit(1);
	}

    // parse arguments
    bool lCreate = false;
    FbxString lFilePath("");
	for( int i = 1, c = argc; i < c; ++i )
	{
        if (strcmp(argv[i], "-create") == 0) lCreate = true;
        else if (lFilePath.IsEmpty()) lFilePath = argv[i];
	}

    if (lCreate == false && !lFilePath.IsEmpty())
    {   
        // To properly read externally referenced FBX files, we must bind the FbxExternalDocRefListener
        // to the main scene. Failing to do so, the main file will still be read, but without the references
        // so the objects would not be properly resolved and have default values.
        FbxExternalDocRefListener lRefDocListener(*lSdkManager, lFilePath);
        FbxEventHandler* lHandler = lRefDocListener.Bind(*lScene, &FbxExternalDocRefListener::HandleEvent);

        // load the main file (and implicitly the externally referenced ones!)
        lResult = LoadScene(lSdkManager, lScene, lFilePath.Buffer());

        // we don't nee the listener anymore (the lHandler pointer is deleted when lRefDocListener goes
        // out of scope)
        if (lHandler) lRefDocListener.Unbind(lHandler);

        if (lResult)
            printScene(lScene);
    }
    else
    {
        // First, let's get the folder so we can write the extra files in the same
        // directory as the main one.
        FbxString folder = FbxPathUtils::GetFolderName(lFilePath.Buffer());
        FbxArray<FbxDocument*> subDocuments;

        // We are using the FbxCloneManager to clone (by reference) the desired objects from their sub-document
        // into the main scene. We should not use the FbxObject::Clone() because the connections are 
        // not cloned by it.
        FbxCloneManager lCloneManager;
        FbxCloneManager::CloneSetElement defaultCloneOptions(
            FbxCloneManager::sConnectToClone,
            FbxCloneManager::sConnectToOriginal,
            FbxObject::eReferenceClone);

        // Create all the materials in the sub-document named 'Materials'.
        // These materials are going to be used by the two planes. Each plane have 4 polys so
        // 8 materials in total are created (the first 4 are going to be applied to the first plane,
        // the next 4 to the second plane)
        int matPerPoly = 4;
        int totNbMaterials = matPerPoly * 2;
        FbxDocument* lMatDocument = CreateMatDocument(folder, lSdkManager, "Materials", totNbMaterials);
        subDocuments.Add(lMatDocument);

        // ------------------------------------------------------
        // Create the first plane directly in the main scene
        FbxNode* lPlane = CreatePlane(lScene, "plane_master");
        lScene->GetRootNode()->AddChild(lPlane);
        lPlane->LclTranslation.Set(FbxVector4(-70, 0, 0));

        // attach ref cloned materials from lMatDocument to lPlane
        AddMaterials(lPlane, lMatDocument, 0, matPerPoly, lCloneManager, defaultCloneOptions, lScene);

        // ------------------------------------------------------
        // Create a second plane in its own sub-document ('geomSubDoc')
        FbxNode* lSubDocPlane = nullptr;
        FbxScene* lSubScene = FbxScene::Create(lSdkManager, "geomSubDoc");
        if (lSubScene)
        {
            // create document info
            FbxDocumentInfo* lDocInfo = FbxDocumentInfo::Create(lSdkManager, "DocInfo");
            lDocInfo->mTitle = "Sub document for geometries";
            lDocInfo->mSubject = "Illustrates the creation of sub-FbxDocument with geometries.";
            lDocInfo->mAuthor = "FBX SDK";

            // add the documentInfo
            lSubScene->SetDocumentInfo(lDocInfo);
            subDocuments.Add(lSubScene);

            lSubDocPlane = CreatePlane(lSubScene, "plane_subdoc");
            lSubScene->GetRootNode()->AddChild(lSubDocPlane);
            lSubDocPlane->LclTranslation.Set(FbxVector4(70, 0, 0));

            // attach ref cloned materials from lMatDocument to lSubDocPlane. The ref cloned materials are inside geomSubDoc
            AddMaterials(lSubDocPlane, lMatDocument, matPerPoly, totNbMaterials, lCloneManager, defaultCloneOptions, lSubScene);
        }

        // ------------------------------------------------------
        // Now, Ref clone the lSubDocPlane (and all its dependencies - this includes the materials) from geomSubDoc 
        // into the main scene.
        if (lSubDocPlane)
        {
#ifdef OBJ_CLONE
            FbxNode* pNode = FbxCast<FbxNode>(lSubDocPlane->Clone(FbxObject::eReferenceClone, lScene));

            // lSubDocPlane have a connection to its NodeAttribute (the mesh definition), so we need to clone it as well
            FbxNodeAttribute* nAttr = FbxCast<FbxNodeAttribute>(lSubDocPlane->GetNodeAttribute()->Clone(FbxObject::eReferenceClone, lScene));
            pNode->SetNodeAttribute(nAttr);

            // same thing for the materials
            for (int j = 0; j < lSubDocPlane->GetMaterialCount(); j++)
            {
                FbxSurfaceMaterial* lMat = lSubDocPlane->GetMaterial(j);
                FbxSurfaceMaterial* lClonedMat = FbxCast<FbxSurfaceMaterial>(lMat->Clone(FbxObject::eReferenceClone, lScene));
                if (lClonedMat) pNode->AddMaterial(lClonedMat);
            }

            // finally, make sure the new cloned node is a child of the scene so it can be propery written to the file.
            lScene->GetRootNode()->AddChild(pNode);
#else
            FbxCloneManager::CloneSet cloneSet;
            cloneSet.Insert((FbxObject*)lSubDocPlane, defaultCloneOptions);
            lCloneManager.AddDependents(cloneSet, lSubDocPlane, defaultCloneOptions, FbxCriteria::ObjectType(FbxObject::ClassId));
            if (lCloneManager.Clone(cloneSet, lScene))
            {
                // access the clones
                FbxCloneManager::CloneSet::RecordType* lIterator = cloneSet.Minimum();
                while (lIterator)
                {
                    FbxObject* lClonedObject = lIterator->GetValue().mObjectClone;
                    FbxNode* lClonedNode = FbxCast<FbxNode>(lClonedObject);
                    if (lClonedNode) lScene->GetRootNode()->AddChild(lClonedNode);
                    lIterator = lIterator->Successor();
                }
            }
#endif
        }

        // save the sub documents into external FBX files. The EXP_FBX_COLLAPSE_EXTERNALS
        // must be set to 'false'
        (*(lSdkManager->GetIOSettings())).SetBoolProp(EXP_FBX_COLLAPSE_EXTERNALS, false);

        // Extract the suffix from the lFilePath so we can use it suffix the sub-documents files
        FbxString lSuffix("");
        FbxString lFileName = FbxPathUtils::GetFileName(lFilePath.Buffer());
        int suffPos = lFileName.Find("_");
        if (suffPos > 0)
        {
            int dot = lFileName.Find(".");
            lSuffix = lFileName.Mid(suffPos, dot - suffPos);
        }

        for (int i = 0; i < subDocuments.GetCount(); i++)
        {
            lResult &= WriteToExternalFile(folder, lSuffix, subDocuments[i], lSdkManager, lScene);
        }

        // and, finally, save the main scene
        if (lResult && !lFilePath.IsEmpty())
        {
            lResult = SaveScene(lSdkManager, lScene, lFilePath.Buffer(), 1);
        }

        printScene(lScene);
    }

    // Destroy all objects created by the FBX SDK.
    DestroySdkObjects(lSdkManager, lResult);
    return 0;
}



