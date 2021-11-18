//
// Copyright (c) 2020-2022 the PhoneixEngine project.
// Open source is written by liuqian(SkySnow)��zhangshuangxue(Calence)
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
#include "ThreadSemaphore.h"
#include "ThreadMutex.h"
namespace DoubleQueue
{
	class ThreadDoubleQueue
	{
	public:
		ThreadDoubleQueue()
			: m_EncoderList(0)
			, m_RenderList(0)
		{
		}

		virtual ~ThreadDoubleQueue()
		{
		}

		void Swap(float lhs,float rhs)
		{
			float temp = lhs;
			lhs = rhs;
			rhs = lhs;
		}
		//MainThread call this function
		void EngineUpdate()
		{
			BeginRender();
			//Submit Render CMD
			m_EncoderList += 1;
			m_PrintMutex.Lock();
			NUWALOGI("MainThread=================================:%f", m_EncoderList);
			m_PrintMutex.UnLock();
			Present();
		}
		//������Ⱦ�߳�
		void BeginRender()
		{
			m_RenderSem.Signal();
		}
		//�ȴ���Ⱦ�߳���Ⱦ��ϣ������������
		void Present()
		{
			m_MainSem.WaitForSignal();
			//Swap(m_EncoderList,m_RenderList);
			float temp = m_EncoderList;
			m_EncoderList = m_RenderList;
			m_RenderList = temp;
		}
		//RenderThread Call this function
		void RenderOneFrame()
		{
			m_RenderSem.WaitForSignal();
			//vlm_RenderList = 2;
			m_PrintMutex.Lock();
			NUWALOGI("RenderThread===:%f", m_RenderList);
			m_PrintMutex.UnLock();
			SimulationBusy();
			m_MainSem.Signal();
		}
	private:
		void SimulationBusy()
		{
			Sleep(3000);
			for (int i = 0; i < 10000000; i++)
			{
				float value = 10 * 20 * 4.234 * 2341;
			}
		}
	private:
		Nuwa::ThreadSemaphore	m_MainSem;
		Nuwa::ThreadSemaphore	m_RenderSem;
		float					m_EncoderList;
		float					m_RenderList;
		Nuwa::ThreadMutex		m_PrintMutex;
	};
}