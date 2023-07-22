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
#include "LogAssert.h"
#include "RefCounted.h"
#include <unordered_map>
using namespace std;
using namespace SkySnow;
namespace SkySnowLearning
{
	struct Node
	{
		Node(int k = -1,int v = -1)
			: key(k)
			, value(v)
			, pre(nullptr)
			, next(nullptr)
		{
		}
		int key;
		int value;
		Node* pre;
		Node* next;
	};
	class LRU
	{
	public:
		LRU(int cap)
			: capacity(cap)
			, size(0)
		{
			head = new Node();
			tail = new Node();
			head->next = tail;
			tail->pre = head;
		}

		~LRU()
		{
			Node* temp;
			while (head)
			{
				temp = head->next;
				delete head;
				head = nullptr;
				head = temp;
			}
		}

		int Get(int key)
		{
			if (dic.find(key) == dic.end())
			{
				return -1;
			}
			Node* target = dic[key];
			//从链表中删除该节点
			target->pre->next = target->next;
			target->next->pre = target->pre;
			//将节点放到头结点后
			head->next->pre = target;
			target->next = head->next;

			head->next = target;
			target->pre = head;
			return target->value;
		}

		void Put(int key,int value)
		{
			//找到对应的key值
			if (dic.find(key)!= dic.end())
			{
				Node* target = dic[key];
				target->value = value;
				dic.erase(key);
				//从当前节点摘除
				target->pre->next = target->next;
				target->next->pre = target->pre;
				//摘除后的节点放到头结点后
				head->next->pre = target;
				target->next = head->next;

				head->next = target;
				target->pre = head;
			}
			else//未找到对应的Key的Node
			{
				//如果容器满了，那么就删除尾节点不常用的
				if (size == capacity)
				{
					Node* target = tail->pre;
					//从链表中摘除
					target->pre->next = tail;
					tail->pre = target->pre;

					delete target;
					target = nullptr;
					size--;
				}
				//容器未满，那么创建一个新的节点，放到头结点后
				Node* target = new Node(key,value);
				//将该节点放到hashmap中
				dic[key] = target;
				//将节点放到头结点后
				target->pre = head;
				head->next->pre = target;
				target->next = head->next;
				head->next = target;
				size++;
			}
		}

	private:
		int size;
		int capacity;
		Node* head;
		Node* tail;
		unordered_map<int, Node*> dic;
	};

	template<typename Key,typename Value>
	class LRUT
	{
	private:
		struct Node
		{
			Node(Key k = nullptr,Value v = nullptr)
				: key(k)
				, value(v)
				, pre(nullptr)
				, next(nullptr)
			{
			}
			Key key;
			Value value;
			Node* pre;
			Node* next;
		};
	public:
		LRUT(int cap)
			: capacity(cap)
			, size(0)
		{
			head = new Node();
			tail = new Node();
			
			head->next = tail;
			tail->pre = head;
		}

		~LRUT()
		{
			Node* temp;
			while (head)
			{
				temp = head->next;
				delete head;
				head = nullptr;
				head = temp;
			}
		}

		Value Get(Key key)
		{
			if (dic.find(key) == dic.end())
				return -1;
			Node* target = dic[key];
			//从链表中删除该节点
			target->pre->next = target->next;
			target->next->pre = target->pre;
			//将节点放到头结点后
			head->next->pre = target;
			target->next = head->next;
			head->next = target;
			target->pre = head;

			return target->value;
		}

		void Put(Key key,Value value)
		{
			//找到对应的key值
			if (dic.find(key) != dic.end())
			{
				Node* target = dic[key];
				target->value = value;
				dic.erase(key);
				//从当前节点摘除
				target->pre->next = target->next;
				target->next->pre = target->pre;
				//摘除后的节点放到头结点后
				head->next->pre = target;
				target->next = head->next;

				head->next = target;
				target->pre = head;
			}
			else//未找到对应的Key的Node
			{
				//如果容器满了，那么就删除尾节点不常用的
				if (size == capacity)
				{
					Node* target = tail->pre;
					//从链表中摘除
					target->pre->next = tail;
					tail->pre = target->pre;

					delete target;
					target = nullptr;
					size--;
				}
				//容器未满，那么创建一个新的节点，放到头结点后
				Node* target = new Node(key, value);
				//将该节点放到hashmap中
				dic[key] = target;
				//将节点放到头结点后
				target->pre = head;
				head->next->pre = target;
				target->next = head->next;
				head->next = target;
				size++;
			}
		}
	private:
		int capacity;
		int size;
		Node* head;
		Node* tail;
		unordered_map<Key, Node*> dic;
	};
}
