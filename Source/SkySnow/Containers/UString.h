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
#include "SkySnowConfigInfo.h"
#include <stdlib.h>
#include <string>
namespace SkySnow
{
	//U is Util
	class UString
	{
	public:
		UString() noexcept
			: _Length(0)
			, _Capacity(0)
			, _Buffer(&g_Null_Char)
		{
		}
		//Destruct
		~UString()
		{
			if (_Capacity)
				delete[] _Buffer;
		}
		//Copy Construct
		UString(const UString& other)
			: _Length(0)
			, _Capacity(0)
			, _Buffer(&g_Null_Char)
		{
			*this = other;
		}
		//Move Construct
		UString(UString&& other)noexcept
			: _Length(0)
			, _Capacity(0)
			, _Buffer(&g_Null_Char)
		{
			Swap(_Length,other._Length);
			Swap(_Capacity,other._Capacity);
			Swap(_Buffer,other._Buffer);
		}
		//assign = String
		UString& operator =(const UString& other)
		{
			if (&other != this)
			{
				Resize(other._Length);
				CopyData(_Buffer,other._Buffer,other._Length);
			}
			return *this;
		}
		//Move = String
		UString& operator =(UString&& other)noexcept
		{
			Swap(_Length,other._Length);
			Swap(_Capacity,other._Capacity);
			Swap(_Buffer,other._Buffer);
			return *this;
		}

		//Assign = char
		UString& operator =(const char* other)
		{
			unsigned length = strlen(other);
			Resize(length);
			CopyData(_Buffer,other,length);
			return *this;
		}

		char& operator [](unsigned index)
		{
			return _Buffer[index];
		}
		const char& operator [](unsigned index) const
		{
			return _Buffer[index];
		}
		//Resize char Buffer Size
		void Resize(unsigned length);
		//Reserve Capacity
		void Reserve(unsigned capacity);
		//Swap Two String
		void Swap(UString& other);
	private:
		template<typename T>
		inline void Swap(T& lhs,T& rhs)
		{
			T temp = lhs;
			lhs = rhs;
			rhs = temp;
		}

		void CopyData(char* des,const char* src,unsigned count)
		{
			if (count)
				memcpy(des,src,count);
		}

	private:
		unsigned	_Length;
		unsigned	_Capacity;
		char*		_Buffer;
	};
}