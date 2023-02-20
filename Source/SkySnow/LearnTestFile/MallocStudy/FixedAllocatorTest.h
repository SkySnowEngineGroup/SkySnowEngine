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
#include <malloc.h>
#define FixedMinBlockSize 256
#define MinNodeSize 16
namespace SkySnow
{
	//¹Ì¶¨ÄÚ´æ·ÖÅäÆ÷
	class FixedAllocator
	{
	private:
		struct FixedNode
		{
			FixedNode* m_Next;
		};

		struct FixedBlock
		{
			FixedBlock* m_Next;
		};

	public:
		FixedAllocator(size_t blockSize,size_t nodeSize)
			: m_BlockHeader(nullptr)
			, m_FreeList(nullptr)
		{
			m_BlockSize = blockSize > FixedMinBlockSize ? blockSize : FixedMinBlockSize;
			m_NodeSize = nodeSize > MinNodeSize ? nodeSize : MinNodeSize;
		}

		~FixedAllocator()
		{
			FixedBlock* block = m_BlockHeader;
			FixedBlock* temp;
			while (block)
			{
				temp = block->m_Next;
				free(block);
				block = temp;
			}
		}

		void* Malloc()
		{
			if (m_FreeList == nullptr)
			{
				FixedBlock* block = (FixedBlock*)malloc(m_BlockSize);
				block->m_Next = m_BlockHeader;
				m_BlockHeader = block;

				size_t i = 0;
				size_t size = m_BlockSize - sizeof(FixedBlock);
				FixedNode* node;
				for (i = 0; i + m_NodeSize < size; i += m_NodeSize )
				{
					node = (FixedNode*)((uint8_t*)(block) + sizeof(FixedBlock) + i);
					node->m_Next = m_FreeList;
					m_FreeList = node;
				}
			}
			FixedNode* node = m_FreeList;
			m_FreeList = m_FreeList->m_Next;
			return node;
		}

		void Free(void* node)
		{
			FixedNode* subNode = (FixedNode*)node;
			subNode->m_Next = m_FreeList;
			m_FreeList = subNode;
		}

	private:
		FixedBlock* m_BlockHeader;
		size_t		m_BlockSize;
		size_t		m_NodeSize;
		FixedNode* m_FreeList;
	};
}
