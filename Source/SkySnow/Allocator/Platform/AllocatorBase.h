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
#include <new>
#include <limits>
#include <cstdint>
#include <utility>
#include "SkySnowProfiles.h"
#include "AllocMacros.h"
#include "UString.h"
namespace SkySnow
{
	//Alloc Base
	class MemBase
	{
	public:
		explicit MemBase(const char* name,bool threadSafe = false);
		virtual ~MemBase();

		virtual void* Alloc(size_t size,int align) = 0;

		virtual void Free(void* pointer = nullptr) = 0;

		const char* GetName() const 
		{
			return _Name;
		}

	protected:
		const char* _Name;
	private:
		bool		_IsThreadSafe;
	};


	//=====================================================================
	class GMalloc
	{
	public:
		static inline void* Alloc(size_t size, size_t alignedSize = 16);
		static inline void Free(void* mem, bool isAligned = true);
	};
#if PLATFORM == PLATFORM_WINDOW
	void* GMalloc::Alloc(size_t size, size_t alignedSize)
	{
		return _aligned_malloc(size, alignedSize);
	}

	void GMalloc::Free(void* mem, bool isAligned)
	{
		_aligned_free(mem);
	}
#elif PLATFORM == PLATFORM_ANDROID || PLATFORM == PLATFORM_LINUX
#include <malloc.h>

	void* GMalloc::Alloc(size_t size, size_t alignedSize)
	{
		return ::memalign(size, alignedSize);
	}

	void GMalloc::Free(void* mem, bool isAligned)
	{
		::free(mem);
	}
#else
	void* GMalloc::Alloc(size_t size, size_t alignedSize)
	{
		if (!alignedSize)
		{
			::malloc(size);
		}
		else
		{
			void* data = ::malloc(size + (alignedSize - 1) + sizeof(void*));
			if (data == nullptr)
				return nullptr;

			char* alignedData = ((char*)data) + sizeof(void*);
			alignedData += (alignedSize - ((uintptr_t)alignedData) & (alignedSize - 1)) & (alignedSize - 1);

			((void**)alignedData)[-1] = data;
			return alignedData;
		}
	}

	void GMalloc::Free(void* mem, bool isAligned)
	{
		if (!isAligned)
		{
			::free(mem);
		}
		else
		{
			::free(((void**)mem)[-1]);
		}
	}
#endif
}
