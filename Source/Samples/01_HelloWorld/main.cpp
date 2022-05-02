//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
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
#include <stdlib.h>
#include <iostream>
#include "TestAddFile.h"
#include "HelloWorld.h"
#include "LogAssert.h"
#include "LinearAllocatorTest.h"
#include "FixedAllocatorTest.h"
#include "SerializeTest.h"
#include "RTTITest.h"
using namespace SkySnow;
int main()
{
	SN_LOG("Hello World!\n");

	//以下为基础知识的内存池测试用例
	//测试不使用内存池的内存地址
	{
		TestAddFile* td1 = new TestAddFile();
		SN_LOG("No FreeListTest Demo Test td1:%p", td1);
		TestAddFile* td2 = new TestAddFile();
		SN_LOG("No FreeListTest Demo Test td2:%p", td2);
		delete td1;
		TestAddFile* td3 = new TestAddFile();
		SN_LOG("No FreeListTest Demo Test td3:%p", td3);
		delete td2;
		TestAddFile* td4 = new TestAddFile();
		SN_LOG("No FreeListTest Demo Test td3:%p", td4);
		delete td3;
		delete td4;
	}
	//测试Freelist内存池，这是Demo级别
	{
		HelloWorld* hw1 = new HelloWorld();
		SN_LOG("FreeListTest Demo Test hw1:%p", hw1);
		HelloWorld* hw2 = new HelloWorld();
		SN_LOG("FreeListTest Demo Test hw2:%p", hw2);
		delete hw1;
		HelloWorld* hw3 = new HelloWorld();
		SN_LOG("FreeListTest Demo Test hw3:%p", hw3);
		delete hw2;
		delete hw3;
	}
	//测试线性分配器的正确性，这是Demo级别。
	{
		SkySnow::LinearAllocatorTest lat;
		SkySnow::LinearAllocatorTest::Allocator alloc;
		lat.Init(&alloc, sizeof(TestAddFile));

		void* test1 = lat.Malloc(&alloc, 16);
		SN_LOG("LinearAllocator Test1:%p", test1);

		void* test2 = lat.Malloc(&alloc, 8);
		SN_LOG("LinearAllocator Test2:%p", test2);

		void* test3 = lat.Malloc(&alloc, 16);
		SN_LOG("LinearAllocator Test3:%p", test3);
	}
	//测试固定内存分配器的正确性，这是Demo级别
	{
		SkySnow::FixedAllocator fixedAlloc(1024,sizeof(TestAddFile));

		void* test1 = fixedAlloc.Malloc();
		SN_LOG("FixedAllocator Test1:%p",test1);
		fixedAlloc.Free(test1);

		void* test2 = fixedAlloc.Malloc();
		SN_LOG("FixedAllocator Test2:%p",test2);

		void* test3 = fixedAlloc.Malloc();
		SN_LOG("FixedAllocator Test2:%p", test3);

		void* test4 = fixedAlloc.Malloc();
		SN_LOG("FixedAllocator Test2:%p", test4);
		
	}

	//测试序列化与反序列化的基础原理，这是Demo级别
	{
		SerializeTest* ser = new SerializeTest();
		ser->TestDemo();
		delete ser;
	}
	
	//测试RTTI基础原理，这是demo级别
	{
		TestRTTI* testRtti = new TestRTTI();
		const char* tname = testRtti->GetTypeName();
		SN_LOG("TestRTTI Type Name:%s",tname);
	}

	system("pause");
	return 0;
}