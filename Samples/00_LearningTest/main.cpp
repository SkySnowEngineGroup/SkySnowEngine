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
#include "TreeBase.h"
#include "ListBase.h"
#include "StackBase.h"
#include "BaseKnowledge.h"
#include "Ptr.h"
#include "Cache.h"
#include "NumberProcess.h"
#include "File.h"
#include "SingletonBase.h"
#include "LockFree.h"
#include "FunCb.h"
#include "Framework.h"
#include "SharePtr.h"
using namespace SkySnow;
using namespace SkySnowLearning;
int main()
{
	SN_LOG("Learning KnowLedge!");
    //Study Base Data Structure
    {
//        StudyList();
//        Stack_Data();
        //StudyNumberProcess();
    }

	//{
	//	CommandBuffer* cb = new CommandBuffer();
	//	//��������
	//	CreateHandle handle = cb->EncoderCreateBuffer();

	//	cb->EncoderSetBuffer(handle);
	//	//ִ����Ⱦ����
	//	cb->RenderCmd();
	//	handle._Data->Log();
	//}
	//{
	//	TestFunctionAboutLockFree();
	//}
	//{
	//	TestTNode* tN = new TestTNode();
	//	tN->Print();
	//}
//	//�����������������ü�˳��
//	{
//		TestChildCon();
//	}
//	//���Զ��ֵ�����
//	{
//		LazySingleton* instance = LazySingleton::GetInstance();
//		instance->Release();
//		LazySingletonLocal* instance1 = LazySingletonLocal::GetInstance();
//
//		HungrySingleton* instance2 = HungrySingleton::GetInstance();
//	}

//	//LRUCache
//	{
//		LRU lru(5);
//;
//		lru.Put(1, 10);
//		lru.Put(2, 20);
//		lru.Put(3, 30);
//		lru.Put(4, 40);
//
//		lru.Put(2,200);
//		SN_LOG("LRU Value:%d",lru.Get(1));
//		SN_LOG("LRU Value:%d",lru.Get(2));
//	}
//	//���Ʋ�����
//	{
//		Move* test = new Move();
//		Move test2;
//		test2.Test(std::move(test));
//		if (test)
//		{
//			delete test;
//		}
//		//test2 = std::move(test);
//		int a = (0x1 << 21) + 17;
//		SN_LOG("Value:%d",a);
//	}
//	//����������԰���
//	{
//		SN_LOG("====================");
//		//RefCountPtr<TestSkySnowPtr> test(new TestSkySnowPtr());
//		share_ptr<Base> test(new Base());
//
//		RefCountPtr<Test> test2(new Test());
//	}
//	//����֪ʶѧϰ
//	{
//		SN_LOG("====================");
//		ConstBase* cb1 = new ConstBase();
//		ConstBase2 cb2;
//		cb2.PrintValue();
//		
//		cb1->FunA(cb2);
//		cb2.PrintValue();
//		cb1->FunB(&cb2);
//		cb2.PrintValue();
//		cb1->FunC(cb2);
//		cb2.PrintValue();
//		delete cb1;
//	}
//	//redfine �ض��常�ຯ��
//	{
//		SN_LOG("====================");
//		Child* child = new Child();
//		child->FunA();
//		//������ø��ຯ��������Ҫ����::����������
//		child->Parent::FunA();
//	}
//
//	{
//		SN_LOG("====================");
//		BinaryTree* bt = new BinaryTree();
//		bt->VisitTree();
//		bt->TwoTreeEqual();
//		bt->ReverTree();
//
//		delete bt;
//		bt = nullptr;
//	}

//	//Base KnowLedge
//	{
//		//Base tem1 = Base();
//		//Base tem2 = tem1;
//		//Base tem3;
//		//tem3 = tem1;
//		SN_LOG("==============");
//		Base* t1 = new Base();
//		Base* t2 = t1;
//
//		t2->BaseLD();
//		delete t1;
//	}
	//system("pause");
    TestSharePtr();
	getchar();
	return 0;
}