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

#include "UString.h"

namespace SkySnow
{
	void UString::Resize(unsigned length)
	{
		if (_Capacity)
		{
			if (length && _Capacity < (length+1))
			{
				//每次增加原来内存大小的一半
				while (_Capacity < (length + 1))
					_Capacity += (_Capacity + 1) >> 1u;
				char* nBuffer = new char[_Capacity];
				if (_Length)
					CopyData(nBuffer, _Buffer, _Length);
				delete[] _Buffer;
				_Buffer = nBuffer;
			}
		}
		else
		{
			if (!length)
				return;
			_Capacity = length + 1;
			if (_Capacity < g_Min_Capacity)
				_Capacity = g_Min_Capacity;
			_Buffer = new char[_Capacity];
			
		}
		_Buffer[length] = '\0';
		_Length = length;
	}

	void UString::Reserve(unsigned capacity)
	{
		if (capacity < _Length + 1)
			capacity = _Length + 1;
		if (capacity == _Capacity)
			return;
		char* nBuffer = new char[capacity];
		CopyData(nBuffer,_Buffer,_Length + 1);
		if (_Capacity)
			delete[] _Buffer;
		_Capacity = capacity;
		_Buffer = nBuffer;
	}
	void UString::Swap(UString& other)
	{
		Swap(_Length,other._Length);
		Swap(_Capacity,other._Capacity);
		Swap(_Buffer,other._Buffer);
	}
	std::vector<UString> UString::Split(char split, bool keepEmpty) const
	{
		return Split(C_Str(), split, keepEmpty);
	}
	std::vector<UString> UString::Split(const char* src, char split, bool keepEmpty)
	{
		std::vector<UString> res;
		const char* srcEnd = src + strlen(src);
		for (const char* curr = src; curr != srcEnd; curr ++)
		{
			if (*curr == split)
			{
				const long long offset_v = curr - src;
				if (offset_v > 0 || keepEmpty)
					res.emplace_back(UString(src, offset_v));
				src = curr + 1;
			}

		}
		const long long offset_v = srcEnd - src;
		if (offset_v > 0 || keepEmpty)
			res.emplace_back(UString(src, offset_v));
		return res;
	}
	unsigned UString::Find(const UString& source, unsigned start, bool isCs) const
	{
		if (!source._Length || source._Length > _Length)
			return NPOS;
		char first = source._Buffer[0];
		//two way
		if (!isCs)
			first = (char)tolower(first);
		for (unsigned i = start;i <= _Length - source._Length; i++)
		{
			char lc = _Buffer[i];
			if (!isCs)
				lc = (char)tolower(lc);
			if (lc == first)
			{
				unsigned skip = NPOS;
				bool found = true;
				for (unsigned j = 1; j < source._Length; j ++)
				{
					lc = _Buffer[i + j];
					char tc = source._Buffer[j];
					if (!isCs)
					{
						lc = (char)tolower(lc);
						tc = (char)tolower(tc);
					}
					if (skip == NPOS && lc == first)
						skip = i + j - 1;
					if (lc != tc)
					{
						found = false;
						if (skip != NPOS)
							i = skip;
						break;
					}
				}
				if (found)
					return i;
			}
		}
		return NPOS;
	}

	unsigned UString::Find(char source, unsigned start, bool isCs) const
	{
		if (isCs)
		{
			for (unsigned i = start;i < _Length; i ++)
			{
				if (_Buffer[i] == source)
					return i;
			}
		}
		else
		{
			source = (char)tolower(source);
			for (unsigned i = start;i < _Length; i++)
			{
				if (_Buffer[i] == source)
					return i;
			}
		}
		return NPOS;
	}

}