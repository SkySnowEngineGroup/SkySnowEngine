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
        g_SceneHandle ++;
        _ActiveScenes[g_SceneHandle] = scene;
        scene->_SceneHandle = g_SceneHandle;
        scene->_RendererScene = SSContext().GetModule<RenderModule>()->NotifyCreateRendererScene(g_SceneHandle);
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
    SPtr<Scene> SceneManager::GetScene(SceneHandle handle)
    {
        auto iter = _ActiveScenes.find(handle);
        if(iter == _ActiveScenes.end())
        {
            SN_WARN("Not has this index(%d) scene.", handle);
            return  nullptr;
        }
        return _ActiveScenes[handle];
    }
    bool SceneManager::RemoveScene(SceneHandle handle)
    {
        auto iter = _ActiveScenes.find(handle);
        if(iter == _ActiveScenes.end())
        {
            SN_WARN("Not has this index(%d) scene.", handle);
            return false;
        }
        SPtr<Scene> removeScene = _ActiveScenes[handle];
        _DeleteScenes[handle] = removeScene;
        _ActiveScenes.erase(iter);
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
        return true;
    }
    bool SceneManager::ClearRemoveScene()
    {
        for(auto iter = _DeleteScenes.begin(); iter != _DeleteScenes.end(); iter ++)
        {
            SSContext().GetModule<RenderModule>()->NotifyRemoveRendererScene(iter->first);
        }
        _DeleteScenes.clear();
        return true;
    }
    //========================================================================
    SceneManager& GetSceneManager()
    {
        return SceneManager::Instance();
    }

}

