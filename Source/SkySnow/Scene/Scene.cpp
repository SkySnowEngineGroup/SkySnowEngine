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
#include "SkySnowConfigInfo.h"
namespace SkySnow
{
    Scene::Scene(std::string sceneName)
        : _CullingMask(g_DefaultCullingMask)
        , _SceneName(sceneName)
        , _IsSubScene(false)
    {
    }

    Scene::~Scene()
    {
        
    }

    std::string Scene::GetSceneName()
    {
        return _SceneName;
    }

    void Scene::SetRootTransform(TransformComponent* transform)
    {
        _CurrSceneTransform = transform;
    }
    TransformComponent* Scene::GetRootTransform() const
    {
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

    void Scene::AddRootToScene(GameObject* rootGo)
    {
        _RootList.push_back(rootGo);
    }
}

