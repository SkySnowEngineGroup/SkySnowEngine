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
#include <atomic>
/*
	M��Multiple�������
	S��Single��������
	P��Producer��������
	C��Consumer��������
	Nettyû��ʹ��JDK���������У�ʹ����Lock-freeMpscqueue
*/
namespace SkySnow
{
	template<typename T>
	struct QNode
	{
		std::atomic<QNode*> next{nullptr};
		T* value;
	};
	//�������̳У�Ҳ���̳��κλ���
	template<typename T>
	class MpscQueue final
	{
	public:
		//��ѭstd::atomic<T>�Ķ����׼��pod����
		MpscQueue() = default;

		~MpscQueue()
		{
			//MpscQueue is Empty
			if (m_Head.load(std::memory_order_relaxed) == nullptr)
			{
				return;
			}
			//QNode* curr = m_Curr
		}
		/**
						   |-------------��Ч������--------------------|
			(ջ��)QNode -> |QNode -> QNode -> QNode -> QNode -> nullptr|
			     m_Head
				 m_Curr
				 mHead ָ��ͷ���
				 m_Currָ��ͷ���
		**/
		template<typename... Args>
		bool Enqueue(Args&&... args)
		{
			QNode* head = m_Head.load(std::memory_order_acquire);
			if (head == nullptr)//MpscQueue already Empty
			{
				return false;
			}

			QNode* newNode = new QNode;
			//���캯���ĵ���
			new (&newNode->value) T(std::forward<Args>(args)...);

			while (head != nullptr && !m_Head.compare_exchange_weak(head,newNode,std::memory_order_release));

			if (head == nullptr)//MpscQueue is Empty
			{
				((T*)(&newNode->value))->~T();
				delete newNode;
				newNode = nullptr;
				return false;
			}
			head->next.store(newNode,std::memory_order_release);
			return false;
		}



		bool IsEmpty() const
		{
			return m_Head.load(std::memory_order_relaxed) == nullptr;
		}
	private:
		QNode* GetNext(QNode* node)
		{
			QNode* next;
			do 
			{
				next = node->next.load(std::memory_order_relaxed);
			} while (next == nullptr);
			return QNode;
		}
		QNode m_Curr;
		std::atomic<QNode*> m_Head{ &m_Curr };
	};
}