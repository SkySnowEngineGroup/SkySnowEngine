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
#include <stdlib.h>
#include <iostream>
#include "MainThread.h"
#include "RenderThread.h"
#include "Engine_T.h"
#include "pthread.h"

sem_t m_Encoder;
sem_t m_Render;
pthread_mutex_t print_mutex;
int submit = 0;
int render = 0;
void* EngineCMD(void* arg)
{
	while(1)
	{
		sem_wait(&m_Encoder);
		
		
		if (submit < 10000)
		{
			submit ++;
		}
		else 
		{
			submit = 1;
		}
		for (int i = 0; i < 1000000;i ++)
		{
			float q = 10 * 27 * 34.12228 * 128.90;
		}
		pthread_mutex_lock(&print_mutex);
		NUWALOGI("EngineCMD:%d", submit);
		pthread_mutex_unlock(&print_mutex);
		sem_post(&m_Render);
	}
	return nullptr;
}
void swap(int& lhs,int& rhs)
{
	int temp = lhs;
	lhs = rhs;
	rhs = temp;
}
void* RenderCMD(void* arg)
{
	while (1)
	{
		sem_wait(&m_Render);
		swap(submit, render);
		sem_post(&m_Encoder);
		for (int i = 0; i < 1000000;i++)
		{
			float q = 10 * 27 * 34.12228 * 128.90;
		}
		pthread_mutex_lock(&print_mutex);
		NUWALOGI("RenderCMD=========:%d", render);
		pthread_mutex_unlock(&print_mutex);
	}

	return nullptr;
}

int main()
{
	NUWALOGI("Hello World!\n");
	sem_init(&m_Encoder, 0, 1);
	sem_init(&m_Render, 0, 0);
	pthread_mutex_init(&print_mutex, nullptr);

	pthread_t engineId;
	pthread_create(&engineId, NULL, EngineCMD, "MainThread");

	pthread_t renderId;
	pthread_create(&renderId, NULL, RenderCMD, "RenderThread");
	void* estatus;
	pthread_join(engineId, &estatus);

	void* rstatus;
	pthread_join(renderId, &rstatus);

	sem_destroy(&m_Encoder);
	sem_destroy(&m_Render);
	system("pause");

	//Engine_T* m_Engine = new Engine_T();
	//m_Engine->Initial();
	//MainThread* mt = new MainThread(m_Engine);
	//mt->StartMainThread();

	//RenderThread* rt = new RenderThread(m_Engine);
	//rt->StartRenderThread();

	//system("pause");
	//if (mt)
	//{
	//	mt->StopMainThread();
	//	delete mt;
	//	mt = nullptr;
	//}

	//if (rt)
	//{
	//	rt->StopRenderThread();
	//	delete rt;
	//	rt = nullptr;
	//}

	//if (m_Engine)
	//{
	//	delete m_Engine;
	//	m_Engine = nullptr;
	//}
	system("pause");
	return 0;
}