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
#include "EngineMainThread.h"
#include "Application.h"
namespace SkySnow
{
	EngineMainThread::EngineMainThread()
		: m_ExitMainThread(false)
		, m_MainThread(nullptr)
		, m_EngineLoopFunPtr(nullptr)
	{
	}

	EngineMainThread::~EngineMainThread()
	{
		if (m_MainThread)
		{
			delete m_MainThread;
			m_MainThread = nullptr;
		}
	}

	void EngineMainThread::StartEngineMainThread()
	{
		if (m_MainThread == nullptr)
		{
			m_MainThread = new SkySnow::Thread();
			m_MainThread->SetName("Main_Thread.");
			m_MainThread->Run(EngineMainThreadRun, this);
		}
	}

	void EngineMainThread::StopEngineMainThread()
	{
		if (m_MainThread)
		{
			m_ExitMainThread = true;
			m_MainThread->Stop();
		}
	}

	void EngineMainThread::AttactMainThread(void(Application::* EngineLoopFun)(void), Application* ptr)
	{
		m_EngineLoopFunPtr = EngineLoopFun;
		m_App = ptr;
	}

	void EngineMainThread::MainThreadUpdate()
	{
		while (!m_ExitMainThread)
		{
			(m_App->*m_EngineLoopFunPtr)();
			SN_LOG("SkySnowEngine EngineMain Thread Update.");
		}
	}
}