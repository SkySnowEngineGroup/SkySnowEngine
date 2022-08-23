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
}