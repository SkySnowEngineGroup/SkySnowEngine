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
#include "RefCounted.h"

namespace SkySnow
{
	//==========not safe thread RefCount
	RefCounted::RefCounted()
		: m_refs(0)
	{
	}

	RefCounted::~RefCounted()
	{
		m_refs = -1;
	}
	
	void RefCounted::Add()
	{
		m_refs ++;
	}

	void RefCounted::Release()
	{
		m_refs--;
		if (!m_refs)
		{
			delete this;
		}
	}

	int RefCounted::RefCount() const
	{
		return m_refs;
	}

	//==========safe thread RefCount
	RefThreadSafeCounted::RefThreadSafeCounted()
		: NonCopyable()
	{
		std::atomic_init(&m_refs, 0);
	}

	RefThreadSafeCounted::~RefThreadSafeCounted()
	{
		m_refs.store(-1, std::memory_order_relaxed);
	}

	void RefThreadSafeCounted::Add()
	{
		m_refs.fetch_add(1, std::memory_order_acquire);
	}

	void RefThreadSafeCounted::Release()
	{
		m_refs.fetch_sub(1, std::memory_order_release);
		if (!m_refs.load(std::memory_order_relaxed))
		{
			delete this;
		}
	}

	int RefThreadSafeCounted::RefCount() const
	{
		return m_refs.load(std::memory_order_relaxed);
	}
}