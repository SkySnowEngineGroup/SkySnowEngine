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
#include <stdint.h>
#include <string>
using namespace std;
namespace SkySnow
{
	class Data
	{
	public:
		Data();

		~Data();

		//拷贝构造函数
		explicit Data(const Data& other);
		//拷贝赋值函数
		Data& operator=(const Data& other);

		//右移构造函数
		explicit Data(Data&& other) noexcept;
		//右移赋值函数
		Data& operator=(Data&& other) noexcept;

		bool IsNull() const;

		void SetBytes(unsigned char* bytes,const size_t size);

		unsigned char* GetBytes() const;

		size_t GetSize() const;
	private:
		void Clear();
		void Move(Data& other);
		void Copy(const unsigned char* bytes,const size_t size);
	private:
		unsigned char*	m_Bytes;
		size_t			m_Size;

	};
}