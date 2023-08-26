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
	template <typename T>
	class UniquePtr
	{
	public:
        explicit UniquePtr(std::nullptr_t)
        {
            _Ptr = nullptr;
        }

        UniquePtr(T* ptr = nullptr)
        {
            _Ptr = ptr;
        }

        template <typename U>
        explicit UniquePtr(U* ptr)
        {
            _Ptr = dynamic_cast<T*>(ptr);
        }

        ~UniquePtr()
        {
            delete _Ptr;
        }

        UniquePtr(UniquePtr const&) = delete;
        UniquePtr& operator=(UniquePtr const&) = delete;

        inline UniquePtr(UniquePtr&& moving) noexcept
        {
            moving.Swap(*this);
        }

        inline UniquePtr& operator=(UniquePtr&& moving) noexcept
        {
            moving.Swap(*this);
            return *this;
        }

        template <typename U>
        inline UniquePtr(UniquePtr<U>&& moving)
        {
            UniquePtr<T> tmp(moving.Release());
            tmp.Swap(*this);
        }
        template <typename U>
        inline UniquePtr& operator=(UniquePtr<U>&& moving)
        {
            UniquePtr<T> tmp(moving.Release());
            tmp.Swap(*this);
            return *this;
        }

        inline UniquePtr& operator=(std::nullptr_t)
        {
            Reset();
            return *this;
        }

        T* operator->() const
        {
            return _Ptr;
        }
        T& operator*() const
        {
            return *_Ptr;
        }

        T* Get() const
        {
            return _Ptr;
        }
        explicit operator bool() const
        {
            return _Ptr;
        }

        inline T* Release()
        {
            T* result = nullptr;
            std::swap(result, _Ptr);
            return result;
        }

        inline void Reset()
        {
            T* tmp = Release();
            delete tmp;
        }

        inline void Swap(UniquePtr& src) noexcept
        {
            std::swap(_Ptr, src._Ptr);
        }

    private:
        T* _Ptr = nullptr;
	};
    template <typename T>
    void Swap(UniquePtr<T>& lhs, UniquePtr<T>& rhs) noexcept
    {
        lhs.Swap(rhs);
    }
}