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
namespace SkySnowLearning
{
	//std::move�����Ʋ���������Դ���������Ȩת�Ƶ���ǰ������
	// 	   ����ȥ�����õĲ�������
	//std::forward������ת��������Դ�����ֵ���Բ���
	//	   ����ǿ������ת����ʹ��static_caseȥ��

	/*
		���&ǳ����
		ǳ����
		  ���������Ա����:string\number\object\Array
		  ��������(string\number)����ô�����������͵�ֵ
		  �������ͣ��������ڴ��ַ����ԭ����ָͬһ���ڴ��ַ
		���
		  ���������Ա����:string\number\object\Array
		  ��������(string\number)����ô�����������͵�ֵ
		  �������ͣ�������ָ�룬����ָ��ָ�����ݽ��п�������ԭ����ָ��ͬ���ڴ��ַ
	*/

	//����cast���ô�
	/*	1. dynamic_cast<T>
	 *	   ��������̳���������������ʱ���TypeInfo(RTTI)������Ƿ��д��麯��δ��������д
	 *     �ô�
	 *         1.1 ����������֮��ת��:��ת��װ�����Ͱ�ȫ��
	 *         1.2 ������֮��Ľ���ת��
	 *	2. static_cast<T>
	 *     ���ڱ��������̳��������ǲ����������ڼ��TypeInfo(RTTI)
	 *     �ô�
	 *		   2.1 ����������֮��ת��:����ת���������Ͱ�ȫ����֮���Ͳ���ȫ
	 *		   2.2 ��������ת�����������ڼ�飬���Ͳ���ȫ
	 *         2.3 ��ָ��ת��ΪĿ�����Ϳ�ָ��
	 *         2.4 �κ�����ת��Ϊvoid����
	 *	3. reinterpret_cast<T>
	 *     �����������Ŀ���������תΪָ����������(�������:������ָ��)
	 *     ֻ�Ǹı����ݵĶ����Ƹ�ʽ�����ǲ����ı�����ֵ
	 *     �ô�
	 *		   3.1 ��ָ��תΪĿ��ָ�����ͣ�ֻ�ı�ָ�����ͣ������ı�ָ������
	 *         3.2 ������תΪĿ��������ͣ�ֻ�ı�������ͣ������ı��������
	 *     ע���
	 *         3.2.1 ��������ǵ;���ת�߾��ȣ����ⲻ̫�󣬵�������߾���ת�;��ȣ��ᱻ�ض�
	 *         3.2.2 ָ��ָ��Ķ����С����Ŀ������ָ��Ķ�����ô�ᾫ�Ƚضϣ����ֲ���Ԥ������
	 *	4. cons_cast<T>
	 *     ���������ת�����͵�const��volatile����
	 *     �ô�
	 *         4.1 ������ָ��תΪ�ǳ���ָ�룬������ָ��ԭ���Ķ���
	 *         4.2 ����������תΪ�ǳ������ã�������ָ��ԭ���Ķ���
	 */
	class Move
	{
	public:
		Move() 
		{
			SN_LOG("Move Construct.");
		}
		~Move() 
		{
			SN_LOG("Move DesConstruct.");
		}

		Move(const Move& input) 
		{
			SN_LOG("Move Copy Construct.");
		}

		Move& operator=(const Move& input)
		{
			SN_LOG("Move = operator.");
		}
		
		Move(Move&& input) 
		{
			SN_LOG("Move Move Construct.");
		}

		Move& operator =(Move&& other)
		{
			SN_LOG("Move Move = operator.");
			return *this;
		}

		void Test(Move* value)
		{

		}
	};

	/*
	������ʽ������ָ����÷�
	*/

	class Test : public SkySnow::RefThreadSafeCounted
	{
	public:
		Test()
			: RefThreadSafeCounted()
		{
			SN_LOG("Test Construct.");
		}

		~Test()
		{
			SN_LOG("Test DesConstruct.");
		}
	};
	class Base
	{
	public:
		Base()
			: m_Ia(0)
		{
			SN_LOG("Base Construct.");
		}
		~Base() 
		{
			SN_LOG("Base DesConstruct.");
		}

		Base(const Base& other)
		{
			m_Ia = other.m_Ia;
			SN_LOG("Copy Construct.");	
		}

		Base& operator=(const Base& other)
		{
			//if (this != &other)
			{
				m_Ia = other.m_Ia;
				SN_LOG("Copy operator Construct.");
			}
			return *this;
		}

		void BaseLD()
		{
			int* count = new int(1);

			(*count)++;
			SN_LOG("count int pointer value is:%d",*count);
		}
	private:
		int m_Ia;
	};
	//��������̵�������ʽ: �̳С���װ����̬
	//��̬:(��̬&��̬��̬)
	//  ��д(����)<��̬>: Ҫ����෽��ǰ����virtual���ҷ���ֵ�������б����ͻ�����ͬ
	//  ����<��̬>: Ҫ������б��ԭ������ͬ�����з���ֵ��ͬ�������أ�ʹ��ʱ��Ҫע�������
	//  �ض���<��̬>: Ҫ�󷽷����͸�����ͬ��������Բ�ͬ���Ҵ�ʱҪ���ø��෽��ʱֻ�ܲ���(������::������)������
	//          �����ඨ���������ͬ���ĳ�Ա�����������з���ͬ����Աʱ�����˻����ͬ��
	//          ����������ʹ�û����ͬ����Ա����ʾ��ʹ�������޶���--����::��Ա
	/*
	�������ļ���ԭ��
		1. ��һְ��ԭ��(Single Responsibility Principle)
		   ÿһ����Ӧ��רע����һ�����顣 �������ھۣ������
		2. ����ԭ��Open Close Principle��
		   һ���������չ���ţ����޸Ĺرա���������ĸĶ���ͨ�����Ӵ�����еģ��������޸����д���
		3. �����滻ԭ��Liskov Substitution Principle��
		   ���κθ�����ֵĵط����������������������
		4. ��������ԭ��Dependence Inversion Principle��
		   Ҫ�����ڳ��󣬲�Ҫ�����ھ���ʵ��
		5. �ӿڸ���ԭ��Interface Segregation Principle��
		   Ӧ��Ϊ�ͻ����ṩ������С�ĵ����Ľӿڣ��������ṩ����ܵĽӿ�
		6. ������ԭ��Law Of Demeter��
		   һ������Ӧ�������ٵ�����������֮�䷢���໥���ã�ʹ��ϵͳ����ģ����Զ���
		7. ���/�ۺϸ���ԭ��Composite/Aggregate Reuse Principle��
		   ����ʹ�����/�ۺϵķ�ʽ��������ʹ�ü̳�
	
	*/
	class Parent
	{
	public:
		Parent()
		{
			SN_LOG("Parent Construct.");
		}

		virtual ~Parent()
		{
			SN_LOG("Parent DesConstruct.");
		}
		
		void FunA()
		{
			SN_LOG("Parent Function A.");
		}
		//����
		void FunA(int vi)
		{
			SN_LOG("Parent Function A,But Overload.");
		}
		virtual void FunB()
		{
			SN_LOG("Parent Function B.");
		}
	};

	class Child : public Parent
	{
	public:
		Child()
		{
			SN_LOG("Child Construct.");
		}
		
		~Child()
		{
			SN_LOG("Child DesConstruct.");
		}
		//�ض��常�෽�� redefined
		void FunA()
		{
			SN_LOG("Child Function A.");
		}
		//��д���෽�������߽и��Ǹ��෽��
		virtual void FunB() override
		{
			SN_LOG("Child Function B, overrider Parent FunB.");
		}
	};
	//C�е�NULL��void* ��C++�е�NULL��0��C++�в����Խ�void*תΪ����ָ�����
	//c++�е�nullptr��std::nullptr,����ת��Ϊ����ָ��
	//����ʹ��nullptr�������������
	/*
	void Test(void* num)
	{
	}
	void Test(int num)
	{
	}

	void main()
	{
		//����Ϊ�Ǳ��벻���ģ���֪�������Ǹ�����
		Test(NULL);
	}
	*/

	//ʹ�����ò�����ԭ��
	//1. ������Ա�ܹ��޸ĵ��ú����е����ݶ���
	//2. ͨ���������ö������������ݶ��󣬿�����������ٶ�
	//	 ������ʵ��ָ��������һ������
	//��ʱʹ��ֵ����
	//1. ���ݶ����С���ɴ�ֵ:ֵ���ݻ���ÿ������캯��
	//2. �����в��Զ������ݽ����޸ģ���ʹ�޸�Ҳ���޸ĵ���ʱ���������ݣ�����Ӱ�����������
	//��ʱʹ��const�������û�ָ��
	//1. ��ϣ�������ڶԴ��ݹ����Ķ���ֵ�����޸�(���顢�������ݽṹ)
	//2. ����������ݽ�С������ʹ��ֵ����
	class ConstBase2
	{
	public:
		//���캯��
		ConstBase2()
			: m_IData(0)
		{
			SN_LOG("ConstBase2 Construct Function.");
		}
		//�������캯��
		ConstBase2(const ConstBase2& other)
		{
			m_IData = other.m_IData;
			SN_LOG("ConstBase2 CopyConstruct Function.");
		}
		//��������
		~ConstBase2()
		{
			SN_LOG("ConstBase2 DesConstruct Function.");
		}
		//��ֵ������
		ConstBase2& operator= (const ConstBase2& other)
		{
			SN_LOG("ConstBase2 Operator = Function.");
		}

		void SetValue(const int value)
		{
			m_IData = value;
		}

		void PrintValue()
		{
			SN_LOG("Current Value is:%d",m_IData);
		}
	private:
		int m_IData;
	};
	class ConstBase
	{
	public:
		//���캯��
		ConstBase()
		{
			SN_LOG("ConstBase Construct Function.");
		}
		//�������캯��
		ConstBase(const ConstBase& other)
		{
			SN_LOG("ConstBase CopyConstruct Function.");
		}
		//��������
		~ConstBase()
		{
			SN_LOG("ConstBase DesConstruct Function.");
		}
		//��ֵ������
		ConstBase& operator= (const ConstBase& other)
		{
			SN_LOG("ConstBase Operator = Function.");
		}
		//�������const���η�����ô���ݽ����Ķ����ǲ��������޸ĵ�
		void FunA(ConstBase2& value)
		{
			value.SetValue(1);
			SN_LOG("��������");
		}
		//�������const���η�����ô���ݽ����Ķ����ǲ��������޸ĵ�
		void FunB(ConstBase2* value)
		{
			value->SetValue(2);
			SN_LOG("����ֵ:ָ�봫��");
		}
		//ֵ���ݷ�ʽ�����ȵ���ConstBase2�Ŀ������캯������һ����ʱ�Ķ���
		//��ʹ�޸���������󣬵���Ҳ����Ӱ��ԭ���Ķ����ֵ��
		//��Ϊֵ���ݻ���ö��󿽱����캯������˶��ڶ��������ݽ�С��ʱ��
		//�������Ĳ�̫���ԣ�����������ݽϴ������£��ͱȽϴ��ˡ�
		void FunC(ConstBase2 value)
		{
			value.SetValue(3);
			SN_LOG("����ֵ2:��ָ�봫��");
		}
	};
	/*
	���μ̳У���̳н����������ͳ�Ա������
	�龰:
		����A��������B�̳�A��������C�̳�A��������D�̳�B��C
		����:
			1. ��������: ��D�б�������A������
			2. ������: D�е��ú��������������B����CΪ�н�������A(����ͨ��[����::������]��ȷ��)
		����:
			1. D��Ҫ��ʾ����A�Ĺ��캯����������ظ�����Ķ�����
			2. ��̳У���class���ڼ̳��У�����virtual�ؼ���
		ԭ��
			1. ������B��C��̳�A��D�̳�B��C������ͨ��[����::������]������ֻ��һ��A��ʵ��
			2. ������D�м̳�B��C�е�һ���麯�����麯����ָ��
	*/

	class A
	{
	public:
		A() 
		{
		}
	};

	class B : virtual public A
	{
	public:
		B() :A()
		{
		}
	};
	class C : virtual public A
	{
	public:
		C() :A()
		{
		}
	};

	class D : public B,public C
	{
	public:
		D() : A(), B(), C()
		{
		}
	};

	class BaseCon
	{
	public:
		BaseCon() 
		{
			SN_LOG("BaseCon Construct.");
		}
		~BaseCon()
		{
			SN_LOG("BaseCon Destruct.");
		}
	};

	class BaseCon1
	{
	public:
		BaseCon1()
		{
			SN_LOG("BaseCon1 Construct.");
		}
		virtual ~BaseCon1()
		{
			SN_LOG("BaseCon1 Destruct.");
		}
	};

	class ChildCon : public BaseCon
	{
	public:
		ChildCon()
		{
			SN_LOG("ChildCon Construct.");
		}

		~ChildCon()
		{
			SN_LOG("ChildCon Destruct.");
		}
	};

	class ChildCon1 : public BaseCon1
	{
	public:
		ChildCon1()
		{
			SN_LOG("ChildCon1 Construct.");
		}
		~ChildCon1()
		{
			SN_LOG("ChildCon1 Destruct.");
		}
	};
	//���캯��˳���ȸ��࣬������  
	//��������˳�������࣬����
	//�ڴ��й©�����
	//�����������������Ϊ�麯��
	//��ô������������Parent* parent = new Child()��
	//              �������:��ֻ���ø�����������������������������������
	static void TestChildCon()
	{
		SN_LOG("=====================Test1==");
		//test1
		BaseCon* b1 = new BaseCon();
		delete b1;
		SN_LOG("=====================");
		BaseCon* c1 = new ChildCon();
		delete c1;
		SN_LOG("=====================");
		ChildCon* c2 = new ChildCon();
		delete c2;
		SN_LOG("=====================Test2==");
		//test2
		BaseCon1* b11 = new BaseCon1();
		delete b11;
		SN_LOG("=====================");
		BaseCon1* c11 = new ChildCon1();
		delete c11;
		SN_LOG("=====================");
		ChildCon1* c22 = new ChildCon1();
		delete c22;
		SN_LOG("=====================");
	}
}