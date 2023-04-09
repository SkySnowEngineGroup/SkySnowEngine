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
#include "Framework.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
namespace SkySnow
{
    Framework::Framework()
        : _RenderSystem(nullptr)
    {

    }
    Framework::~Framework()
    {
        Delete_Object(_RenderSystem);
    }

    void Framework::WordUpdate()
    {
        if(!_TempTest)
        {
            _RenderSystem = new RenderSystem();
            
            Scene* scene = GetSceneManager().CreateScene("Test");
            TransformComponent* curSceneTrans = new TransformComponent();
            scene->SetRootTransform(curSceneTrans);
            
            GameObject* go = new GameObject();
            CameraComponent* cameraCom = new CameraComponent();
            TransformComponent* goTrans = new TransformComponent();
            RenderComponent* renderCom = new RenderComponent();
            
            go->AddComponent(renderCom);
            go->AddComponent(goTrans);
            go->AddComponent(cameraCom);
            
            scene->AddRootToScene(go);
            _TempTest = true;
        }
        
        _RenderSystem->PreUpdate();
        _RenderSystem->Update();
        _RenderSystem->PostUpdate();
    }
}
