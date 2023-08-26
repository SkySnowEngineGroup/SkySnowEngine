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
#include "Reference.h"

namespace SkySnow
{
    RefCount::RefCount()
    {
        _Refcount.Init();
        _RefcountInit.Init();
        _WeakRefcount.Init(0);
    }

    RefCount::~RefCount()
    {

    }

    bool RefCount::Init()
    {
        if (Add())
        {
            if (_RefcountInit.Get() > 0)
            {
                _RefcountInit.Unref();
                Release(); // first referencing is already 1, so compensate for the ref above
            }

            return true;
        }
        else
        {

            return false;
        }
    }

    //Return false at count is zero
    bool RefCount::Add()
    {
        return _Refcount.SharedPtr();
    }

    bool RefCount::Release()
    {
        return _Refcount.Unref();
    }

    bool RefCount::WeakAdd()
    {
        return _WeakRefcount.SharedPtr();
    }
    bool RefCount::WeakRelease()
    {
        return _WeakRefcount.Unref() && _WeakRefcount._Count == 0;
    }

    int RefCount::GetRefCount() const
    {
        return _Refcount.Get();
    }
    int RefCount::GetWeakRefCount() const
    {
        return _WeakRefcount.Get();
    }
}
