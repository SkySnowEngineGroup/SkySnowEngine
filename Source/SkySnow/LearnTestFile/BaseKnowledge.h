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
namespace SkySnowLearning
{
	class Base
	{
	public:
		Base()
			: m_Ia(0)
		{
			SN_LOG("Construct.");
		}
		~Base() 
		{
			SN_LOG("DesConstruct.");
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
	//��д(����): Ҫ����෽��ǰ����virtual���ҷ���ֵ�������б����ͻ�����ͬ
	//����: Ҫ������б��ԭ������ͬ�����з���ֵ��ͬ�������أ�ʹ��ʱ��Ҫע�������
	//�ض���: Ҫ�󷽷����͸�����ͬ��������Բ�ͬ���Ҵ�ʱҪ���ø��෽��ʱֻ�ܲ���(������::������)������
	//        �����ඨ���������ͬ���ĳ�Ա�����������з���ͬ����Աʱ�����˻����ͬ��
	//        ����������ʹ�û����ͬ����Ա����ʾ��ʹ�������޶���--����::��Ա
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
}