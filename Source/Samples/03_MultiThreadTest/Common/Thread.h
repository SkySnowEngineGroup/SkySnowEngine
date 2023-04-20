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
#include <cstdint>
#include <pthread.h>
#include "ThreadProfiles.h"
using namespace SkySnow;
namespace ThreadMultiRender
{
	class Thread : public NonCopyable
	{
	public:
		Thread();
		virtual ~Thread();
		void Run(void*(*thread_funptr)(void*), void* data);

		void SetName(const char* name)
		{
			m_ThreadName = name;
		}

		void Stop();

		void SetPriority(ThreadPriority tpri);

		ThreadPriority GetThreadPriority()
		{
			return m_Priority;
		}
		bool IsRunning() const
		{
			return m_IsRunning;
		}
		static pthread_t GetCurrentThreadID();
	protected:
		void CreateThread();
	private:
		static void* RunThreadFunStatic(void* ptr);
		void UpdatePriority(const Thread* thread) const;
	private:
		void*			m_Data;
		void*			(*m_ThreadFunPtr)(void*);
		volatile bool	m_IsRunning;
		ThreadPriority	m_Priority;
		int				m_DefaultPriority;
		pthread_t*		m_PThread;
		const char*		m_ThreadName;
	};
}