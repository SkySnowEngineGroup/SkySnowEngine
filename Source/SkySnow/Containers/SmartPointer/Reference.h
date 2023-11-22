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
#include <stdint.h>
#include <atomic>
#include "LogAssert.h"
namespace SkySnow
{
    struct SafeCounter
    {
    public:
        inline bool SharedPtr()
        {
            _Count++;
            return _Count != 0;
        }

        inline int RefValue()
        {
            _Count++;
            return _Count;
        }

        inline bool Unref()
        {
            --_Count;
            bool del = _Count == 0;
            return del;
        }

        inline int Get() const
        {
            return _Count;
        }

        inline void Init(int value = 1)
        {
            _Count = value;
        }
       
        SafeCounter()
            : _Count(0)
        {
        }
    public:
        std::atomic_int _Count = {0};
    };

    class RefCount
    {
    public:
        RefCount();
        ~RefCount();

        inline bool IsDelete() const
        {
            return _RefcountInit.Get() < 1;
        }
        bool Init();

        //Return false at count is zero
        bool Add();
        bool Release();

        bool WeakAdd();
        bool WeakRelease();

        int GetRefCount() const;
        int GetWeakRefCount() const;

    private:
        SafeCounter _Refcount;
        SafeCounter _RefcountInit;
        SafeCounter _WeakRefcount;
    };
}
