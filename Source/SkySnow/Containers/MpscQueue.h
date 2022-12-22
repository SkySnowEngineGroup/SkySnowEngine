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


#pragma once
#include <vector>
#include <atomic>
#include "LogAssert.h"
#include "StackAllocator.h"
/*
	M：Multiple，多个的
	S：Single，单个的
	P：Producer，生产者
	C：Consumer，消费者
	Netty没有使用JDK的阻塞队列，使用了Lock-freeMpscqueue
*/
namespace SkySnow
{
	template<typename T>
	class MpscQueue final
	{
	public:
		MpscQueue()
		{
			Node* sentinel = new Node;
			_Head.store(sentinel,std::memory_order_relaxed);
			_Tail = _Head;
		}
		MpscQueue(const MpscQueue& other) = delete;
		MpscQueue(const MpscQueue&& other) = delete;
		MpscQueue& operator=(const MpscQueue& other) = delete;
		MpscQueue& operator=(const MpscQueue&& other) = delete;

		template<typename... Args>
		void Enqueue(Args&&... args)
		{

			
		}
		template<typename T>
		bool Dequeue(T& item)
		{
			return true;
		}
	private:
		struct Node
		{
			std::atomic<Node*> _Next{ nullptr };
			T				   _Value;
		};
	private:
		std::atomic<Node*>	_Head;
		std::atomic<Node*>	_Tail;
	};
}