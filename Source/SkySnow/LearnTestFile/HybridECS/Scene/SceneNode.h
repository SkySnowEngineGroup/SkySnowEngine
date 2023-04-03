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
#include <vector>
#include "TComponent.h"
using namespace SkySnow;
namespace SkySnowLearning
{
    //SceneNode is ECS of the ECS System
    //GameObject in u3d, actor in ue
    class SceneNode : public Object
    {
        SkySnow_Object(SceneNode,Object);
    public:
        SceneNode();
        ~SceneNode();
        template<typename T> T* GetComponent();
        
        template<typename T> bool HasComponent();
        
        void AddComponent(Component* component);
    private:
        std::vector<Component*> _ComponentList;
    };
    //========================================================================================
    template<typename T> inline T* SceneNode::GetComponent()
    {
        for(int i = 0; i < _ComponentList.size(); i ++)
        {
            if(T::GetTypeNameStatic() == _ComponentList[i]->GetTypeName())
            {
                Component* com = _ComponentList[i];
                return dynamic_cast<T*>(com);
            }
        }
        return nullptr;
    }
    //========================================================================================
    template<typename T> inline bool SceneNode::HasComponent()
    {
        for(int i = 0; i < _ComponentList.size(); i ++)
        {
            if(T::GetTypeNameStatic() == _ComponentList[i]->GetTypeName())
            {
                return true;
            }
        }
        return false;
    }
}
