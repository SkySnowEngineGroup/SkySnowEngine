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

#include "RunnablePThread.h"
namespace SkySnow
{
	RunnablePThread::RunnablePThread()
		: _DThreadPriority(0)
		, _IsExit(false)
	{

	}
	RunnablePThread::~RunnablePThread()
	{
		Exit();
	}

	void RunnablePThread::SetPriority(ThreadPriority priority)
	{
		if (_ThreadPriority != priority)
		{
			_ThreadPriority = priority;
			UpdatePriority(_PThread, _ThreadPriority);
		}
	}

	void RunnablePThread::Pause()
	{

	}

	bool RunnablePThread::Exit()
	{
		if (_Runnable)
		{
			_Runnable->Stop();
		}
		if (!_IsExit)
		{
			pthread_join(_PThread, nullptr);
			_IsExit = true;
		}
		return true;
	}

	void RunnablePThread::WaitForExit()
	{

	}
	void* RunnablePThread::PThreadFun(void* ptr)
	{
		RunnablePThread* thread = (RunnablePThread*)(ptr);
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
		SN_WARN("IOS and Mac not support this api pthread_setname_np.");
#else
		pthread_setname_np(thread->_PThread, thread->_ThreadName.c_str());
#endif
		thread->UpdatePriority(thread->_PThread, thread->_ThreadPriority);
		thread->Run();
		pthread_exit((void*)nullptr);
		return nullptr;
	}
	bool RunnablePThread::CreateThread(Runnable* runnable, std::string name)
	{
		_Runnable = runnable;
		_ThreadName = name;
		_Runnable->Init();
		int result = pthread_create(&_PThread, nullptr, PThreadFun, (void*)this);
		if (result != 0)
		{
			SN_WARN("Pthread_create fail.");
		}

		struct sched_param param;
		int outputPolicy;
		if (pthread_getschedparam(_PThread, &outputPolicy, &param) == 0)
		{
			_DThreadPriority = param.sched_priority;
		}
		if (_ThreadPriority != ETP_Normal)
		{
			UpdatePriority(_PThread,_ThreadPriority);
		}
		
		return true;
	}

	void RunnablePThread::Run()
	{
		if (_Runnable->Init())
		{
			_Runnable->Run();
			_Runnable->Exit();
		}
	}

	void RunnablePThread::UpdatePriority(pthread_t thread, ThreadPriority newPriority)
	{
		struct sched_param param;
		int policy;
		pthread_getschedparam(thread, &policy, &param);
		int min = sched_get_priority_min(policy);
		int max = sched_get_priority_max(policy);
		int priority;
		switch (newPriority)
		{
		case ETP_Low:
			priority = min;
			break;
		case ETP_Normal:
			priority = 0;
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
			pthread_setschedparam(thread, policy, &param);
		}
	}
}