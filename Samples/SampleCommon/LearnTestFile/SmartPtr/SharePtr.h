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
#include "RefCounted.h"
#include "LogAssert.h"
namespace SkySnowLearning
{
    class ResourceRaw : public RefThreadSafeCounted
    {
    public:
        ResourceRaw(){}
        ~ResourceRaw(){}
        
    };
    //测试GRI中Handle的用法是否存在逻辑漏洞，测试结果来看是存在逻辑漏洞
    void TestSharePtr()
    {
        RefCountPtr<ResourceRaw> ptr1 = new ResourceRaw();
        SN_LOG("ptr1 Count:%d",ptr1.GetRefCount());
        
        ResourceRaw* ptr2 = ptr1.GetReference();
        SN_LOG("ptr2 Count:%d",ptr2->RefCount());
        
        RefCountPtr<ResourceRaw> ptr3 = ptr2;
        SN_LOG("ptr3 Count:%d",ptr3.GetRefCount());
    }
}
