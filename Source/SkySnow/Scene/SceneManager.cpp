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
#include "SceneManager.h"
#include "LogAssert.h"
#include "Context.h"
#include "RenderModule.h"
#include "Scene.h"
#include "GameObject.h"

namespace SkySnow
{
    SceneManager::SceneManager()
    {
    }
    SceneManager::~SceneManager()
    {
    }
    SceneManager& SceneManager::Instance()
    {
        static SceneManager instance;
        return instance;
    }

    SPtr<Scene> SceneManager::CreateScene(std::string name)
    {
        SPtr<Scene> scene = CreateSPtr<Scene>(name);
        _ActiveScenes[scene->GetUUID()] = scene;
        scene->_RendererScene = SSContext().GetModule<RenderModule>()->NotifyCreateRendererScene(scene->GetUUID());
        return scene;
    }

    SPtr<Scene> SceneManager::GetScene(std::string name)
    {
        for(auto iter = _ActiveScenes.begin(); iter != _ActiveScenes.end(); iter ++)
        {
            if(iter->second->GetSceneName() == name)
            {
                return iter->second;
            }
        }
        SN_WARN("Not Find This %s Scene.",name.c_str());
        return nullptr;
    }
    void SceneManager::GetScenes(std::vector<SPtr<Scene>>& sceneList)
    {
        for(auto iter = _ActiveScenes.begin(); iter != _ActiveScenes.end(); iter ++)
        {
            sceneList.push_back(iter->second);
        }
    }
    SPtr<Scene> SceneManager::GetScene(const UUID& uuid)
    {
        auto iter = _ActiveScenes.find(uuid);
        if(iter == _ActiveScenes.end())
        {
            SN_WARN("Not has this index(%d) scene.", (uint64_t)uuid);
            return  nullptr;
        }
        return _ActiveScenes[uuid];
    }
    bool SceneManager::RemoveScene(const UUID& uuid)
    {
        auto iter = _ActiveScenes.find(uuid);
        if(iter == _ActiveScenes.end())
        {
            SN_WARN("Not has this index(%d) scene.", (uint64_t)uuid);
            return false;
        }
        SPtr<Scene> removeScene = _ActiveScenes[uuid];
        _DeleteScenes[uuid] = removeScene;
        _ActiveScenes.erase(iter);
        SSContext().GetModule<RenderModule>()->NotifyRemoveRendererScene(removeScene->GetUUID());
        return true;
    }
    bool SceneManager::RemoveScene(std::string name)
    {
        int index = -1;
        for(auto iter = _ActiveScenes.begin(); iter != _ActiveScenes.end(); iter ++)
        {
            if(iter->second->GetSceneName() == name)
            {
                index = iter->first;
            }
        }
        if(index < 0)
        {
            SN_WARN("Not Find This %s Scene.",name.c_str());
            return false;
        }
        SPtr<Scene> removeScene = _ActiveScenes[index];
        _DeleteScenes[index] = removeScene;
        _ActiveScenes.erase(_ActiveScenes.find(index));
        SSContext().GetModule<RenderModule>()->NotifyRemoveRendererScene(removeScene->GetUUID());
        return true;
    }
    
    void SceneManager::ClearScene()
    {
        for(auto iter = _ActiveScenes.begin(); iter != _ActiveScenes.end(); iter ++)
        {
            SSContext().GetModule<RenderModule>()->NotifyRemoveRendererScene(iter->second->GetUUID());
        }
        _ActiveScenes.clear();
        _DeleteScenes.clear();
    }
    //========================================================================
    SceneManager& GetSceneManager()
    {
        return SceneManager::Instance();
    }
}

