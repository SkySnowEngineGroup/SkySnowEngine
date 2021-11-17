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
#include "GRI_T.h"
#include "ThreadMutex.h"
class Engine_T
{
public:
	Engine_T()
		: m_GRI_T(nullptr)
	{
	}

	virtual ~Engine_T()
	{
	}

	void Initial()
	{
		m_GRI_T = new GRI_T();
		m_GRI_T->Initial();
	}

	void EngineUpdate()
	{
		m_LockPrint.Lock();
		NUWALOGI("MainThread is Running================================.\n");
		m_LockPrint.UnLock();
		m_GRI_T->EngineThreadWriteData();
	}

	void RenderUpdate()
	{
		m_LockPrint.Lock();
		NUWALOGI("RenderThread is Running================================.\n");
		m_LockPrint.UnLock();
		m_GRI_T->RenderThreadReadData();
		m_GRI_T->Update();
	}
private:
	GRI_T* m_GRI_T;
	Nuwa::ThreadMutex		m_LockPrint;
};