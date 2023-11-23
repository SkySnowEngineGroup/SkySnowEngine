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
#include <memory>
namespace SkySnow
{
    //if GO has parent-child,A TransformComponent must be mounted
    //https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
    class Scene;
	class GameObject : public Object , public std::enable_shared_from_this<GameObject>
	{
		SkySnow_Object(GameObject, Object);
        friend class Scene;
	public:
		GameObject();
		virtual ~GameObject();
        
        void SetLayer(int32_t layer);
        int32_t GetLayer() const;
        int32_t GetLayerMask() const;
        
        void SetEnable(bool enable);
        bool IsEnable() const;
        
        void SetTag(int16_t tag);
        int16_t GetTag() const;

        template<typename T> SPtr<T> AddComponent();
        template<typename T> void RemoveComponent();
        
        template<typename T> SPtr<T> GetComponent();
        template<typename T> bool HasComponent();
        
        SPtr<GameObject> AddChild();
        void RemoveChild(SPtr<GameObject> childGO);
        void SetParent(SPtr<GameObject> parentGO);

        WPtr<Scene> GetHostScene() const
        {
            if (!_HostScene.lock())
            {
                SN_WARN("Curr GameObject Not Attach Any Scene.");
            }
            return _HostScene;
        }
	private:
        SPtr<GameObject> GetPtr()
        {
            return shared_from_this();
        }

        void AttachScene(WPtr<Scene> scene)
        {
            _HostScene = scene;
        }
    private:
        bool                        _Enable;
        //GameObject at Layer
        int32_t                         _Layer;
        int16_t                         _Tag;
        SPtr<GameObject>                _Parent;
        WPtr<Scene>                     _HostScene;
        std::vector<SPtr<GameObject>>   _ChildList;
        std::vector<SPtr<IComponent>>   _ComponentList;
	};

    //========================================================================================
    template<typename T> inline SPtr<T> GameObject::AddComponent()
    {
        for (int i = 0; i < _ComponentList.size(); i++)
        {
            if(T::GetTypeNameStatic() == _ComponentList[i]->GetTypeName())
            {
                SN_WARN("A component of this type(%s) is already included",_ComponentList[i]->GetTypeName());
                return SPtr<T>(dynamic_cast<T*>(_ComponentList[i].get()));
            }
        }
        SPtr<T> newCom = CreateSPtr<T>();
        newCom->AttachGO(GetPtr());
        _ComponentList.emplace_back(newCom);
        return newCom;
    }
    template<typename T> void GameObject::RemoveComponent()
    {
        for (auto iter = _ComponentList.begin(); iter != _ComponentList.end(); ++iter)
        {
            if((*iter)->GetTypeName() == T::GetTypeNameStatic())
            {
                (*iter)->DetachGO();
                _ComponentList.erase(iter);
                break;
            }
        }
    }
    template<typename T> inline SPtr<T> GameObject::GetComponent()
    {
        for (int i = 0; i < _ComponentList.size(); i++)
        {
            if (T::GetTypeNameStatic() == _ComponentList[i]->GetTypeName())
            {
                return dynamic_cast<T>(_ComponentList[i]);
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
}
