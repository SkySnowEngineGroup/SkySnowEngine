//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
// Open source is written by wangcan(crygl)¡¢liuqian(SkySnow)¡¢zhangshuangxue(Calence)
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
namespace Nuwa
{
	void* Thread::RunThreadFunStatic(void* ptr)
	{
		Thread* thread = (Thread*)(ptr);
		thread->UpdatePriority(thread);
		void* res = nullptr;
		res = thread->m_ThreadFunPtr(thread->m_Data);
		thread->m_Runing = false;
		pthread_exit((void*)nullptr);
		return reinterpret_cast<void*>(res);
	}

	Thread::Thread() 
		: m_PThread(new pthread_t)
		, m_Runing(false)
		, m_Priority(ETP_Normal)
		, m_DefaultPriority(0)
		, m_Data(nullptr)
		, m_ThreadFunPtr(nullptr)
	{
	}

	Thread::~Thread()
	{
		if (m_PThread)
		{
			pthread_join(*m_PThread, nullptr);
			delete m_PThread;
			m_PThread = nullptr;
		}
	}

	void Thread::CreateThread()
	{
		pthread_create(m_PThread, NULL, RunThreadFunStatic, (void*)this);
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