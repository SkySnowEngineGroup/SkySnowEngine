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
#pragma once
#include "AllocatorBase.h"
#include "PageAllocator.h"
namespace SkySnow
{
	/*
	*	Base Key Introduce	
	* 	MemoryPool
	*		Block:ָ�룬ָ���һ��memoryblock
	*		UnitSize:���ͣ���ʾÿ��unit �ĳߴ�
	*		InitSize:���ͣ���ʾ��һ��block��unit����
	*		GrowSize:���ͣ���ʾ�ڵ�һ��block֮���ټ������ӵ�ÿ��block��unit����
	*	MemoryBlock
	*		Size:�������ݣ���ʾ��block���ڴ��еĴ�С
	*		Free:���ͣ���ʾʣ���м���unitδ������
	*		First:���ͣ���ʾ��һ���ɹ������unit�ı�ʶ��
	*		Next:ָ�룬ָ����һ��memory block
	*	MemoryUnit<���߽�Chunk>
	*		Next:�������ݣ���ʾ��һ���ɹ������unit�ı�ʶ��
	*		Data[]:ʵ�ʵ��ڴ��������С�ڴ���ʱ�ɵ��÷�ָ��
	*
	*/
	class MemStack : public MemBase
	{
	private:
		struct Chunk
		{
			Chunk*		_Next;//4byte
			int32_t		_DataSize;//4byte

			uint8_t* Data() const
			{
				return ((uint8_t*)this + sizeof(Chunk));
			}
		};
	public:
		MemStack();
		MemStack(const char* name, bool threadSafe = false);

		MemStack(const MemStack& other) = delete;

		virtual ~MemStack();

		virtual void* Alloc(size_t size, int align = DefaultAlignment) override;

		virtual void Free(void* pointer = nullptr) override;
		void Flush();
	private:
		void* ContainsPointer(const void* pointer);
		void AllocNewChunk(int32_t minSize);
		void FreeChunks(Chunk* chunk);
	private:
		uint8_t*		_Top;
		uint8_t*		_End;
		Chunk*			_TopChunk;
	};
}
