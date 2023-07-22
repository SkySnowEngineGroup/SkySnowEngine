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
#include "SkySnowProfiles.h"
#include <stdlib.h>
#include <iostream>
#include "IWindow.h"
#include "Framework.h"
namespace SkySnow
{
	enum EngineUsagType
	{
		None	= 0,
		Sample	= 1,
		Editor	= 2
	};
	class Application
	{
	public:
		Application(const char* name,const char* description, uint32_t width, uint32_t height);
		virtual ~Application();
		virtual bool Init() = 0;
		//virtual void Update() = 0;
    public:
        //don't overload child
        int RunApplication();
		void SetUseEngineType(EngineUsagType eut) { _EngineUsagType = eut; }
	private:
        //void* GetNativeWindow()
        //{
        //    return _Window->GetNativeWindow();
        //}
	
        void MainThreadLoop();

		void InitAppication();
	private:
		EngineUsagType		_EngineUsagType;
		bool				_IsInit;
		uint32				_Width;
		uint32				_Height;
		const char*			_Name;
		const char*			_Description;
        IWindow*		    _Window;
		Framework*			_Framework;
	};
	
}

