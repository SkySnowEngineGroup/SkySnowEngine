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
#include <vector>
namespace SkySnow
{
    class GameObject;
	class IComponent : public Object
	{
		SkySnow_Object(IComponent,Object);
	public:
		IComponent()
			: _GameObject(nullptr)
		{
		}
		virtual ~IComponent() {}

		virtual void Update() = 0;

		virtual void Deactivate() { _Enable = false; }

		virtual bool HasEnabled() const { return _Enable; }

		virtual void SetEnabled(bool enable) { _Enable = enable; }
        //base function
        void AttachToGameObject(GameObject* go);
	protected:
		bool		_Enable = true;
        GameObject* _GameObject;
	};
}
