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
//

#include "Data.h"

namespace SkySnow
{
	Data::Data()
		: m_Bytes(nullptr)
		, m_Size(0)
	{
	}

	Data::~Data()
	{
		Clear();
	}

	Data::Data(const Data& other)
		: m_Bytes(nullptr)
		, m_Size(0)
	{
		Copy(other.m_Bytes,other.m_Size);
	}

	Data& Data::operator=(const Data& other)
	{
		if (this != &other)
		{
			Copy(other.m_Bytes,m_Size);
		}
		return *this;
	}

	Data::Data(Data&& other) noexcept
		: m_Bytes(nullptr)
		, m_Size(0)
	{
		Move(other);
	}

	Data& Data::operator=(Data&& other) noexcept
	{
		if (this != &other)
		{
			Move(other);
		}
		return *this;
	}

	void Data::SetBytes(unsigned char* bytes, const size_t size)
	{
		m_Bytes = bytes;
		m_Size = size;
	}

	unsigned char* Data::GetBytes() const
	{
		return m_Bytes;
	}

	size_t Data::GetSize() const
	{
		return m_Size;
	}

	bool Data::IsNull() const
	{
		return m_Bytes == nullptr || m_Size == 0;
	}

	void Data::Clear()
	{
		if (m_Bytes)
		{
			free(m_Bytes);
			m_Bytes = nullptr;
			m_Size = 0;
		}
	}
	void Data::Move(Data& other)
	{
		Clear();
		m_Bytes = other.m_Bytes;
		m_Size = other.m_Size;
		other.m_Bytes = nullptr;
		other.m_Size = 0;
	}

	void Data::Copy(const unsigned char* bytes, const size_t size)
	{
		Clear();
		if (size > 0)
		{
			m_Size = size;
			m_Bytes = (unsigned char*)malloc(sizeof(unsigned char) *( m_Size));
			memcpy(m_Bytes,bytes,m_Size);
		}
	}
}