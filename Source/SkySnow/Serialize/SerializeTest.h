//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by sunguoqiang(SunGQ1987),wangcan(crygl),
//							 liuqian(SkySnow),zhangshuangxue(Calence)
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
#include <string>
#include "LogAssert.h"
//Serialize and Deserialize test Demo. study base knowlage
namespace SkySnow
{
	struct TestBase
	{
		std::string name;
		int			age;
	};
	class SerializeTest
	{
	public:
		SerializeTest()
		{
		}

		~SerializeTest()
		{
		}

		int Serialize(const TestBase& test,char out[])
		{
			int count = 0;
			memcpy(out,test.name.c_str(),test.name.length());
			count += test.name.length();
			memcpy(out + count,&test.age,sizeof(int));
			count += sizeof(int);
			return count;
		}

		int Deserialize(TestBase& test,const char* in, int count)
		{
			int offset = 0;
			test.name.append(in,count - sizeof(int));
			offset += test.name.length();
			memcpy(&test.age,in + offset,sizeof(int));
			return 0;
		}

		void TestDemo()
		{
			char buffer[128];
			int count = 0;

			TestBase test1;
			test1.name = "SerializeDemo";
			test1.age = 29;
			count = Serialize(test1,buffer);

			TestBase test2;//RTTI create this object
			Deserialize(test2,buffer,count);//this fun normal use third lib example flatBuffer or protoBuf
			SN_LOG("Deserialize Name is:%s",test2.name.c_str());
			SN_LOG("Deserialize Age is:%d",test2.age);
			
		}
	};
}