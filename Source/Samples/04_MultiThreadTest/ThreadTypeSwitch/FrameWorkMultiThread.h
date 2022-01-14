//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
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
#include "DoubleQueueTest.h"
namespace ThreadMultiRender
{
	enum MRTType
	{
		DQ_MRT,//双队列帧同步
		PQ_MRT,//管道
		CQ_MRT //环形队列
	};
	class MTRFrameWork
	{
	public:
		MTRFrameWork(MRTType mrtType = DQ_MRT)
			: m_MRTType(mrtType)
		{
		}

		virtual ~MTRFrameWork()
		{
			if (m_Edq)
			{
				delete m_Edq;
				m_Edq = nullptr;
			}
		}

		void Initial()
		{
			if (m_MRTType == DQ_MRT)//双队列帧同步
			{
				m_Edq = new ThreadMultiRender::Engine_DoubleQueue();
				m_Edq->Initial();
			}
			else if(m_MRTType == PQ_MRT)//管道
			{

			}
			else if (m_MRTType == CQ_MRT)//环形队列
			{

			}
		}

	private:
		MRTType									m_MRTType;
		ThreadMultiRender::Engine_DoubleQueue*	m_Edq;
		
	};
}