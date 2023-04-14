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
#include "Application.h"
#include "LogAssert.h"
#include "GRIProfiles.h"
#include "OSPlatform.h"
#include "GRI.h"
namespace SkySnow
{
	Application::Application(const char* name, const char* description)
		: _Name(name)
		, _Description(description)
        , _Window(nullptr)
        , _ChildApp(nullptr)
        , _Argv(nullptr)
        , _Argc(0)
        , _IsInit(false)
        , _Framework(nullptr)
	{

	}
	Application::~Application()
	{
        if(_Window)
        {
            delete _Window;
            _Window = nullptr;
        }
        if (_Framework)
        {
            delete _Framework;
            _Framework = nullptr;
        }
	}

	int Application::RunApplication(Application* app, int argc, const char* const* argv)
	{
        _ChildApp = app;
        _Argc = argc;
        _Argv = argv;
        MainThreadLoop();
        return 0;
	}
    void Application::MainThreadLoop()
    {
        _Window = new GLFWWindow();
        _Window->CreateEngineWindow(DEFAUT_WADTH, DEFAUT_HEIGHT);
        
        _Framework = new Framework();
        FrameworkInfo frameInfo;
        OSPlatformInfo osPlatformInfo;
        osPlatformInfo._NativeWindow = GetNativeWindow();
        frameInfo._OSPlatformInfo = osPlatformInfo;
        _Framework->Init(frameInfo);
        
        _ChildApp->Init(_Argc, _Argv, DEFAUT_WADTH, DEFAUT_HEIGHT);
        glViewport(0,0,DEFAUT_WADTH,DEFAUT_HEIGHT);
        while (!_Window->IsCloseWindow())
        {
            //_ChildApp->Update();
            _Framework->MainUpdate();
            glfwPollEvents();
        }
        _Framework->Stop();
        _Framework->Exit();
        _Window->ShutDown();
    }
}
