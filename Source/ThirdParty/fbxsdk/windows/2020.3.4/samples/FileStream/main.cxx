/****************************************************************************************

   Copyright (C) 2015 Autodesk, Inc.
   All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.

****************************************************************************************/

/////////////////////////////////////////////////////////////////////////
//
//
// The example illustrates how to:
//        1) create a file custom stream class
//        2) write a text file using the stream
//        3) read the generated file via the stream
//
/////////////////////////////////////////////////////////////////////////

#include <fbxsdk.h>

// Custom stream
//
// IMPORTANT: This stream class will manipulate the stream with the standard fopen/fseek functions
// even thought the offsets and the pSize parameter of the Read and Write functions are defined 
// with FbxInt64. If you want to handle large file, you will need to change the fopen and fseek 
// calls with the appropriate 64 bits version and handle the large buffers in the Write/Read
// functions.
//
class CustomStreamClass : public FbxStream
{
public:
	CustomStreamClass( FbxManager* pSdkManager, const char* mode )
	{
		mFile = NULL;

		// expect the mode to contain something
		if (mode == NULL) return;


		FBXSDK_strcpy(mFileName, 30, "CustomStreamClass_temp.txt");
		FBXSDK_strcpy(mMode, 3, (mode) ? mode : "r");

		if ( mode[0] == 'r' )
		{
			const char* format = "FBX (*.fbx)";
			mReaderID = pSdkManager->GetIOPluginRegistry()->FindReaderIDByDescription( format );
			mWriterID = -1;
		}
		else
		{
			const char* format = "FBX ascii (*.fbx)";
			mWriterID = pSdkManager->GetIOPluginRegistry()->FindWriterIDByDescription( format );
			mReaderID = -1;
		}
	}

	~CustomStreamClass()
	{
		Close();
	}

	EState GetState() override
	{
		return mFile ? FbxStream::eOpen : eClosed;
	}

	/** Open the stream.
	  * \return True if successful.
	  */
	bool Open( void* /*pStreamData*/ ) override
	{
		// This method can be called several times during the
		// Initialize phase so it is important that it can handle 
		// multiple opens
		if (mFile == NULL)
			FBXSDK_fopen(mFile, mFileName, mMode);

		if (mFile != NULL)
            Seek( 0L, FbxFile::eBegin);

		return ( mFile != NULL );
	}

	/** Close the stream.
	  * \return True if successful.
	  */
	bool Close() override
	{
		// This method can be called several times during the
		// Initialize phase so it is important that it can handle multiple closes
		if ( mFile )
			fclose( mFile );
		mFile = NULL;
		return true;
	}

	/** Empties the internal data of the stream.
	  * \return True if successful.
	  */
	bool Flush() override
	{
		return true;
	}

	/** Writes a memory block.
	  * \param pData Pointer to the memory block to write.
	  * \param pSize Size (in bytes) of the memory block to write.
	  * \return The number of bytes written in the stream.
	  */
	size_t Write(const void* pData, FbxUInt64 pSize) override
	{
		if ( mFile == NULL )
			return 0;
#ifdef FBXSDK_CPU_32
        FBX_ASSERT_RETURN_VALUE(pSize < FBXSDK_UINT_MAX, 0);
#endif
		return fwrite( pData, 1, (size_t)pSize, mFile );
	}

	/** Read bytes from the stream and store them in the memory block.
	  * \param pData Pointer to the memory block where the read bytes are stored.
	  * \param pSize Number of bytes read from the stream.
	  * \return The actual number of bytes successfully read from the stream.
	  */
    size_t Read (void* pData, FbxUInt64 pSize) const override
	{
		if ( mFile == NULL )
			return 0;
#ifdef FBXSDK_CPU_32
        FBX_ASSERT_RETURN_VALUE(pSize < FBXSDK_UINT_MAX, 0);
#endif
		return fread( pData, 1, (size_t)pSize, mFile );
	}

	int GetReaderID() const override
	{
		return mReaderID;
	}

	int GetWriterID() const override
	{
		return mWriterID;
	}

    void Seek(const FbxInt64& pOffset, const FbxFile::ESeekPos& pSeekPos)  override
    {
        // make sure pOffset does not overflow the int
        FBX_ASSERT_RETURN(pOffset < FBXSDK_INT_MAX && pOffset > -FBXSDK_INT_MAX);
            
        int offset = (int)pOffset;
        switch (pSeekPos)
        {
        case FbxFile::eBegin:
            fseek(mFile, offset, SEEK_SET);
            break;
        case FbxFile::eCurrent:
            fseek(mFile, offset, SEEK_CUR);
            break;
        case FbxFile::eEnd:
            fseek(mFile, offset, SEEK_END);
            break;
        }
    }

	FbxInt64 GetPosition() const override
	{
        if (mFile == NULL)
            return 0;

        return (FbxInt64)ftell(mFile);
	}

	void SetPosition( FbxInt64 pPosition ) override
	{
        if (mFile)
           Seek(pPosition, FbxFile::eBegin);
	}

	int GetError() const override
	{
		if ( mFile == NULL )
			return 0;
		return ferror( mFile );
	}
	void ClearError() override
	{
		if ( mFile != NULL )
			clearerr( mFile );
	}

private:
	FILE*	mFile;
	int		mReaderID;
	int		mWriterID;
	char    mFileName[30];
	char    mMode[3];
};



int testExport()
{
	// create a SdkManager
	FbxManager* lSdkManager = FbxManager::Create();
	// create an IOSettings object
	FbxIOSettings* ios = FbxIOSettings::Create( lSdkManager, IOSROOT );
	// create an empty scene.
	FbxScene* lScene = FbxScene::Create( lSdkManager, "" );
	// create an exporter.
	FbxExporter* lExporter = FbxExporter::Create( lSdkManager, "" );
	// create a stream.
	CustomStreamClass stream( lSdkManager, "wb" );
	// can pass in a void* data pointer to be passed to the stream on FileCreate
	void* streamData = NULL;
	// initialize the exporter.
	if ( !lExporter->Initialize( &stream, streamData, -1, ios ) )
		return -1;
	// export the scene.
	if ( !lExporter->Export( lScene ) )
		return -1;
	// destroy the exporter.
	lExporter->Destroy();

	return 0;
}

int testImport()
{
	// create a SdkManager
	FbxManager* lSdkManager = FbxManager::Create();
	// create an IOSettings object
	FbxIOSettings* ios = FbxIOSettings::Create( lSdkManager, IOSROOT );
	// create an empty scene
	FbxScene* lScene = FbxScene::Create( lSdkManager, "" );
	// create an importer.
	FbxImporter* lImporter = FbxImporter::Create( lSdkManager, "" );
	// create a stream. (CustomStreamClass – stream initialization in constructor)
	CustomStreamClass stream( lSdkManager, "rb" );
	// can pass in a void* data pointer to be passed to the stream on FileOpen
	void* streamData = NULL;
	// initialize the importer with a stream
	if ( !lImporter->Initialize( &stream, streamData, -1, ios ) )
		return -1;
	// import the scene.
	if ( !lImporter->Import( lScene ) )
		return -1;
	// destroy the importer.
	lImporter->Destroy();

	return 0;
}

int main(int /*argc*/, char** /*argv*/)
{
	int ret;

	ret = testExport();
	if ( ret ) return ret;
	
	ret = testImport();
	if ( ret ) return ret;

	return 0;
}

