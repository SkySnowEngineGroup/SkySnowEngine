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
#include "RefCounted.h"
#include "Reference.h"
#include "SharedPointer.h"
#include "WeakPtr.h"
#include "UniquePtr.h"
namespace SkySnow
{
    //RefCounted use for gri,resource recycle(flushResource)
#if Use_Smart_Ptr
    //Shared pointer
    template <class T>
    using SPtr = SharedPtr<T>;

    template <typename T, typename... Args>
    SPtr<T> CreateSPtr(Args&&... args)
    {
        auto ptr = new T(std::forward<Args>(args)...);

        return SPtr<T>(ptr);
    }
    //Weak Pointer
    template <class T>
    using WPtr = WeakPtr<T>;

    //Unique Pointer
    template <class T>
    using UPtr = UniquePtr<T>;

    template <typename T, typename... Args>
    UPtr<T> CreateUPtr(Args&&... args)
    {
        auto ptr = new T(std::forward<Args>(args)...);
        return UPtr<T>(ptr);
    }
#else
    template <class T>
    using SPtr = std::shared_ptr<T>;

    template <typename T, typename... Args>
    SPtr<T> CreateSPtr(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <class T>
    using WPtr = std::weak_ptr<T>;

    template <class T>
    using UPtr = std::unique_ptr<T>;

    template <typename T, typename... Args>
    UPtr<T> CreateUPtr(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

#endif
}

#if Use_Smart_Ptr
namespace std
{
    template <typename T>
    struct hash<SkySnow::SharedPtr<T>>
    {
        size_t operator()(const SkySnow::SharedPtr<T>& x) const
        {
            return hash<T*>()(x.Get());
        }
    };
}
#endif