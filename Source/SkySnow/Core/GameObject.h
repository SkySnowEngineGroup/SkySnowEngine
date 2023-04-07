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
#pragma once
#include "Object.h"
#include "IComponent.h"
namespace SkySnow
{
	class GameObject : public Object
	{
		SkySnow_Object(GameObject, Object);
	public:
		GameObject();
		virtual ~GameObject();
        
        void SetLayer(int32_t layer);
        
        int32_t GetLayer() const;
        //Gets the tag of the GameObject's level
        int32_t GetLayerMask() const;

		template<typename T> T* GetComponent();

		template<typename T> bool HasComponent();

        void AddComponent(IComponent* component);
        
        void RemoveComponent(IComponent* component);
        
        template<typename T> void GetComponents(std::vector<IComponent*>& comList);
	private:
        //GameObject at Layer
        int32_t _Layer;
        //TODO: Whether the array is going to be here, whether it's going to be a miss in memory
		std::vector<IComponent*> _ComponentList; 
	};

    //========================================================================================
    template<typename T> inline T* GameObject::GetComponent()
    {
        for (int i = 0; i < _ComponentList.size(); i++)
        {
            if (T::GetTypeNameStatic() == _ComponentList[i]->GetTypeName())
            {
                IComponent* com = _ComponentList[i];
                return dynamic_cast<T*>(com);
            }
        }
        return nullptr;
    }
    //========================================================================================
    template<typename T> inline bool GameObject::HasComponent()
    {
        for (int i = 0; i < _ComponentList.size(); i++)
        {
            if (T::GetTypeNameStatic() == _ComponentList[i]->GetTypeName())
            {
                return true;
            }
        }
        return false;
    }
    //========================================================================================
    template<typename T> inline void GameObject::GetComponents(std::vector<IComponent*>& comList)
    {
        for(auto entry:_ComponentList)
        {
            if(T::GetTypeNameStatic() == entry->GetTypeName())
            {
                comList.emplace_back(entry);
            }
        }
    }
}
