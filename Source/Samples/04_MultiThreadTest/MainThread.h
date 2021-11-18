//
// Copyright (c) 2020-2022 the PhoneixEngine project.
// Open source is written by liuqian(SkySnow)¡¢zhangshuangxue(Calence)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#pragma once
#include "LogAssert.h"
#include "Thread.h"
#include "ThreadDoubleQueue.h"
class MainThread
{
public:
	MainThread(DoubleQueue::ThreadDoubleQueue* tdq)
        : m_MainThread_quit(false)
        , m_MainThread(nullptr)
        , m_DoublueQueue(tdq)
	{
	}

	virtual ~MainThread()
	{
        if (m_MainThread)
        {
            delete m_MainThread;
            m_MainThread = nullptr;
        }
	}
    void StartMainThread()
    {
        if (m_MainThread == nullptr)
        {
            m_MainThread = new Nuwa::Thread();
            m_MainThread->SetName("Main_Thread.");
            m_MainThread->Run(MainThreadRun, this);
        }
        return;
    }
    void StopMainThread()
    {
        if (m_MainThread)
        {
            m_MainThread_quit = true;
            m_MainThread->Stop();
        }
    }
private:
    static void* MainThreadRun(void* data)
    {
        MainThread* worker = (MainThread*)data;
        worker->Run();
        return nullptr;
    }

    void Run()
    {
        while (!m_MainThread_quit)
        {
            if (m_DoublueQueue)
            {
                m_DoublueQueue->EngineUpdate();
            } 
        }
    }
private:
    bool                            m_MainThread_quit;
    Nuwa::Thread*                   m_MainThread;
    DoubleQueue::ThreadDoubleQueue* m_DoublueQueue;
};