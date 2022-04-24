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

//This is an example of a memory pool. The real engine can't be so simple. 
//It's just a simple review of some basic concepts of memory pools.
#pragma once
#include <iostream>
using namespace std;
namespace SkySnow
{
	template<int ObjSize, int NumObj = 20>
	class MemoryPool
	{
	private:
		struct FreeNode
		{
			FreeNode* m_Next;
			char		m_Data[ObjSize];
		};

		struct MemoryBlock
		{
			MemoryBlock* m_Next;
			FreeNode		m_Data[NumObj];
		};

	public:
		MemoryPool()
			: m_FreeNodeHeader(nullptr)
			, m_MemoryBlockHeader(nullptr)
		{
		}

		~MemoryPool()
		{
			MemoryBlock* ptr;
			while ()
			{
				ptr = m_MemoryBlockHeader->m_Next;
				delete m_MemoryBlockHeader;
				m_MemoryBlockHeader = ptr;
			}
		}
		void* Malloc();
		void Free(void* ptr);
	private:
		FreeNode* m_FreeNodeHeader;
		MemoryBlock* m_MemoryBlockHeader;
	};

	template<int ObjSize, int NumObj>
	void* MemoryPool<ObjSize, NumObj>::Malloc()
	{

	}

	template<int ObjSize, int NumObj>
	void MemoryPool<ObjSize, NumObj>::Free(void* ptr)
	{

	}
}
