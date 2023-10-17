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
#include "ThreadProfiles.h"
#include "NonCopyable.h"
#include "Runnable.h"
#include <thread>
namespace SkySnow
{
	struct ThreadID
	{
		static uint32 GetCurrThreadId()
		{
			std::thread::id threadId = std::this_thread::get_id();
			return std::hash<std::thread::id>{}(threadId);
		}
	};
	class RunnableThread : public NonCopyable
	{
	public:
		RunnableThread();
		virtual ~RunnableThread();

		static RunnableThread* Create(Runnable* runable);

		virtual void SetPriority(ThreadPriority priority) = 0;

		virtual void Pause() = 0;

		virtual bool Exit() = 0;

		virtual void WaitForExit() = 0;

		const uint32 GetThreadID() const
		{
			return _ThreadID;
		}
	protected:
		virtual bool CreateThread(Runnable* runnable,std::string name = "NullName") = 0;
	protected:
		Runnable*		_Runnable;
		ThreadPriority	_ThreadPriority;
		std::string		_ThreadName;
		uint32			_ThreadID;
	};

	extern RunnableThread* GRenderThread;
	extern bool IsInRenderThread();
}
