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
#include "MainThread.h"
#include "RenderThread.h"
#include "ThreadDoubleQueue.h"
namespace ThreadMultiRender
{
	class Engine_DoubleQueue
	{
	public:
		Engine_DoubleQueue()
			: m_MainThread(nullptr)
			, m_RenderThread(nullptr)
			, m_DoublueQueue(nullptr)
		{
		}

		virtual ~Engine_DoubleQueue()
		{
			if (m_MainThread)
			{
				m_MainThread->StopMainThread();
				delete m_MainThread;
				m_MainThread = nullptr;
			}
			if (m_RenderThread)
			{
				m_RenderThread->StopRenderThread();
				delete m_RenderThread;
				m_RenderThread = nullptr;
			}
			if (m_DoublueQueue)
			{
				delete m_DoublueQueue;
				m_DoublueQueue = nullptr;
			}
		}

		void Initial()
		{
			m_DoublueQueue = new ThreadDoubleQueue();
			m_MainThread = new MainThread(m_DoublueQueue);
			m_MainThread->StartMainThread();

			m_RenderThread = new RenderThread(m_DoublueQueue);
			m_RenderThread->StartRenderThread();
		}

	private:
		MainThread*						m_MainThread;
		RenderThread*					m_RenderThread;
		ThreadDoubleQueue*				m_DoublueQueue;
	};
}
