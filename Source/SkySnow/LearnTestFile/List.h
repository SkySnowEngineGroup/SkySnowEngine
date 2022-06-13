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
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include "LogAssert.h"
using namespace std;
namespace SkySnowLearning
{
	struct ListNode
	{
		ListNode()
			: m_Data(0)
			, m_Next(nullptr)
		{
		}
		ListNode(int value)
			: m_Data(value)
			, m_Next(nullptr)
		{
		}
		ListNode(int value,ListNode* next)
			: m_Data(value)
			, m_Next(next)
		{
		}
		int m_Data;
		ListNode* m_Next;
	};
	//链表无环:查找单向链表中的中间节点，可以使用快慢指针，当快指针走到结尾，那么慢指针则指向中间节点
	//两条链表交于某个节点:可以将其中一个链表首尾相连，然后查找到链表环节点即为两条链表交叉点
	class ListAlgorithm
	{
	public:
		ListAlgorithm()
			: m_Head(nullptr)
		{
		}

		~ListAlgorithm()
		{
		}

		void ReverseListNode()
		{
			vector<int> listData = { 1,2,3,4,5,6 };
			ListNode* head = CreateList(listData);
			VisitList(head);

			head = ReverseList(head);
			VisitList(head);
		}

		void IsExitisLoop()
		{
			//创建有环链表
			//  1->2->3->4->5->6->2;
			ListNode* node1 = new ListNode(1);
			ListNode* node2 = new ListNode(2);
			ListNode* node3 = new ListNode(3);
			ListNode* node4 = new ListNode(4);
			ListNode* node5 = new ListNode(5);
			ListNode* node6 = new ListNode(6);

			node1->m_Next = node2;
			node2->m_Next = node3;
			node3->m_Next = node4;
			node4->m_Next = node5;
			node5->m_Next = node6;
			node6->m_Next = node2;

			//判断链表是否有环
			bool isLoop = IsExitisLoop(node1);
			if (isLoop) 
			{
				SN_LOG("List Exit Loop.");
			}
			else 
			{ 
				SN_LOG("List Not Exit Loop."); 
			}
			ListNode* enterNode = LoopListEnter(node1);
			SN_LOG("Enter Node Value:%d",enterNode->m_Data);
		}

	private:
		bool IsExitisLoop(ListNode* head)
		{
			ListNode* slow = head;
			ListNode* fast = head;
			while (fast && fast->m_Next)
			{
				slow = slow->m_Next;
				fast = fast->m_Next->m_Next;
				if (slow == fast)
					break;
			}
			return !(fast == nullptr || fast->m_Next == nullptr);
		}

		ListNode* LoopListEnter(ListNode* head)
		{
			ListNode* slow = head;
			ListNode* fast = head;
			while (fast && fast->m_Next)
			{
				slow = slow->m_Next;
				fast = fast->m_Next->m_Next;
				if (slow == fast)
					break;
			}
			if (fast == nullptr || fast->m_Next == nullptr)
				return nullptr;

			//查看环入口节点
			//假设节点头距离入口为len，入口点距离相交点x,环长度为r,n为倍数
			//slow走的距离为: d = len + x;
			//fast走的距离为: 2d = len + x + nr;
			//带入计算得关系: len = nr - x; 假设n=1，那么就是len = r - x;
			//从头开始一步一步走，和从相遇点开始走，最终会相遇，相遇点即为入口点
			slow = head;
			while (slow != fast)
			{
				slow = slow->m_Next;
				fast = fast->m_Next;
			}
			return slow;
		}

		//    node-->node-->node-->node-->null
		//pre curr   next
		ListNode* ReverseList(ListNode* head)
		{
			if (head == nullptr)
				return nullptr;
			ListNode* pre = nullptr;
			ListNode* curr = head;
			while (curr != nullptr)
			{
				ListNode* next = curr->m_Next;
				curr->m_Next = pre;
				pre = curr;
				curr = next;
			}
			return pre;
		}
		//遍历打印链表的值
		void VisitList(ListNode* rNode)
		{
			if (rNode == nullptr)
			{
				SN_LOG("Root Node is Null.");
			}
			ListNode* temp = rNode;
			while (temp != nullptr)
			{
				printf("%d ",temp->m_Data);
				temp = temp->m_Next;
			}
			printf("\n");
		}

		ListNode* CreateList(const vector<int>& vec)
		{
			ListNode* head = nullptr;
			ListNode* tl = nullptr;
			for (int i = 0; i < vec.size();i ++)
			{
				if (tl == nullptr)
				{
					ListNode* node = new ListNode(vec[i]);
					tl = node;
					head = tl;
				}
				else
				{
					ListNode* newNode = new ListNode(vec[i]);
					newNode->m_Next = nullptr;
					tl->m_Next = newNode;
					tl = newNode;
				}
			}
			return head;
		}

		
	private:
		ListNode* m_Head;

	};


}

