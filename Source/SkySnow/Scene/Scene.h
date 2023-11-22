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
#include "Object.h"
#include "SkySnowProfiles.h"
#include "TransformComponent.h"
#include <vector>
namespace SkySnow
{
    class GameObject;
    class Scene : public Object
    {
        SkySnow_Object(Scene,Object);
    public:
        Scene(std::string sceneName = "");
        ~Scene();
        
        std::string GetSceneName() const;
        //setup subscene flag
        void SetSubScene(bool subScene);
        //get subscene flag
        bool IsSubScene() const;
        //Scene culling mask(camera cal visable and novisable)
        void SetSceneCullingMask(uint64_t cullingMask);
        //Get Scene
        uint64_t GetSceneCullingMask() const;
        //SetUp curr scene root gameobject
        SPtr<GameObject> AddRootGo();
        //Get Root GameObject
        SPtr<GameObject> GetRootGo();
    private:
        bool                        _IsSubScene;
        SkySnowSceneHandle          _SceneHandle;
        uint64_t                    _CullingMask;
        std::string                 _SceneName;
        SPtr<GameObject>            _RootGo;
    };
}
