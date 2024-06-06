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
    class Scene;
    class IProxy;
    class GameObject;
	class IComponent : public Object
	{
		SkySnow_Object(IComponent,Object);
	public:
        IComponent();
        virtual ~IComponent();
        
		virtual bool IsEnable() const{ return _Enable;}
		virtual void SetEnable(bool enable){ _Enable = enable;}
        
        //attach this comonent to gameobject
        void AttachGO(int64 goUuid);
        //Get curr component attach gameobject
        SPtr<GameObject> GetHostGoPtr() const;
        //Get Scene
        SPtr<Scene> GetHostScenePtr() const;
        SceneHandle GetHostSceneHandle() const { return _SceneHandle;}
	protected:
		bool		     _Enable;
        int64            _GoUUID;
        SceneHandle      _SceneHandle;
	};
}
