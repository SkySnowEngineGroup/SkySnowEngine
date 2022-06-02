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
	//��ռָ��
	template<typename T>
	class unique_ptr
	{
	public:
		//explicit ��ֹ��ʽת��
		//std::move�ǽ������״̬��һ������ת�Ƶ�����һ������
		//û�п�����ֵ������raw_ptr���ƶ�������ָ����ǿ�
		//noxecept��c++���쳣���ϱ���ǣ���Ǻ󽫲���Ҫ��Runtimeʱ�ϱ�
		//C++���쳣��������Runtimeʱ���������ڱ����ڴ���
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
		//��ռָ����ֻ������ӵ�У�����ת������Ȩ
		//����������Ʋ�����������û�п������캯���븳ֵ������
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
		//���û�����ʲô��˼
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
	//Share_ptr ���ü�������ָ��
	template<typename T>
	class share_ptr
	{
	public:

	private:
	};

}