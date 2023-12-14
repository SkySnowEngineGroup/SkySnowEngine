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
#pragma once
#include "NonCopyable.h"
#include <map>
#include "Scene.h"
#include "SPtr.h"
namespace SkySnow
{
    //SkySnow use HybridECS framework
    class SceneManager : public NonCopyable
    {
    public:
        static SceneManager& Instance();
        
        SPtr<Scene> CreateScene(std::string name = "");
        //Get all scene list
        void GetScenes(std::vector<SPtr<Scene>>& sceneList);
        //Get Taget SceneName Scene
        SPtr<Scene> GetScene(std::string name);
        //Get Target SceneIndex Scene
        SPtr<Scene> GetScene(SceneHandle handle);
        bool RemoveScene(SceneHandle handle);
        bool RemoveScene(std::string name);
        bool ClearRemoveScene();
    private:
        SceneManager();
        ~SceneManager();
    private:
        std::map<int, SPtr<Scene>> _ActiveScenes;
        std::map<int, SPtr<Scene>> _DeleteScenes;
    };

    SceneManager& GetSceneManager();
}

