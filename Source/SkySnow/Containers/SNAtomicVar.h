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
#pragma once
#include <atomic>

namespace SkySnow
{
	//原子操作计数器
	//原子载入是acquire操作memory_order_acquire，
	//原子存储是release操作memory_order_release，原子的读，修改，写操作是获取，
	//释放或者两者兼有memory_order_acq_rel
	class AtomicCount
	{
	public:
		//-------------------------------------------------------------
		//fetch_add：该函数将原子对象封装的值加上v，同时返回原子对象的旧值
		int Add(std::memory_order mb)
		{
			return m_Count.fetch_add(1,mb) + 1;
		}
		//fetch_sub：该函数将原子对象封装的值减去v，同时返回原子对象的旧值
		int Release(std::memory_order mb)
		{
			return m_Count.fetch_sub(1, mb) - 1;
		}
		//-------------------------------------------------------------
		//交换，赋值后返回变量赋值前的值。exchange也称为read-modify-write操作
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
		//load读取原子变量的值，operator T是load的简化版本，内部调用的是load(memory_order_seq_cst)形式
		bool IsCanDelete()
		{
			if (m_Count.load(std::memory_order_seq_cst) == 0)
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
	class AutomicBool
	{
	public:
		AutomicBool()
		{
		}
		constexpr AutomicBool(bool arg)
			: _Flag(arg)
		{
		}

		operator bool() const
		{
			return _Flag.load();
		}

		bool operator=(bool val)
		{
			_Flag.store(!val);
			return val;
		}

		bool LoadFlag()
		{
			return _Flag.load();
		}

		void ChangeFlag()
		{
			bool val = _Flag.load();
			_Flag.store(!val);
		}
	private:
		AutomicBool(AutomicBool&&) = delete;
		AutomicBool(const AutomicBool&) = delete;
		AutomicBool& operator=(AutomicBool&&) = delete;
		AutomicBool& operator=(const AutomicBool&) = delete;
	private:
		std::atomic_bool _Flag{true};
	};
}