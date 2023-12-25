//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by liuqian(SkySnow),zhangshuangxue(Calence)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include <stdlib.h>
#include <iostream>
#include "Application.h"
#include "LogAssert.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Renderable.h"
#include "MeshRenderComponent.h"
#include "MeshComponent.h"
#include "StaticMesh.h"
#include "SampleApplication.h"
#include "Context.h"
#include "Texture2D.h"
#include "StbImageLoad.h"
#include "SkySnowEngine.h"
#include "TextureLoader.h"
#include "SPtr.h"
using namespace SkySnow;
using namespace SampleEntry;
class Triangle : public SkySnow::Application
{
public:
	Triangle(const char* name, const char* description, uint32_t width, uint32_t height)
		: Application(name, description, width, height)
        , _Scene(nullptr)
	{
	}
	~Triangle()
	{
	}

	bool Init()
	{
        _Scene = GetSceneManager().CreateScene("Test");

		SPtr<GameObject> go = _Scene->GetRootGo();

        SPtr<TransformComponent> transCom = go->AddComponent<TransformComponent>();
        SPtr<MeshRenderComponent> meshRenderCom = go->AddComponent<MeshRenderComponent>();
        SPtr<MeshComponent>       meshCom = go->AddComponent<MeshComponent>();

        std::string imagePath = GetImageAllPath("panda.png");
        TextureLoader* tImp = new TextureLoader();
        TextureStream* texStream = tImp->Load<TextureStream>(imagePath);
        Texture2D* texture = new Texture2D();
        texture->SetTextureStream(texStream);

        SPtr<Material> mat = CreateSPtr<Material>();
        mat->SetTexture("panda.png",texture);
        mat->CreateShader("QuadVS.sns", "QuadFS.sns");
        
        SPtr<StaticMesh> mesh = CreateSPtr<StaticMesh>();
        mesh->CreateStandardMesh(StandardMeshType::SM_Quad);
        meshCom->SetShareMesh(mesh);

        meshRenderCom->SetMaterialCount(1);
        meshRenderCom->SetMaterial(mat,0);

		return true;
	}
    
    void Update()
    {
        
    }
    
    void ShutDown()
    {
        
    }

private:
    SPtr<Scene> _Scene;
};

SkySnow_SampleApplication(Triangle,"03-Triangles","Draw Trangle At Window&MacOS.", DEFAUT_WADTH, DEFAUT_HEIGHT);
