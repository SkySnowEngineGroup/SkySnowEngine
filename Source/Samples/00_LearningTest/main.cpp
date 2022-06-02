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
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "LogAssert.h"
#include "Tree.h"
#include "List.h"
#include "BaseKnowledge.h"
using namespace SkySnow;
using namespace SkySnowLearning;
int main()
{
	SN_LOG("Learning KnowLedge!\n");

	{
		BinaryTree* bt = new BinaryTree();
		bt->VisitTree();
		bt->TwoTreeEqual();
		bt->ReverTree();

		delete bt;
		bt = nullptr;
	}
	//Study ListNode
	{
		ListAlgorithm* la = new ListAlgorithm();
		la->ReverseListNode();

		la->IsExitisLoop();
		delete la;
		la = nullptr;
	}
	//Base KnowLedge
	{
		//Base tem1 = Base();
		//Base tem2 = tem1;
		//Base tem3;
		//tem3 = tem1;
		SN_LOG("==============");
		Base* t1 = new Base();
		Base* t2 = t1;

		t2->BaseLD();
		delete t1;
	}
	//system("pause");
	getchar();
	return 0;
}