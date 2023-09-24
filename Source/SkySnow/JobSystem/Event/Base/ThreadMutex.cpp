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
#include "ThreadMutex.h"
#include "LogAssert.h"
namespace SkySnow
{
	ThreadMutex::ThreadMutex()
	{
		pthread_mutexattr_t    attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&m_mutex, &attr);
		pthread_mutexattr_destroy(&attr);
	}

	ThreadMutex::~ThreadMutex()
	{
		pthread_mutex_destroy(&m_mutex);
	}

	void ThreadMutex::Lock()
	{
		pthread_mutex_lock(&m_mutex);
	}

	void ThreadMutex::UnLock()
	{
		pthread_mutex_unlock(&m_mutex);
	}

	bool ThreadMutex::TryLock()
	{
		return pthread_mutex_trylock(&m_mutex) == 0;
	}

    ThreadRWMutex::ThreadRWMutex()
    {
        int err = pthread_rwlock_init(&_Mutex, nullptr);
        if(err != 0)
        {
            SN_ERR("pthread_rwlock_init failed with error:%d",err);
        }
    }

    ThreadRWMutex::~ThreadRWMutex()
    {
        int err = pthread_rwlock_destroy(&_Mutex);
        if(err != 0)
        {
            SN_ERR("pthread_rwlock_destroy failed with error: %d",err);
        }
    }

    //read lock
    void ThreadRWMutex::ReadLock()
    {
        int err = pthread_rwlock_rdlock(&_Mutex);
        if(err != 0)
        {
            SN_ERR("pthread_rwlock_rdlock failed with error: %d",err);
        }
    }
    //read unlock
    void ThreadRWMutex::ReadUnLock()
    {
        int err = pthread_rwlock_unlock(&_Mutex);
        if(err != 0)
        {
            SN_ERR("pthread_rwlock_unlock failed with error: %d",err);
        }
    }
    //write lock
    void ThreadRWMutex::WriteLock()
    {
        int err = pthread_rwlock_wrlock(&_Mutex);
        if(err != 0)
        {
            SN_ERR("pthread_rwlock_wrlock failed with error: %d",err);
        }
    }
    //write unlock
    void ThreadRWMutex::WriteUnlock()
    {
        int err = pthread_rwlock_unlock(&_Mutex);
        if(err != 0)
        {
            SN_ERR("pthread_rwlock_unlock failed with error: %d",err);
        }
    }

}
