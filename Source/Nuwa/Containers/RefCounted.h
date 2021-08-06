//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
// Open source is written by wangcan(crygl)��liuqian(SkySnow)��zhangshuangxue(Calence)
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
namespace Nuwa
{
	template <typename Referenced>
	class RefCountPtr
	{
		typedef Referenced* ReferencedPtr;
	public:

		RefCountPtr()
		: m_Referenced(nullptr)
		{
		}

		RefCountPtr(const RefCountPtr& inputCopy)
		{
			m_Referenced = inputCopy;
			if (m_Referenced)
			{
				m_Referenced->Add();
			}
		}

		RefCountPtr(RefCountPtr&& inputMove)
		{
			m_Referenced = inputMove.m_Referenced;
			inputMove.m_Referenced = nullptr;
		}

		template<typename CloneReferenced>
		explicit RefCountPtr(const RefCountPtr<CloneReferenced>& inputClone)
		{
			m_Referenced = static_cast<m_Referenced*>(inputClone.GetReference());
			if (m_Referenced)
			{
				m_Referenced->Add();
			}
		}

		template<typename MoveReferenced>
		explicit RefCountPtr(RefCountPtr<MoveReferenced>&& inputMove)
		{
			m_Referenced = static_cast<Referenced*>(inputMove.GetReference());
			inputMove.m_Referenced = nullptr;
		}

		~RefCountPtr()
		{
			if (m_Referenced)
			{
				m_Referenced->Release();
			}
		}

		RefCountPtr& operator=(Referenced* inputRef)
		{
			Referenced* originRef = m_Referenced;
			m_Referenced = inputRef;
			if (m_Referenced)
			{
				m_Referenced->Add();
			}
			if (originRef)
			{
				originRef->Release();
			}
			return *this;
		}

		inline RefCountPtr& operator=(const RefCountPtr& inpurRef)
		{
			return *this = inpurRef.m_Referenced;
		}

		template<typename CloneReferenced>
		inline RefCountPtr& operator=(const RefCountPtr<CloneReferenced>& inputRef)
		{
			return *this = inputRef.GetReference();
		}

		RefCountPtr& operator=(RefCountPtr&& inputPtr)
		{
			if (this != &inputPtr)
			{
				Referenced originRef = m_Referenced;
				m_Referenced = inputPtr.m_Referenced;
				inputPtr.m_Referenced = nullptr;
				if (originRef)
				{
					originRef->Release();
				}
			}
			return *this;
		}

		inline Referenced* operator->()const
		{
			return m_Referenced;
		}

		inline operator Referenced() const
		{
			return m_Referenced;
		}

		inline bool IsNull()const
		{
			return m_Referenced != nullptr;
		}

		inline bool IsNullRef(const RefCountPtr& inputRef)
		{
			return inputRef.m_Referenced != nullptr;
		}

		inline Referenced* GetReference()
		{
			return m_Referenced;
		}

		int32_t GetRefCount()
		{
			int32_t count = 0;
			if (m_Referenced)
			{
				count = m_Referenced->RefCount();
			}
			return count;
		}

		inline void Swap(RefCountPtr& inputPtr)
		{
			ReferencedPtr* originRef = m_Referenced;
			m_Referenced = inputPtr.m_Referenced;
			inputPtr.m_Referenced = originRef;
		}
	private:
		ReferencedPtr* m_Referenced;
		template <typename U> friend class RefCountPtr;
	};

	template<typename Referenced>
	inline bool operator==(const RefCountPtr<Referenced>& lhs, const RefCountPtr<Referenced>& rhs)
	{
		return lhs.GetReference() == rhs.GetReference();
	}

	template<typename Referenced>
	inline bool operator==(const RefCountPtr<Referenced>& lhs, Referenced* rhs)
	{
		return lhs.GetReference() == rhs;
	}

	template<typename Referenced>
	inline bool operator==(Referenced* lhs, const RefCountPtr<Referenced>& rhs)
	{
		return lhs == rhs.GetReference();
	}

	//If you want your class to be automatically reclaimed, inherit the class Use as RefCountPtr<XXX>
	//refcount base,thread not safe
	class RefCounted
	{
	public:
		RefCounted();

		virtual ~RefCounted();

		RefCounted(const RefCounted& rhs) = delete;

		RefCounted& operator =(const RefCounted& rhs) = delete;

		void Add();

		void Release();

		int RefCount()const;
	private:
		int32_t m_refs;
	};
	//use atomic refcount
	//thread safe
	class RefThreadSafeCounted
	{
	public:
		RefThreadSafeCounted();

		virtual ~RefThreadSafeCounted();
		
		RefThreadSafeCounted(const RefThreadSafeCounted& rhs) = delete;
		
		RefThreadSafeCounted& operator =(const RefThreadSafeCounted& rhs) = delete;

		void Add();

		void Release();

		int RefCount()const;
	private:
		std::atomic<int32_t> m_refs;
	};
}