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
#include <utility>
#include <iostream>
namespace SkySnowLearning
{
	//独占指针
	template<typename T>
	class unique_ptr
	{
	public:
		//explicit 防止隐式转换
		//std::move是将对象的状态从一个对象转移到另外一个对象，
		//没有拷贝赋值操作，raw_ptr被移动后，其所指向的是空
		//noxecept是c++的异常不上报标记，标记后将不需要再Runtime时上报
		//C++的异常处理是在Runtime时处理，不是在编译期处理
		explicit unique_ptr(T* raw_ptr)noexcept
			: m_Ptr(std::move(raw_ptr))
		{
		}
		unique_ptr(std::nullptr_t) noexcept
			: m_Ptr(nullptr)
		{
		}

		~unique_ptr() noexcept
		{
			if (m_Ptr)
			{
				delete m_Ptr;
				m_Ptr = nullptr;
			}
		}
		//独占指针是只能自已拥有，或者转移所有权
		//因此其有右移操作符，但是没有拷贝构造函数与赋值操作符
		unique_ptr(const unique_ptr<T>& raw_ptr) noexcept = delete;

		unique_ptr& operator = (const unique_ptr<T>& raw_ptr) noexcept = delete;

		unique_ptr(unique_ptr<T>&& other) noexcept
		{
			other.swap(*this);
		}

		void swap(unique_ptr<T>& other) noexcept
		{
			std::swap(m_Ptr, other.m_Ptr);
		}
		//这个没理解是什么意思
		explicit operator bool() const noexcept
		{
			return this->m_Ptr;
		}

		T* Release() noexcept
		{
			return std::exchange(m_Ptr,nullptr);
		}

		T* Get() const noexcept
		{
			return m_Ptr;
		}

		void Reset(T* raw_ptr) noexcept
		{
			if(raw_ptr == nullptr)
				throw std::invalid_argument("An invalid pointer was passed, resources will not be swapped");

			delete raw_ptr;
			raw_ptr = nullptr;

			std::swap(m_Ptr,raw_ptr);
		}

		T* operator->() const noexcept
		{
			return this->m_Ptr;
		}

		T& operator*() const noexcept
		{
			return *this->m_Ptr;
		}
	private:
		T* m_Ptr;
	};
	//Share_ptr 引用计数智能指针
	template<typename T>
	class share_ptr
	{
	public:

	private:
	};

}