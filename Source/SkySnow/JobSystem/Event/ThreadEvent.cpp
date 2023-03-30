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
#include "ThreadEvent.h"

namespace SkySnow
{
	ThreadEvent::ThreadEvent()
	{
		if (pthread_mutex_init(&_Mutex, nullptr) == 0)
		{
			if (pthread_cond_init(&_Condition, nullptr) == 0)
			{
				_Initial = true;
			}
			else
			{
				pthread_mutex_destroy(&_Mutex);
				SN_ERR("Create Mutex Fail.\n");
			}
		}
	}
	ThreadEvent::~ThreadEvent()
	{
		if (_Initial)
		{
			Signal();
			LockEventMutex();
			pthread_cond_destroy(&_Condition);
			UnlockEventMutex();
			pthread_mutex_destroy(&_Mutex);
		}
	}

	void ThreadEvent::Signal()
	{
		LockEventMutex();
		//todo multi threads
		pthread_cond_signal(&_Condition);
		UnlockEventMutex();
	}

	void ThreadEvent::Wait()
	{
		LockEventMutex();
		pthread_cond_wait(&_Condition, &_Mutex);
		UnlockEventMutex();
	}
}