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
#include <unordered_map>
#include <vector>
#include "LogAssert.h"
#include "StudyUtil.h"
using namespace std;
using namespace SkySnowLearning;
//base ruler study class name first is s_ start
namespace SkySnow
{
/*
    List&Vector&Dequeue
    一、vector
      1. 底层实现为数组，在堆上分配
      2. 如果内存不够使用，那么会分配两倍容量，将原空间的内存数据拷贝到新的内存空间，
         并将原空间的内存数据释放，将内存回收
      特点
      1. 随机访问时间复杂度为0(1)
      2. 插入
         2.1 内存足够情况，在尾部插入，不需要拷贝
         2.2 内存不够情况，在尾部插入，需要内存申请和释放，并对之前数据进行拷贝
         2.3 内存足够情况，在中间插入，需要拷贝
         2.4 内存不够情况，在中间插入，需要进行内存申请和释放，并对之前数据进行拷贝
      3. 删除
         3.1 最后删除，效率很快
         3.2 中间删除，内存拷贝
      适用场景
      1. 随机访问，不经常对非尾节点进行插入删除
    二、List
      1. 底层为动态链表(双向链表)，在堆上分配，删除结点会进行内存释放，插入结点会申请内存
      特点
        1. 访问: 随机访问时间很差，只能从头结点开始
        2. 插入: 很快，常数开销，不涉及内存拷贝及内存释放
        3. 删除: 很快，常数开销，不设计内存拷贝及内存释放
      适用场景
        1. 经常插入删除大量数据
*/
	class S_Array
    {
    public:
        
    };
    //Deal With Single List
    class S_List
    {
    public:
        S_List()
            : _Head(nullptr)
            , _Curr(nullptr)
        {
        }
        
        ~S_List()
        {
            Clear();
        }
        //add node trail
        bool Append_Back(SSNode* node)
        {
            if(!node)
            {
                SN_WARN("Append Node is nullptr.");
                return false;
            }
            if(_Head == nullptr)
            {
                _Head = node;
                _Curr = node;
            }
            else
            {
                _Curr->next = node;
                _Curr = node;
            }
            return true;
        }
        
        SSNode* GetHeadNode()
        {
            return _Head;
        }
        
        SSNode* GetTrailNode()
        {
            return _Curr;
        }
        
        void Print_Node()
        {
            SSNode* node = _Head;
            while (node)
            {
                SN_LOG("NodeValue:%d",node->value);
                node = node->next;
            }
        }

        SSNode* isLoop()
        {
            //查看环入口节点
            //假设节点头距离入口为len，入口点距离相交点x,环长度为r,n为倍数
            //slow走的距离为: d = len + x;
            //fast走的距离为: 2d = len + x + nr;
            //带入计算得关系: len = nr - x; 假设n=1，那么就是len = r - x;
            //从头开始一步一步走，和从相遇点开始走，最终会相遇，相遇点即为入口点
            SSNode* slow = _Head;
            SSNode* fast = _Head;
            while (slow && fast != nullptr && fast->next)
            {
                slow = slow->next;
                fast = fast->next->next;
                if(slow == fast)
                {
                    break;
                }
            }
            if(fast == nullptr || fast->next == nullptr)
            {
                return nullptr;
            }
            slow = _Head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
        void Reverse()
        {
            //      node->node->node->node->node->null
            //pre   curr  next
            SSNode* cur = _Head;
            _Curr = _Head;
            SSNode* pre = nullptr;
            while (cur)
            {
                SSNode* nn = cur->next;
                cur->next = pre;
                pre = cur;
                cur = nn;
            }
            _Head = pre;
        }
        bool Clear()
        {
            //if loop,break this loop
            SSNode* lln = isLoop();
            if(lln)
            {
                SSNode* temp = _Head;
                while(lln != temp->next)
                {
                    temp = temp->next;
                }
                temp->next = nullptr;
            }
            SSNode* node = _Head;
            while (node)
            {
                SSNode* tn = node->next;
                delete node;
                node = nullptr;
                node = tn;
            }
            _Head = nullptr;
            _Curr = nullptr;
        }
        //if acc return first number,if odd return target number
        SSNode* Find_MidNode()
        {
            SSNode* slow = _Head;
            SSNode* fast = _Head;
            while (fast && fast->next)
            {
                slow = slow->next;
                fast = fast->next->next;
            }
            return slow;
        }
        //delete target node
        bool Delete_Node(SSNode* node)
        {
            if(!node)
            {
                SN_WARN("Node is nullptr.");
                return false;
            }
            SSNode* temp = _Head;
            bool isFind = false;
            while(temp)//
            {
                if(temp == node)//deleta tragrt node is head
                {
                    temp = node;
                    _Head = _Head->next;
                    delete node;
                    node = nullptr;
                    isFind = true;
                    break;
                }
                else if(temp->next != nullptr && temp->next == node)
                {
                    SSNode* rnn = temp->next->next;
                    delete node;
                    node = nullptr;
                    temp->next = rnn;
                    isFind = true;
                    break;
                }
                temp = temp->next;
            }
            if(!isFind)
            {
                SN_WARN("Not find target node.");
                return false;
            }
            return true;
        }
        //insert target node back
        bool Instert_Back(SSNode* targetNode,SSNode* node)
        {
            if(!targetNode || !node)
            {
                SN_WARN("Maybe targetNode or node is nullptr.");
                return false;
            }
            SSNode* temp = _Head;
            while(temp)
            {
                if(temp == targetNode)
                {
                    temp = targetNode;
                    break;
                }
                temp = temp->next;
            }
            //search target node
            if(temp)
            {
                SSNode* rn = targetNode->next;
                targetNode->next = node;
                node->next = rn;
            }
            else
            {
                SN_WARN("Not Find TargetNode.");
                return false;
            }
            return true;
        }
        //instert target nod back
        bool Instert_Front(SSNode* targetNode,SSNode* node)
        {
            if(!targetNode || !node)
            {
                SN_WARN("Maybe targetNode or node is nullptr.");
                return false;
            }
            SSNode* temp = _Head;
            bool isFind = false;
            while(temp)
            {
                if(temp == targetNode)//instert head front
                {
                    node->next = _Head;
                    _Head = node;
                    isFind = true;
                    break;
                }
                else if(temp->next != nullptr && temp->next == targetNode)
                {
                    SSNode* tnn = temp->next;
                    temp->next = node;
                    node->next = tnn;
                    isFind = true;
                    break;
                }
                temp = temp->next;
            }
            if(!isFind)
            {
                SN_WARN("Not Find TargetNode.");
                return false;
            }
            return true;
        }
    private:
        SSNode* _Head;
        SSNode* _Curr;
    };
    
    void Clear(SSNode* node)
    {
        SSNode* temp = node;
        while (temp)
        {
            SSNode* tn = temp->next;
            delete temp;
            temp = nullptr;
            temp = tn;
        }
    }

    static void StudyList()
    {
        S_List* list = new S_List();
        SSNode* n1 = new SSNode(1);//a b
        SSNode* n2 = new SSNode(2);//a
        SSNode* n3 = new SSNode(3);//b a
        SSNode* n4 = new SSNode(4);//
        SSNode* n5 = new SSNode(5);//b

        list->Append_Back(n1);
        list->Append_Back(n2);
        list->Append_Back(n3);
        list->Append_Back(n4);
        list->Append_Back(n5);
//        n5->next = n3;
//        SSNode* ln = list->isLoop();
//        SN_LOG("NodeValue:%d",ln->value);
//        list->Reverse();
        SSNode* mid = list->Find_MidNode();
        list->Print_Node();
        SN_LOG("MidNumber:%d",mid->value);
        delete list;
    }
}
