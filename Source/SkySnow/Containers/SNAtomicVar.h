//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by sunguoqiang(SunGQ1987),wangcan(crygl),
//							 liuqian(SkySnow),zhangshuangxue(Calence)
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
#pragma once
#include <atomic>

namespace SkySnow
{
	//ԭ�Ӳ���������
	//ԭ��������acquire����memory_order_acquire��
	//ԭ�Ӵ洢��release����memory_order_release��ԭ�ӵĶ����޸ģ�д�����ǻ�ȡ��
	//�ͷŻ������߼���memory_order_acq_rel
	class AtomicCount
	{
	public:
		//-------------------------------------------------------------
		//fetch_add���ú�����ԭ�Ӷ����װ��ֵ����v��ͬʱ����ԭ�Ӷ���ľ�ֵ
		int Add(std::memory_order mb)
		{
			return m_Count.fetch_add(1,mb) + 1;
		}
		//fetch_sub���ú�����ԭ�Ӷ����װ��ֵ��ȥv��ͬʱ����ԭ�Ӷ���ľ�ֵ
		int Release(std::memory_order mb)
		{
			return m_Count.fetch_sub(1, mb) - 1;
		}
		//-------------------------------------------------------------
		//��������ֵ�󷵻ر�����ֵǰ��ֵ��exchangeҲ��Ϊread-modify-write����
		bool Mark(std::memory_order mb)
		{
			return m_Mark.exchange(true,mb);
		}
		bool UnMark(std::memory_order mb)
		{
			bool origin = m_Mark.exchange(false,mb);
			return origin;
		}
		//-------------------------------------------------------------
		//load��ȡԭ�ӱ�����ֵ��operator T��load�ļ򻯰汾���ڲ����õ���load(memory_order_seq_cst)��ʽ
		bool IsCanDelete()
		{
			if (m_Count.load(std::memory_order_relaxed) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool IsValid(std::memory_order mb)
		{
			return !m_Mark.load(mb) && m_Count.load(mb) > 0;
		}
		//-------------------------------------------------------------
		int GetCountRef(std::memory_order mb)
		{
			return m_Count.load(mb);
		}
	private:
		std::atomic_int m_Count = { 0 };
		std::atomic_bool m_Mark = { 0 };
	};
}