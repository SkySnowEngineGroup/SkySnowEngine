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
#include "NonCopyable.h"
#include <pthread.h>

namespace SkySnow
{
	class ThreadMutex : public NonCopyable
	{
	public:
		ThreadMutex();
		virtual ~ThreadMutex();
		void Lock();
		void UnLock();
		bool TryLock();
	private:
		pthread_mutex_t m_mutex;
	};
    //读写锁
    //读模式下，多个线程可以同时读取共享资源，但不能写入
    //写模式下，只有一个线程可以读写共享资源，其它线程不能读取或写入
    class ThreadRWMutex : public NonCopyable
    {
    public:
        ThreadRWMutex()
        {
            int err = pthread_rwlock_init(&_Mutex, nullptr);
            if(err == 0)
            {
                SN_ERR("pthread_rwlock_init failed with error:%d",err);
            }
        }
        ~ThreadRWMutex()
        {
            int err = pthread_rwlock_destroy(&_Mutex);
            if(err == 0)
            {
                SN_ERR("pthread_rwlock_destroy failed with error: %d",err);
            }
        }
        //read lock
        void ReadLock()
        {
            int err = pthread_rwlock_rdlock(&_Mutex);
            if(err == 0)
            {
                SN_ERR("pthread_rwlock_rdlock failed with error: %d",err);
            }
        }
        //read unlock
        void ReadUnLock()
        {
            int err = pthread_rwlock_unlock(&_Mutex);
            if(err == 0)
            {
                SN_ERR("pthread_rwlock_unlock failed with error: %d",err);
            }
        }
        //write lock
        void WriteLock()
        {
            int err = pthread_rwlock_wrlock(&_Mutex);
            if(err == 0)
            {
                SN_ERR("pthread_rwlock_wrlock failed with error: %d",err);
            }
        }
        //write unlock
        void WriteUnlock()
        {
            int err = pthread_rwlock_unlock(&_Mutex);
            if(err == 0)
            {
                SN_ERR("pthread_rwlock_unlock failed with error: %d",err);
            }
        }
    private:
        pthread_rwlock_t _Mutex;
    };
}
