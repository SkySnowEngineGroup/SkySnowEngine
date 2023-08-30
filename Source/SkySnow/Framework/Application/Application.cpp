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
#include "GRI.h"
#include "SkySnowEngine.h"
#include "Context.h"
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
        , _Framework(nullptr)
	{

	}
	Application::~Application()
	{
        Delete_Object(_Framework);
        Context::Instance().RemoveSkySnowEngine();
	}

	void Application::RunApplication()
	{
        RunAppInternal();
	}
    void Application::RunAppInternal()
    {
        //注册SkySnowEngine到Context中
        _SkySnowEngine = Context::Instance().RegisterSkySnowEngine();
        _SkySnowEngine->Init();
        //Create Window
        _GameWindow = _SkySnowEngine->CreateGameWindow(_Width, _Height);
        if (_EngineUsagType == Editor)
        {
            _EditorWindow = _SkySnowEngine->CreateEditorWindow(_Width, _Height);
        }
        
        //Create Engine Framework
        _Framework = new Framework();
        _Framework->Init();
        //Start Engine MainUpdate
        MainUpdateInternal();
        ShutDown();
        _Framework->ShutDown();
        _SkySnowEngine->ShutDown();
    }

    void Application::MainUpdateInternal()
    {
        while (!_SkySnowEngine->IsEngineWindowClose())
        {
            //main thread start
            _GQueue->BeginFrame();
            FlushResource();
            //Child App Init
            if (!_AppInit)
            {
                Init();
                _AppInit = true;
            }
            //Chile App Update
            Update();
            _Framework->MainUpdate();
            //main thread end
            _GQueue->EndFrame();
            glfwPollEvents();
        }
    }
}
