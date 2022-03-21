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
	{

	}
	Application::~Application()
	{
        if(m_Window)
        {
            delete m_Window;
            m_Window = nullptr;
        }
	}

	int Application::RunApplication(Application* app, int argc, const char* const* argv)
	{
        m_Window = new SN_GLFWWindow();
        m_Window->SNCreateWindow(DEFAUT_WADTH,DEFAUT_HEIGHT);
        m_MainThread = new EngineMainThread();
        void(*Test)(void);
        Test a = EngineLoop;
        m_MainThread->AttactMainThread(el);
        m_RenderThread = new RenderingThread();
        m_RenderThread->SetGLContext(m_Window->GetWindow());
        
        bool isInit = app->Init(argc,argv, DEFAUT_WADTH, DEFAUT_HEIGHT);
		while (!m_Window->SNIsCloseWindow())
		{
			//SN_LOG("Main Thread Update.");
			app->Update();
		}
        m_Window->SNShutDown();
        return 0;
	}

    void Application::EngineLoop()
    {
        
    }
}
