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
#include <atomic>
#include <memory>
#include "LogAssert.h"
#include "MpscQueue.h"
#include "GRIResource.h"
#include <thread>
namespace SkySnowLearning
{

	class HazardPointerMap
	{
	public:
		HazardPointerMap() {}

		void AddHazardPointer()
		{

		}
		void DeleteHazardPointer()
		{

		}

		void Acquire()
		{
			struct Pseudo
			{
				static inline uint32_t GetThread()
				{
					static std::atomic_uint counter{ 0 };
					uint32_t value = counter.fetch_add(1, std::memory_order_relaxed);
					SN_LOG("===value:%d\n", value);
					value = ((value >> 16) ^ value) * 0x45d9f3b;
					value = ((value >> 16) ^ value) * 0x45d9f3b;
					value = (value >> 16) ^ value;
					//SN_LOG("value:%d\n", value);
					return value;
				}
			};
			static thread_local uint32_t startIndex = Pseudo::GetThread();
			SN_LOG("startIndex:%d\n", startIndex);
		}
	};
	template<typename T>
	class HazardPointer
	{
		HazardPointer(const HazardPointer& copy) = delete;
		HazardPointer& operator=(const HazardPointer& other) = delete;
	public:
		HazardPointer() = default;
		HazardPointer(std::atomic<T*>& hazard, HazardPointerMap& hpMap)
		{
			SN_LOG("HazardPointer Construct.");
		}

		HazardPointer(HazardPointer&& other)
		{
			SN_LOG("HazardPointer Move Construct.");
		}

		HazardPointer& operator=(HazardPointer&& other)
		{
			SN_LOG("HazardPointer Move =.");
		}
	};

	template<typename T>
	HazardPointer<T> MakeHazardPointer(std::atomic<T*>& hazard, HazardPointerMap& hpMap)
	{
		return { hazard ,hpMap };
	}
	class TestMpscQueue
	{
	public:
		TestMpscQueue()
			: a(10)
		{
			SN_LOG("Construct TestMpscQueue.");
		}
		~TestMpscQueue()
		{
			SN_LOG("DeConstruct TestMpscQueue.");
		}

		void TestFun()
		{
			int atest = TestCa(1);
			SN_LOG("atest:%d", atest);
			int value = 1;
			int v1 = (value >> 16) ^ value;
			SN_LOG("atest:%d", v1);
			mpscQueue.store(new SkySnow::MpscQueue<TestMpscQueue*>(),std::memory_order_release);
			SkySnow::MpscQueue<TestMpscQueue*>* mpq = mpscQueue.load(std::memory_order_relaxed);
			mpq->Enqueue(const_cast<TestMpscQueue*>(this));

			std::vector<TestMpscQueue*> popData;
//			mpq->Dequeue(popData);
			int aa = 10;
		}

		int TestCa(int value)
		{
			value = ((value >> 16) ^ value) * 0x45d9f3b;
			value = ((value >> 16) ^ value) * 0x45d9f3b;
			value = (value >> 16) ^ value;
			return value;
		}
	private:
		std::atomic<SkySnow::MpscQueue<TestMpscQueue*>*> mpscQueue;
		int a;
	};
	struct TNode
	{
		std::atomic<TNode*> next{ nullptr };
		int value;
	};
	class TestTNode
	{
	public:
		TestTNode() {}
		~TestTNode() {}

		void Enqueue()
		{
			SN_LOG("***************************");
			SN_LOG("m_Cur:%p", &m_Cur);
			SN_LOG("m_Head:%p", (m_Head.load(std::memory_order_relaxed)));
			SN_LOG("m_Head->next:%p", (m_Head.load(std::memory_order_relaxed)->next.load(std::memory_order_relaxed)));
			SN_LOG("---------------------------");
			TNode* Prev = m_Head.load(std::memory_order_acquire);

			TNode* nNode = new TNode;
			nNode->value = 10;

			SN_LOG("temp:%p", nNode);

			

			while (Prev != nullptr && !m_Head.compare_exchange_weak(Prev, nNode, std::memory_order_release))
			{
			}

			Prev->next.store(nNode,std::memory_order_release);
			SN_LOG("head->next:%p", Prev->next.load(std::memory_order_relaxed));
			SN_LOG("m_Cur->next:%p", m_Cur.next.load(std::memory_order_relaxed));
		}
		void Dequeue()
		{
			TNode* tail = &m_Cur;
			TNode* const head = m_Head.exchange(nullptr,std::memory_order_acq_rel);
			if (tail == head || head == nullptr)
			{
				return;
			}
		}

		void Print()
		{
			TestMpscQueue* tq = new TestMpscQueue();
			tq->TestFun();
			//Enqueue();
			//Enqueue();
			//Dequeue();
			//SN_LOG("+++++++++++++++++++++++++");
			//SN_LOG("m_Cur:%p",&m_Cur);
			//SN_LOG("m_Head:%p",(m_Head.load(std::memory_order_relaxed)));
			//SN_LOG("m_Head->next:%p",m_Head.load(std::memory_order_relaxed)->next.load(std::memory_order_relaxed));
			//SN_LOG("+++++++++++++++++++++++++");

			//TNode* nextNode = m_Cur.next.load(std::memory_order_relaxed);
			//while (nextNode != nullptr)
			//{
			//	TNode* nn = nextNode->next.load(std::memory_order_relaxed);
			//	SN_LOG("All Node Address:%p", nextNode);
			//	nextNode = nn;
			//}
		}
	private:
		TNode m_Cur;
		int a{ 1 };
		std::atomic<TNode*> m_Head{ &m_Cur };
	};

	//此方式会存在ABA问题
	template<typename T>
	class LockFreeStack
	{
	private:
		struct Node
		{
			Node()
				: value(nullptr)
				, next(nullptr)
			{
			}
			Node(T& v, Node* n)
				: value(v)
				, next(n)
			{}
			~Node()
			{}
			T value;
			Node* next;
		};
	public:
		LockFreeStack()
			: m_Head(nullptr)
		{
		}
		void Push(const T& value)
		{
			Node* node = new Node{ value, m_Head.load() };
			node->next = m_Head.load();
			while (!m_Head.compare_exchange_strong(node->next, node));
		}

		void Pop()
		{
			Node* node = m_Head.load();
			while (node && !m_Head.compare_exchange_strong(node, node->next));
			if (node)
			{
				delete node;
				node = nullptr;
			}
		}
	private:
		std::atomic<Node*> m_Head;
	};

	//简单实现一个自旋锁
	class SpinMutex
	{
	public:
		SpinMutex()
		{
		}
		void Lock()
		{
			while (flag.test_and_set(std::memory_order_acquire));
		}

		void UnLock()
		{
			flag.clear(std::memory_order_release);
		}
	private:
		std::atomic_flag flag = ATOMIC_FLAG_INIT;
	};

	static void TestThreadFun()
	{
		static HazardPointerMap hpMap;
		hpMap.Acquire();
	}


	static void TestFunctionAboutLockFree()
	{
		//static HazardPointerMap hpMap;
		//static std::atomic<SkySnow::MpscQueue<SkySnow::GRIResource*>*> mpscQueue;
		//auto hp = MakeHazardPointer(mpscQueue, hpMap);

		//std::thread  t1(TestThreadFun);
		//std::thread  t2(TestThreadFun);
		//std::thread  t3(TestThreadFun);
		//std::thread  t4(TestThreadFun);
		int a = (10 + 2) % 32;
		int b = a;

		//t1.join();
		//t2.join();
		//t3.join();
		//t4.join();
	}
}