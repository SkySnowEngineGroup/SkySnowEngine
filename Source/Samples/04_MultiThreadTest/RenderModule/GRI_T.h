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
#include "LogAssert.h"
#include "ThreadSemaphore.h"
#include "ThreadMutex.h"
#include "LogAssert.h"
class GRI_T
{
public:
	GRI_T()
	{
		m_CMD_List = new float[20];
	}

	virtual ~GRI_T()
	{
		delete m_CMD_List;
		m_CMD_List = nullptr;
	}
	void Initial()
	{
		
	}

	void EngineThreadWriteData()
	{
		for (int i = 0; i < 20;i ++)
		{
			m_CMD_List[i] = 1;
		}
		//m_LockPrint.Lock();
		//for (int i = 0; i < 20;i++)
		//{
		//	NUWALOGI("MainThread Data is:%f\n", m_CMD_List[i]);
		//}
		//m_LockPrint.UnLock();
		m_RenderSem.Signal();
	}

	void RenderThreadReadData()
	{
		m_RenderSem.WaitForSignal();
		for (int i = 0; i < 20;i++)
		{
			m_CMD_List[i] = 2;
		}	
		//m_LockPrint.Lock();
		//for (int i = 0; i < 20;i++)
		//{
		//	NUWALOGI("RenderThread Data is:%f\n", m_CMD_List[i]);
		//}
		//m_LockPrint.UnLock();
	}

	void Update()
	{

	}
private:
	float* m_CMD_List;
	Nuwa::ThreadSemaphore	m_RenderSem;
	Nuwa::ThreadMutex		m_LockPrint;
};