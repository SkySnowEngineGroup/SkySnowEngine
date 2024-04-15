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
#include "SkySnowProfiles.h"
#include "SkySnowEngine.h"
#include "Context.h"
#include "EngineWindow.h"
namespace SkySnow
{
	Application::Application(const char* name, const char* description,uint32_t width, uint32_t height)
		: _Name(name)
		, _Description(description)
        , _Width(width)
        , _Height(height)
        , _EngineUsagType(None)
        , _SkySnowEngine(nullptr)
        , _EditorWindow(nullptr)
        , _GameWindow(nullptr)
	{

	}
	Application::~Application()
	{
        Context::Instance().RemoveEngine();
        Delete_Object(_GameWindow);
	}

	void Application::RunApplication()
	{
        RunAppInternal();
	}
    void Application::RunAppInternal()
    {
        //注册SkySnowEngine到Context中
        _SkySnowEngine = Context::Instance().RegisterEngine();
        _SkySnowEngine->Init();
        
        //Create Window
        _GameWindow = new EngineWindow(EGameWindow);
        _GameWindow->CreateEngineWindow(_Width, _Height);
        SSContext().SetGameWindow(_GameWindow);
        //Start Engine MainUpdate
        MainUpdateInternal();
        
        ShutDown();
        _GameWindow->ShutDown();
        _SkySnowEngine->ShutDown();
    }

    void Application::MainUpdateInternal()
    {
        while (!_GameWindow->GetOSWindow()->IsCloseWindow())
        {
            _SkySnowEngine->BeginFrame();
            _GameWindow->BeginWindow();
            //Child App Init
            if (!_AppInit)
            {
                Init();
                _AppInit = true;
            }
            //Chile App Update
            Update();
            _SkySnowEngine->EngineLoop();
            
            _GameWindow->EndWindow();
            _SkySnowEngine->EndFrame();
            glfwPollEvents();
        }
    }
}
