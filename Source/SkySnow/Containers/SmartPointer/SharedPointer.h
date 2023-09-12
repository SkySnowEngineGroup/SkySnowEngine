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
#include "Reference.h"
#include "LogAssert.h"
namespace SkySnow
{

	template<typename T>
	class SharedPtr
	{
	public:
		SharedPtr() noexcept
			: _Ptr(nullptr)
		{
		}

		SharedPtr(std::nullptr_t) noexcept
			: _Ptr(nullptr)
			, _Counter(nullptr)
		{
		}

		SharedPtr(T* ptr) noexcept
		{
			if (ptr)
			{
				_Ptr = ptr;
				_Counter = new RefCount();
				_Counter->Init();
			}
		}

		SharedPtr(const SharedPtr<T>& other) noexcept
		{
			_Ptr = nullptr;
			_Counter = nullptr;

			Add(other);
		}

		SharedPtr(SharedPtr<T>&& rhs) noexcept
		{
			_Ptr = nullptr;
			_Counter = nullptr;

			Add(rhs);
		}

		template <typename U>
		inline SharedPtr(const SharedPtr<U>& moving) noexcept
		{
			U* movingPtr = moving.Get();

			T* castPointer = static_cast<T*>(movingPtr);

			Release();

			if (castPointer != nullptr)
			{
				if (moving.Get() == _Ptr)
					return;

				if (moving.GetCounter() && moving.Get())
				{
					_Ptr = castPointer;
					_Counter = moving.GetCounter();
					_Counter->Release();
				}
			}
			else
			{
				SN_ERR("Failed to cast Reference");
			}
		}

		~SharedPtr() noexcept
		{
			Release();
		}

		inline T* Get() const
		{
			return _Ptr;
		}

		inline RefCount* GetCounter() const
		{
			return _Counter;
		}

		inline void Reset(T* p_ptr = nullptr)
		{
			Release();

			_Ptr = p_ptr;
			_Counter = nullptr;

			if (_Ptr != nullptr)
			{
				_Counter = new RefCount();
				_Counter->Init();
			}
		}

		inline void operator=(SharedPtr const& rhs)
		{
			Add(rhs);
		}

		inline SharedPtr& operator=(SharedPtr&& rhs) noexcept
		{
			Add(rhs);
			return *this;
		}

		inline SharedPtr& operator=(T* newData)
		{
			Reset(newData);
			return *this;
		}

		template <typename U>
		inline SharedPtr& operator=(const SharedPtr<U>& moving)
		{
			U* movingPtr = moving.Get();

			T* castPointer = dynamic_cast<T*>(movingPtr);

			Release();

			if (castPointer != nullptr)
			{
				if (moving.GetCounter() && moving.Get())
				{
					_Ptr = moving.get();
					_Counter = moving.GetCounter();
					_Counter->Add();
				}
			}
			else
			{
				SN_ERR("Failed to cast Reference");
			}

			return *this;
		}

		inline operator T* () const
		{
			return _Ptr;
		}

		inline SharedPtr& operator=(std::nullptr_t)
		{
			Reset();
			return *this;
		}

		// Const correct access owned object
		inline T* operator->() const
		{
			return &*_Ptr;
		}
		inline T& operator*() const
		{
			return *_Ptr;
		}

		inline T& operator[](int index)
		{
			return _Ptr[index];
		}

		inline explicit constexpr operator bool() const
		{
			return _Ptr != nullptr;
		}

		inline constexpr bool operator==(const T* p_ptr) const
		{
			return _Ptr == p_ptr;
		}
		inline constexpr bool operator!=(const T* p_ptr) const
		{
			return _Ptr != p_ptr;
		}
		inline constexpr bool operator<(const SharedPtr<T>& p_r) const
		{
			return _Ptr < p_r._Ptr;
		}
		inline constexpr bool operator==(const SharedPtr<T>& p_r) const
		{
			return _Ptr == p_r._Ptr;
		}
		inline constexpr bool operator!=(const SharedPtr<T>& p_r) const
		{
			return _Ptr != p_r._Ptr;
		}

		inline void swap(SharedPtr& other) noexcept
		{
			std::swap(_Ptr, other._Ptr);
			std::swap(_Counter, other._Counter);
		}

		template <typename U>
		inline SharedPtr<U> As() const
		{
			return SharedPtr<U>(*this);
		}
	private:
		inline void Add(const SharedPtr& inSPtr)
		{
			if (inSPtr._Ptr == _Ptr)
				return;

			Release();

			_Counter = nullptr;
			_Ptr = nullptr;

			if (inSPtr.GetCounter() && inSPtr.Get())
			{
				_Ptr	 = inSPtr.Get();
				_Counter = inSPtr.GetCounter();
				_Counter->Add();
			}
		}

		inline void Release()
		{
			if (_Counter != nullptr)
			{
				if (_Counter->Release())
				{
					delete _Ptr;

					if (_Counter->GetWeakRefCount() == 0)
					{
						delete _Counter;
					}

					_Ptr = nullptr;
					_Counter = nullptr;
				}
			}
		}
	private:
		RefCount*	_Counter = nullptr;
		T*			_Ptr = nullptr;
	};
}
