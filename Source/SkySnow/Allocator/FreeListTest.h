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

//Note:这是一些需要考虑的实际问题，想要一个灵活及性能及内存都良好的内存管理，需要针对不同业务场景以及各种实现方式进行处理
//This is an example of a memory pool. The real engine can't be so simple. 
//It's just a simple review of some basic concepts of memory pools.
//This is a simple freelist method. The real engine is definitely not such a simple method.
//Multiple business scenarios must be considered
//1. and multi-threaded access conflicts and efficiency issues (minimum locks and thread local variables) must be considered.
//2. Address shaders Offset avoids the problem of inefficient cacheline (processing an offset during allocation),
//3. considers the memory shrinking scheme (Slab processing method), 
//4. and needs to deal with the situation where multiple CPUs access the same cache in the case of multi-core (paging processing)

//According to the usage scenarios of the engine, various implementation schemes of memory allocation need to be considered.
//1. Linear memory allocation; it is linear growth, suitable for the processing of rendering state dataand skeletal animation data of each frame, and it is easy to support lockfreeand index increment operations
//2. Stack allocator; suitable for level resource loading, can be released on demand, as the backend of other allocators
//3. Freelist allocation is suitable for particle effect buffer pool, but its memory is not continuous, which will cause cache_lineand multiple CPUs to access the same cached data, which should be considered
//4. Buddy allocation(伙伴分配器), automatic merging, can handle continuous multi - frame GPU memory management
//5. Thread - safe memory pool, suitable for multi - threaded processing
//And so on, these situations need to be taken into account
#pragma once
#include <iostream>
using namespace std;
namespace SkySnow
{
	template<int ObjSize, int NumObj = 10>
	class FreeListTest
	{
	private:
		struct FreeNode
		{
			FreeNode*	m_Next;
			char		m_Data[ObjSize];
		};

		struct MemoryBlock
		{
			MemoryBlock*	m_Next;
			FreeNode		m_Data[NumObj];
		};

	public:
		FreeListTest()
			: m_FreeNodeHeader(nullptr)
			, m_MemoryBlockHeader(nullptr)
		{
		}

		~FreeListTest()
		{
			MemoryBlock* ptr;
			while (m_MemoryBlockHeader)
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
	void* FreeListTest<ObjSize, NumObj>::Malloc()
	{
		if (m_FreeNodeHeader == nullptr)
		{
			MemoryBlock* newBlock = new MemoryBlock();
			newBlock->m_Next = nullptr;
			m_FreeNodeHeader = &newBlock->m_Data[0];

			for (int i = 1; i < NumObj; i++)
			{
				newBlock->m_Data[i - 1].m_Next = &newBlock->m_Data[i];
			}
			newBlock->m_Data[NumObj - 1].m_Next = nullptr;

			if (m_MemoryBlockHeader == nullptr)
			{
				m_MemoryBlockHeader = newBlock;
			}
			else
			{
				newBlock->m_Next = m_MemoryBlockHeader;
				m_MemoryBlockHeader = newBlock;
			}
		}

		void* freeNode = m_FreeNodeHeader;
		m_FreeNodeHeader = m_FreeNodeHeader->m_Next;
		return freeNode;
	}

	template<int ObjSize, int NumObj>
	void FreeListTest<ObjSize, NumObj>::Free(void* ptr)
	{
		FreeNode* pNode = (FreeNode*)ptr;
		pNode->m_Next = m_FreeNodeHeader;
		m_FreeNodeHeader = pNode;
	}
}
