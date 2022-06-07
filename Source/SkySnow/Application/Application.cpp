//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
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
namespace SkySnow
{
	Application::Application(const char* name, const char* description)
		: m_Name(name)
		, m_Description(description)
        , m_Window(nullptr)
        , m_ChildApp(nullptr)
        , m_IsInit(false)
        , m_MainThread(nullptr)
        , m_RenderThread(nullptr)
	{

	}
	Application::~Application()
	{
        if(m_Window)
        {
            delete m_Window;
            m_Window = nullptr;
        }
        if (m_MainThread)
        {
            delete m_MainThread;
            m_MainThread = nullptr;
        }
        if (m_RenderThread)
        {
            delete m_RenderThread;
            m_RenderThread = nullptr;
        }
	}

	int Application::RunApplication(Application* app, int argc, const char* const* argv)
	{
        m_Window = new SN_GLFWWindow();
        m_Window->SNCreateWindow(DEFAUT_WADTH,DEFAUT_HEIGHT);

        //m_MainThread = new EngineMainThread();
        //m_MainThread->AttactMainThread(&Application::EngineLoop,this);
        //m_MainThread->StartEngineMainThread();
        //如果是GLFW，GLFWSwapBuffer必须在主线程进行调用，因为SwapBuffer是交换后台缓冲到前台缓冲显示。
        //如果想要单独起一个渲染线程，那么需要创建一个ShareContext给渲染线程，渲染到BackBuffer中，从BackBuffer
        //可以使用像素解包缓冲区到纹理，给GLFW所在线程显示,或者是使用windowsurface，渲染到挂载到fbo的纹理上给GLFW所在线程显示
        m_RenderThread = new RenderingThread();
        m_RenderThread->SetSNWindow(m_Window);

        m_ChildApp = app;
        m_Argc = argc;
        m_Argv = argv;
        
        m_RenderThread->RenderOneFrame();

        //m_MainThread->StopEngineMainThread();
        return 0;
	}

    void Application::EngineLoop()
    {
        if (!m_IsInit)
        {
            m_ChildApp->Init(m_Argc, m_Argv, DEFAUT_WADTH, DEFAUT_HEIGHT);
            m_IsInit = true;
        }
        m_ChildApp->Update();
    }
}
