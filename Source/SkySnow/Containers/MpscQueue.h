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
	struct QNode
	{
		std::atomic<QNode*> next{nullptr};
		T* value;
	};
	//不允许被继承，也不继承任何基类
	template<typename T>
	class MpscQueue final
	{
	public:
		//遵循std::atomic<T>的对象标准，pod类型
		MpscQueue() = default;

		~MpscQueue()
		{
			//MpscQueue is Empty
			if (m_Curr.load(std::memory_order_relaxed) == nullptr)
			{
				return;
			}
			QNode* nextNode = m_Head.next.load(std::memory_order_relaxed);
			while (nextNode != nullptr)
			{
				QNode* NN = nextNode->next.load(std::memory_order_relaxed);
				((T*)(&nextNode->value))->~T();
				delete nextNode;
				nextNode = NN;
			}
		}
		/**
						   |---有效数据区---|
			(栈上)QNode -> |QNode -> nullptr|
			     m_Head
							m_Curr
				 mHead 指向头结点
				 m_Curr指向有效数据
		**/
		template<typename... Args>
		bool Enqueue(Args&&... args)
		{
			QNode* curr = m_Curr.load(std::memory_order_acquire);
			if (curr == nullptr)//MpscQueue already Empty
			{
				return false;
			}

			QNode* newNode = new QNode;
			//构造函数的调用
			new (&newNode->value) T(std::forward<Args>(args)...);

			while (curr != nullptr && !m_Curr.compare_exchange_weak(curr, newNode, std::memory_order_release))
			{
			}

			if (curr == nullptr)//MpscQueue is Empty
			{
				((T*)(&newNode->value))->~T();
				delete newNode;
				newNode = nullptr;
				return false;
			}
			curr->next.store(newNode,std::memory_order_release);
			return false;
		}
		//一次性全出队列，适用于整帧中数据的处理
		void Dequeue(std::vector<T*>& popData)
		{
			QNode* head = &m_Head;
			QNode* const curr = m_Curr.exchange(nullptr,std::memory_order_acq_rel);

			if (head == curr || curr == nullptr)
			{
				return nullptr;
			}

			QNode* nextNode = GetNext(head);

			while (nextNode != curr)
			{
				QNode* temp = GetNext(nextNode);

				T* valuePtr = (T*)&nextNode->value;
				popData.emplace_back(*valuePtr);
				valuePtr->~T();
				delete nextNode;
				nextNode = temp;
			}
			//处理当前节点
			T* vPtr = (T*)&curr->value;
			popData.emplace_back(*vPtr);
			vPtr->~T();
			delete curr;
		}


		bool IsEmpty() const
		{
			return m_Curr.load(std::memory_order_relaxed) == nullptr;
		}
	private:
		QNode* GetNext(QNode* node)
		{
			QNode* next;
			do 
			{
				next = node->next.load(std::memory_order_relaxed);
			} while (next == nullptr);
			return next;
		}

	private:
		QNode m_Head;
		std::atomic<QNode*> m_Curr{ &m_Head };
	};
}