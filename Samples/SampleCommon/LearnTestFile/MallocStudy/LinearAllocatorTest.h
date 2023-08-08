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
//Linear memory allocation; it is linear growth, suitable for the processing of rendering state dataand skeletal animation data of each frame, 
//							and it is easy to support lockfreeand index increment operations
//微软中的mimalloc中的代码挺好的:https://github.com/microsoft/mimalloc
#pragma once
#include <stdint.h>
#include "SkySnowProfiles.h"
#if PLATFORM == PLATFORM_MAC
#include <sys/malloc.h>
#else
#include <malloc.h>
#endif
namespace SkySnow
{
	class LinearAllocatorTest
	{
	private:
		struct Block
		{
			Block*	m_Next;
		};
	public:
		struct Allocator
		{
			Block*		m_BlockHeader;
			uint8_t*	m_End;
			size_t		m_BlockSize;
		};
	public:
		LinearAllocatorTest()
		{
		}
		~LinearAllocatorTest()
		{

		}


		void Init(Allocator* alloc,size_t size)
		{
			alloc->m_BlockSize = size + sizeof(Block) < 1024 ? 1024 : (size + sizeof(Block));
			alloc->m_BlockHeader = NULL;
			alloc->m_End = (uint8_t*)sizeof(Block);
		}

		void* Malloc(Allocator* alloc, size_t size)
		{
			size_t currSize = alloc->m_End - (((uint8_t*)alloc->m_BlockHeader) + sizeof(Block));
			if (size > currSize)
			{
				size_t rsize = size + sizeof(Block);
				if (rsize > alloc->m_BlockSize)
				{
					Block* block = (Block*)malloc(rsize);
					uint8_t* buffer = (uint8_t*)(block)+sizeof(Block);
					if (alloc->m_BlockHeader != nullptr)
					{
						block->m_Next = alloc->m_BlockHeader->m_Next;
						alloc->m_BlockHeader->m_Next = block;
					}
					else
					{
						block->m_Next = nullptr;
						alloc->m_BlockHeader = block;
						alloc->m_End = buffer;
					}
					return buffer;
				}
				else
				{
					Block* block = (Block*)malloc(alloc->m_BlockSize);
					block->m_Next = alloc->m_BlockHeader;
					alloc->m_BlockHeader = block;
					alloc->m_End = (uint8_t*)block + alloc->m_BlockSize;
				}
			}
			alloc->m_End = alloc->m_End - size;
			return alloc->m_End;
		}

		void Free(Allocator* alloc)
		{
			Block* block = alloc->m_BlockHeader;
			Block* temp;
			while (block) {
				temp = block;
				block = block->m_Next;
				free(temp);
			}
		}	
	};
}