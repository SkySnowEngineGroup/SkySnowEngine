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
#include "LogAssert.h"
#include "Thread.h"
#include "ThreadQueue.h"
using namespace ThreadMultiRender;
class RenderThreadMulti
{
public:
    RenderThreadMulti(ThreadMultiRender::ThreadQueue* tdq)
		: m_RenderThread_quit(false)
		, m_RenderThread(nullptr)
        , m_ThreadQueue(tdq)
	{

	}

	virtual ~RenderThreadMulti()
	{
        if (m_RenderThread)
        {
            delete m_RenderThread;
            m_RenderThread = nullptr;
        }

	}
    void StartRenderThread()
    {
        if (m_RenderThread == nullptr)
        {
            m_RenderThread = new Thread();
            m_RenderThread->SetName("Render_Thread.");
            m_RenderThread->Run(RenderThreadRun, this);
        }
        //return;
    }
    void StopRenderThread()
    {
        if (m_RenderThread)
        {
            m_RenderThread_quit = true;
            m_RenderThread->Stop();
        }
    }
    bool IsRuning()
    {
        return m_RenderThread->IsRunning();
    }
private:
    static void* RenderThreadRun(void* data)
    {
        RenderThreadMulti* worker = (RenderThreadMulti*)data;
        worker->Run();
        return nullptr;
    }

    void Run()
    {
        while (!m_RenderThread_quit)
        {
            if (m_ThreadQueue)
            {
                m_ThreadQueue->RenderOneFrame();
            }
        }
    }
private:
	bool			                m_RenderThread_quit;
	Thread*	                        m_RenderThread;
    ThreadMultiRender::ThreadQueue* m_ThreadQueue;
};
