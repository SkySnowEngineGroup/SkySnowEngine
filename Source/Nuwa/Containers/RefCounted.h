//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
// Open source is written by wangcan(crygl)¡¢liuqian(SkySnow)¡¢zhangshuangxue(Calence)
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
#include <atomic>
namespace Nuwa
{
	template <typename Referenced>
	class RefCountPtr
	{
		typedef Referenced* m_Referenced;
	public:

		RefCountPtr()
		: m_Referenced(nullptr)
		{
		}


	};
	//If you want your class to be automatically reclaimed, inherit the class Use as RefCountPtr<XXX>
	//refcount base,thread not safe
	class RefCounted
	{
	public:
		RefCounted();

		virtual ~RefCounted();

		RefCounted(const RefCounted& rhs) = delete;

		RefCounted& operator =(const RefCounted& rhs) = delete;

		void Add();

		void Release();

		int RefCount()const;
	private:
		int32_t m_refs;
	};
	//use atomic refcount
	//thread safe
	class RefThreadSafeCounted
	{
	public:
		RefThreadSafeCounted();
		virtual ~RefThreadSafeCounted();
		/// Prevent copy construction.
		RefThreadSafeCounted(const RefThreadSafeCounted& rhs) = delete;
		/// Prevent assignment.
		RefThreadSafeCounted& operator =(const RefThreadSafeCounted& rhs) = delete;

		void Add();

		void Release();

		int RefCount()const;
	private:
		std::atomic<int32_t> m_refs;
	};
}