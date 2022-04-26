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
int main()
{
	SN_LOG("Hello World!\n");

	TestAddFile* td1 = new TestAddFile();
	SN_LOG("No MemoryPool Demo Test td1:%p", td1);
	TestAddFile* td2 = new TestAddFile();
	SN_LOG("No MemoryPool Demo Test td2:%p", td2);
	delete td1;
	TestAddFile* td3 = new TestAddFile();
	SN_LOG("No MemoryPool Demo Test td3:%p", td3);
	delete td2;
	TestAddFile* td4 = new TestAddFile();
	SN_LOG("No MemoryPool Demo Test td3:%p", td4);
	delete td3;
	delete td4;

	HelloWorld* hw1 = new HelloWorld();
	SN_LOG("MemoryPool Demo Test hw1:%p",hw1);

	HelloWorld* hw2 = new HelloWorld();
	SN_LOG("MemoryPool Demo Test hw2:%p", hw2);
	delete hw1;

	HelloWorld* hw3 = new HelloWorld();
	SN_LOG("MemoryPool Demo Test hw3:%p", hw3);

	delete hw2;
	delete hw3;
	system("pause");
	return 0;
}