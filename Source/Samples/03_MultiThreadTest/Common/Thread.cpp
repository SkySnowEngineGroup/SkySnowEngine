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
#include "Thread.h"
#include "ThreadProfiles.h"
#include "PlatformProfiles.h"
#include "LogAssert.h"
namespace ThreadMultiRender
{
	void* Thread::RunThreadFunStatic(void* ptr)
	{
		Thread* thread = (Thread*)(ptr);
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
        SN_WARN("IOS and Mac not support this api pthread_setname_np.");
#else
        pthread_setname_np(*thread->m_PThread, thread->m_ThreadName);
#endif
		thread->UpdatePriority(thread);
		void* res = nullptr;
		res = thread->m_ThreadFunPtr(thread->m_Data);
		thread->m_IsRunning = false;
		pthread_exit((void*)nullptr);
		return reinterpret_cast<void*>(res);
	}

	Thread::Thread() 
		: m_PThread(new pthread_t)
		, m_IsRunning(false)
		, m_Priority(ETP_Normal)
		, m_DefaultPriority(0)
		, m_Data(nullptr)
		, m_ThreadFunPtr(nullptr)
		, m_ThreadName(nullptr)
	{
	}

	Thread::~Thread()
	{
		if (m_PThread)
		{
			m_IsRunning = false;
			pthread_join(*m_PThread, nullptr);
			delete m_PThread;
			m_PThread = nullptr;
		}
	}
	void Thread::Run(void* (*thread_funptr)(void*), void* data)
	{
		m_Data = data;
		m_ThreadFunPtr = thread_funptr;
		m_IsRunning = true;

		CreateThread();
	}

	void Thread::Stop()
	{
		void* ptr = 0;
		pthread_join(*m_PThread, &ptr);
		if (nullptr != ptr)
		{
			pthread_exit(ptr);
		}
		m_IsRunning = false;
		m_PThread = 0;
	}

	void Thread::CreateThread()
	{
		int result = pthread_create(m_PThread, nullptr, RunThreadFunStatic, (void*)this);
        if(result != 0)
        {
            SN_WARN("Pthread_create fail.");
        }

		struct sched_param param;
		int outputPolicy;
		if (pthread_getschedparam(*m_PThread, &outputPolicy, &param) == 0)
		{
			m_DefaultPriority = param.sched_priority;
		}
		if (m_Priority != ETP_Normal)
		{
			UpdatePriority(this);
		}
	}

	void Thread::SetPriority(ThreadPriority tpri)
	{
		if (!m_IsRunning && m_Priority == tpri)
		{
			return;
		}
		m_Priority = tpri;
		UpdatePriority(this);
	}

	void Thread::UpdatePriority(const Thread* thread) const
	{
		struct sched_param param;
		int policy;
		pthread_getschedparam(*m_PThread, &policy, &param);
		int min = sched_get_priority_min(policy);
		int max = sched_get_priority_max(policy);
		int priority;
		switch (m_Priority)
		{
			case ETP_Low:
				priority = min;
				break;
			case ETP_Normal:
				priority = m_DefaultPriority;
				break;
			case ETP_Hight:
				priority = max;
				break;
			default:
				priority = min;
				break;
		}
		if (param.sched_priority != priority)
		{
			param.sched_priority = priority;
			pthread_setschedparam(*m_PThread, policy, &param);
		}
	}

	pthread_t Thread::GetCurrentThreadID()
	{
		return pthread_self();
	}
}
