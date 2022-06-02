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
		//constexpr�����ڽ����ݼ�������������������ڼ���
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
	//1. ��Ҫ��һ��Դָ������share_ptr����:��delete����
	//2. ��Ҫ��thisָ���share_ptr����:�൱������1
	//3. С��ѭ����������޷��ͷ��ڴ棬A����share_ptr<B>��B����share_ptr<A>
	//4. ����ʵ�β�Ҫʹ��share_ptr������fun(share_ptr<new int(1)>,funb()),
	//    �������new int��Ȼ�����funb������funb�����쳣��share<int>δ�������ڴ�й©
	//5. Ƕ��ʽ����������Urho3d�еķ�ʽ����Ҫ��Դ����T�ڲ�����share_ptr
	//6. ���Դ������new���ģ���ô���ü���Ϊ0ʱ������delete����ô�����malloc��
	//   ��Ҫ��Ӧfree������Ҫ�趨�Լ����ͷ��ڴ溯��(ʹ��ɾ����)
	//7. �������ʹ��share_ptr����ô���ü�������int*���������Ҫ˼����δ���
	template<typename T>
	class share_ptr
	{
	public:
		constexpr share_ptr() noexcept
		{
		}
		explicit share_ptr(T* raw= nullptr)
			: m_Ptr(raw)
			, m_RefCount(new int(1))
		{
		}

		~share_ptr() noexcept
		{
			Release();
		}

		share_ptr(const share_ptr<T>& other) noexcept
			: m_Ptr(other.m_Ptr)
			,m_RefCount(other.m_RefCount)
		{
			Add();
		}

		share_ptr& operator=(const share_ptr<T>& other) noexcept
		{
			if (this != &other)
			{
				Release();
				m_Ptr = other.m_Ptr;
				m_RefCount = other.m_RefCount;
				Add();
			}
		}

		T* operator->() const noexcept
		{
			return m_Ptr;
		}

		T& operator*() const noexcept
		{
			return *m_Ptr;
		}
		int GetCount() const
		{
			return *(m_RefCount);
		}
	private:
		void Release()
		{
			(*m_RefCount)--;
			if ((*m_RefCount) == 0)
			{
				m_RefCount = 0;
				delete m_Ptr;
				m_Ptr = nullptr;
			}
		}

		void Add()
		{
			(*m_RefCount)++;
		}
	private:
		int*	m_RefCount;
		T*		m_Ptr;
	};

}