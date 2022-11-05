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
#include "StackAllocator.h"
namespace SkySnow
{
	//=============================================================
	MemStack::MemStack()
		: MemBase("StackAllocator", false)
		, _Top(nullptr)
		, _End(nullptr)
		, _TopChunk(nullptr)
	{

	}
	//=============================================================
	MemStack::MemStack(const char* name, bool threadSafe)
		: MemBase(name, threadSafe)
		, _Top(nullptr)
		, _End(nullptr)
		, _TopChunk(nullptr)
	{

	}
	//=============================================================
	MemStack::~MemStack()
	{
		FreeChunks(nullptr);
	}
	//=============================================================
	void* MemStack::Alloc(size_t size, int align)
	{
		uint8_t* result = AlignSize(_Top, align);
		uint8_t* newTop = result + size;
		if (newTop <= _End)
		{
			_Top = newTop;
		}
		else
		{
			AllocNewChunk(size + align);
			result = AlignSize(_Top, align);
			newTop = result + size;
			_Top = newTop;
		}
		return result;
	}
	//=============================================================
	void MemStack::Free(void* pointer)
	{
		Chunk* chunk = (Chunk*)ContainsPointer(pointer);
		if (chunk)
		{
			FreeChunks(chunk);
		}
	}
	//=============================================================
	void MemStack::Flush()
	{
		FreeChunks(nullptr);
	}
	//=============================================================
	void MemStack::AllocNewChunk(int32_t minSize)
	{
		Chunk* chunk = nullptr;
		int32_t allSize = minSize + (int32_t)sizeof(Chunk);
		//uint32_t allocSize;
		////todo .
		//if (_TopChunk || allSize > PageProperty::PageSize)
		//{
		//	
		//}
		chunk = (Chunk*)GMalloc::Alloc(allSize);
		chunk->_DataSize = allSize - (int32_t)sizeof(Chunk);

		chunk->_Next = _TopChunk;
		_TopChunk	 = chunk;
		_Top		 = chunk->Data();
		_End		 = _Top + chunk->_DataSize;
	}
	//=============================================================
	void MemStack::FreeChunks(Chunk* chunk)
	{
		while (_TopChunk != chunk)
		{
			Chunk* removeChunk = _TopChunk;
			_TopChunk = _TopChunk->_Next;
			GMalloc::Free(removeChunk);
		}
		_Top = nullptr;
		_End = nullptr;
		if (_TopChunk)
		{
			_Top = _TopChunk->Data();
			_End = _Top + _TopChunk->_DataSize;
		}
	}
	//=============================================================
	void* MemStack::ContainsPointer(const void* pointer)
	{
		const uint8_t* ptr = (uint8_t*)pointer;
		Chunk* chunk = nullptr;
		for (chunk = _TopChunk; chunk; chunk = chunk->_Next)
		{
			if (ptr >= chunk->Data() && ptr < chunk->Data() + chunk->_DataSize)
			{
				return chunk;
			}
		}
		return nullptr;
	}
	//=============================================================
}