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
#include "Scene.h"
#include "GameObject.h"
#include "SkySnowConfigInfo.h"
namespace SkySnow
{
    Scene::Scene(std::string sceneName)
        : _Enable(true)
        , _IsSubScene(false)
        , _SceneHandle(-1)
        , _SceneRootGO(nullptr)
        , _CullingMask(g_DefaultCullingMask)
        , _SceneName(sceneName)
        , _CurrSceneTransform(nullptr)
    {
    }

    Scene::~Scene()
    {
        for(auto entry:_RootList)
        {
            delete entry;
        }
        _RootList.clear();
        Delete_Object(_CurrSceneTransform);
        Delete_Object(_SceneRootGO);
    }

    std::string Scene::GetSceneName() const
    {
        return _SceneName;
    }

    void Scene::SetEnable(bool enable)
    {
        _Enable = enable;
        for(auto iter = _RootList.begin(); iter != _RootList.end(); iter ++)
        {
            (*iter)->SetEnable(enable);
        }
        if (_SceneRootGO)
        {
            _SceneRootGO->SetEnable(enable);
        }
    }

    bool Scene::IsEnable() const
    {
        return _Enable;
    }

    TransformComponent* Scene::SetupRootTransform()
    {
        if(!_CurrSceneTransform)
        {
            _CurrSceneTransform = new TransformComponent();
        }
        return _CurrSceneTransform;
    }
    TransformComponent* Scene::GetRootTransform()
    {
        if(!_CurrSceneTransform)
        {
            _CurrSceneTransform = SetupRootTransform();
        }
        return _CurrSceneTransform;
    }
    
    void Scene::SetSubScene(bool subScene)
    {
        _IsSubScene = subScene;
    }
    
    bool Scene::IsSubScene()const
    {
        return _IsSubScene;
    }
    
    void Scene::SetSceneCullingMask(uint64_t cullingMask)
    {
        _CullingMask = cullingMask;
    }

    uint64_t Scene::GetSceneCullingMask() const
    {
        return _CullingMask;
    }
    GameObject* Scene::AddRootToScene(GameObject* goRoot)
    {
        if (goRoot)
        {
            _IsSubScene = true;
            if(_SceneRootGO)
            {
                Delete_Object(_SceneRootGO);
            }
            else
            {
                _SceneRootGO = goRoot;
            }
               
        }
        if(!_SceneRootGO)
        {
            _SceneRootGO = new GameObject();
        }
        return _SceneRootGO;
    }
    GameObject* Scene::AddChildGOToScene()
    {
        GameObject* childGo = new GameObject();
        _RootList.push_back(childGo);
        return childGo;
    }
}

