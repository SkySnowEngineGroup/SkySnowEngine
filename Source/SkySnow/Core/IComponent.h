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
#include "SPtr.h"
#include <vector>
namespace SkySnow
{
    class GameObject;
    class Scene;
    class IProxy;
	class IComponent : public Object , public std::enable_shared_from_this<IComponent>
	{
		SkySnow_Object(IComponent,Object);
	public:
		IComponent()
			: _Enable(true)
		{
		}
        
		virtual ~IComponent()
        {
        }

		virtual void Deactivate()
        {
            _Enable = false;
        }

		virtual bool HasEnabled() const
        {
            return _Enable;
        }

		virtual void SetEnabled(bool enable)
        {
            _Enable = enable;
        }
        //attach this comonent to gameobject
        void AttachGO(WPtr<GameObject> go);
        
        SceneHandle GetSceneHandle()
        {
            return _SceneHandle;
        }
        //Get curr component attach gameobject
        WPtr<GameObject> GetGameObject() const
        {
            if(!_GameObject.lock())
            {
                SN_WARN("Curr Component Not Attach Any GameObject.");
            }
            return _GameObject;
        }
        //Get Scene
        WPtr<Scene> GetHostScene() const;
        //proxy
        //引擎层与渲染层代理，每个引擎层组件只能绑定一个代理
        virtual void CreateProxy(){}
    protected:
        SPtr<IComponent> GetPtr()
        {
            return shared_from_this();
        }
	protected:
		bool		     _Enable;
        WPtr<GameObject> _GameObject;
        SceneHandle      _SceneHandle;
	};
}
