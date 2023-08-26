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
#include "SharedPointer.h"
namespace SkySnow
{
	template <typename T>
	class WeakPtr
	{
	public:
        WeakPtr() noexcept
            : _Ptr(nullptr)
            , _Counter(nullptr)
        {
        }

        WeakPtr(std::nullptr_t) noexcept
            : _Ptr(nullptr)
            , _Counter(nullptr)
        {
        }

        WeakPtr(const WeakPtr<T>& rhs) noexcept
            : _Ptr(rhs.m_Ptr)
            , _Counter(rhs._Counter)
        {
            Add();
        }

        explicit WeakPtr(T* ptr) noexcept
            : _Ptr(ptr)
        {
            _Counter = new RefCount();
            _Counter->WeakAdd();
        }

        template <class U>
        WeakPtr(const WeakPtr<U>& rhs) noexcept
            : _Ptr(rhs._Ptr)
            , _Counter(rhs._Counter)
        {
            Add();
        }

        WeakPtr(const SharedPtr<T>& rhs) noexcept
            : _Ptr(rhs.Get())
            , _Counter(rhs._Counter)
        {
            Add();
        }

        ~WeakPtr() noexcept
        {
            if (_Counter->WeakRelease())
            {
                delete _Ptr;
            }
        }

		void Add()
		{
			_Counter->WeakAdd();
		}

		bool IsReference() const
		{
			return _Counter ? _Counter->GetRefCount() <= 0 : true;
		}

        SharedPtr<T> Lock() const
        {
            if (IsReference())
                return SharedPtr<T>();
            else
                return SharedPtr<T>(_Ptr);
        }

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

        inline explicit operator bool() const
        {
            return _Ptr != nullptr;
        }
        inline bool operator==(const T* p_ptr) const
        {
            return _Ptr == p_ptr;
        }
        inline bool operator!=(const T* p_ptr) const
        {
            return _Ptr != p_ptr;
        }
        inline bool operator<(const WeakPtr<T>& p_r) const
        {
            return _Ptr < p_r._Ptr;
        }
        inline bool operator==(const WeakPtr<T>& p_r) const
        {
            return _Ptr == p_r._Ptr;
        }
        inline bool operator!=(const WeakPtr<T>& p_r) const
        {
            return _Ptr != p_r._Ptr;
        }
	private:
		T*			_Ptr;
		RefCount*	_Counter = nullptr;
	};
}