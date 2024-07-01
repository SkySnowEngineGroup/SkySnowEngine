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
#include "GameObjectManager.h"
#include <memory>
namespace SkySnow
{
    //if GO has parent-child,A TransformComponent must be mounted
    class Scene;
	class GameObject : public Object
	{
		SkySnow_Object(GameObject, Object);
        friend class Scene;
        friend class GameObjectManager;
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
        
        SPtr<GameObject> GetGameObjectPtr();
        SPtr<Scene> GetHostScenePtr();
        
        const UUID& GetHostSceneUUID() const { return _SceneUUID;}
        const bool IsBelongScene(const UUID& uuid) { return uuid == _SceneUUID;}
	private:
        void SetSceneUUID(const UUID& sceneUUID){_SceneUUID = sceneUUID;}
    private:
        bool                            _Enable;
        int32_t                         _Layer;//GameObject at Layer
        int16_t                         _Tag;
        UUID                            _ParentUUID = UUID::EMPTY;
        UUID                            _SceneUUID = UUID::EMPTY;
        std::vector<int64>              _ChildUUIDList;
	};

    //========================================================================================
    template<typename T> inline SPtr<T> GameObject::AddComponent()
    {
        SPtr<T> curCom = std::static_pointer_cast<T>(GetGOManager().GetComponentPtr(_UUID, T::GetTypeNameStatic()));
        if(!curCom)
        {
            curCom = CreateSPtr<T>();
            GetGOManager().GetComponents()[_UUID].emplace_back(curCom);
            curCom->AttachGameObject(_UUID);
            curCom->OnInitialized();
            curCom->AddToModule();
        }
        return curCom;
    }
    //========================================================================================
    template<typename T> void GameObject::RemoveComponent()
    {
        GetGOManager().RemoveComponentPtr(_UUID, T::GetTypeNameStatic());
    }
    //========================================================================================
    template<typename T> inline SPtr<T> GameObject::GetComponent()
    {
        SPtr<T> com = std::static_pointer_cast<T>(GetGOManager().GetComponentPtr(_UUID, T::GetTypeNameStatic()));
        return com;
    }
    //========================================================================================
    template<typename T> inline bool GameObject::HasComponent()
    {
        SPtr<T> com = std::static_pointer_cast<T>(GetGOManager().GetComponentPtr(_UUID, T::GetTypeNameStatic()));
        return com ? true : false;
    }
    //========================================================================================
}
