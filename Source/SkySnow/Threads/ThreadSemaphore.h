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
#pragma once
#include "NonCopyable.h"
#include <errno.h>
#include "LogAssert.h"
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
#include <dispatch/dispatch.h>
#else
#include <semaphore.h>
#endif
namespace SkySnow
{
	class ThreadSemaphore : public NonCopyable
	{
	public:
		ThreadSemaphore() 
		{
            Create();
		}

		virtual ~ThreadSemaphore()
		{ 
            Destroy();
		}

		inline void Reset()
		{ 
			Destroy();
			Create(); 
		}

        inline void WaitForSignal()
        {
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
            int ret = dispatch_semaphore_wait(m_Semaphore,DISPATCH_TIME_FOREVER);
            if(ret != 0)
            {
                SKYSNOWERROR("Filed to wait on a semaphore.");
            }
#else
            int ret = 0;
            while ((ret = sem_wait(&m_Semaphore)) == -1 && errno == EINTR)
            {
                continue;
            }
            if (ret == -1)
            {
                SKYSNOWERROR("Filed to wait on a semaphore(%s).", strerror(errno));
            }
#endif
        }

        inline void Signal()
        {
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
            dispatch_semaphore_signal(m_Semaphore);
#else
            if (sem_post(&m_Semaphore) == -1)
            {
                SKYSNOWERROR("Filed to post to a semaphore(%s).", strerror(errno));
            }
#endif
        }
    private:
        void Create()
        {
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
            m_Semaphore = dispatch_semaphore_create(0);
            if(m_Semaphore == nullptr)
            {
                SKYSNOWERROR("dispatch_semaphore_create failed.");
            }
#else
            if (sem_init(&m_Semaphore, 0, 0) == -1)
            {
                SKYSNOWERROR("Failed to open a semaphore(%s).", strerror(errno));
            }
#endif
        }
        void Destroy()
        {
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
            dispatch_release(m_Semaphore);
#else
            if (sem_destroy(&m_Semaphore) == -1)
            {
                SKYSNOWERROR("Filed to destroy a semaphore(%s).", strerror(errno));
            }
#endif
        }
    private:
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
        dispatch_semaphore_t m_Semaphore;
#else
        sem_t m_Semaphore;
#endif
	};
}
