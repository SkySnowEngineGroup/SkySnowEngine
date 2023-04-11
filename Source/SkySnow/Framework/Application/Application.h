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
#include "GRIProfiles.h"
#include <stdlib.h>
#include <iostream>
#include "GLFWWindow.h"
//#include "EngineMainThread.h"
namespace SkySnow
{
#if defined(PLATFORM_WINDOW) || defined(PLATFORM_MAC)
#define SkySnow_DEFINE_APPLICATION_MAIN(application, ...)	\
	int main(int argc, char** argv)			                \
	{											            \
			application app(__VA_ARGS__);				    \
            app.RunApplication(&app,argc,argv);             \
			return 0;	                                    \
	}
#endif
	class Application
	{
	public:
		Application(const char* name,const char* description);
		virtual ~Application();
		virtual bool Init(int32_t argc, const char* const* _argv, uint32_t width,uint32_t height) = 0;
		virtual void Update() = 0;
    public:
        //don't overload child
        int RunApplication(Application* app, int argc, const char* const* argv);
    protected:
        void* GetNativeWindow()
        {
            return _Window->GetNativeWindow();
        }
	private:
        void MainThreadLoop();
	private:
		bool				_IsInit;
		const char*			_Name;
		const char*			_Description;
		const char* const*	_Argv;
		int					_Argc;
        GLFWWindow*		    _Window;
		Application*		_ChildApp;
	};
	
}

