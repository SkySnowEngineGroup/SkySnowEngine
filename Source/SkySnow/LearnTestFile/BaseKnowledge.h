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
	//重写(覆盖): 要求基类方法前加上virtual，且返回值及参数列表均需和基类相同
	//重载: 要求参数列表和原函数不同，仅有返回值不同不算重载，使用时需要注意二义性
	//重定义: 要求方法名和父类相同，其余可以不同，且此时要调用父类方法时只能采用(基类名::函数名)来调用
	//        派生类定义了与基类同名的成员，在派生类中访问同名成员时屏蔽了基类的同名
	//        在派生类中使用基类的同名成员，显示的使用类名限定符--类名::成员
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
		//重定义父类方法 redefined
		void FunA()
		{
			SN_LOG("Child Function A.");
		}
		//重写父类方法，或者叫覆盖父类方法
		virtual void FunB() override
		{
			SN_LOG("Child Function B, overrider Parent FunB.");
		}
	};
	//C中的NULL是void* ，C++中的NULL是0，C++中不可以将void*转为其他指针对象
	//c++中的nullptr是std::nullptr,可以转换为任意指针
	//建议使用nullptr解决二义性问题
	/*
	void Test(void* num)
	{
	}
	void Test(int num)
	{
	}

	void main()
	{
		//该行为是编译不过的，不知道调用那个函数
		Test(NULL);
	}
	*/

	//使用引用参数的原因
	//1. 开发人员能够修改调用函数中的数据对象
	//2. 通过传递引用而不是整个数据对象，可以提高运行速度
	//	 引用其实是指针的另外的一个别名
	//何时使用值传递
	//1. 数据对象较小，可传值:值传递会调用拷贝构造函数
	//2. 函数中不对对象数据进行修改，即使修改也是修改的临时变量中数据，不会影响对象本身数据
	//何时使用const修饰引用或指针
	//1. 不希望函数内对传递过来的对象值进行修改(数组、对象、数据结构)
	//2. 如果对象数据较小，可以使用值传递
	class ConstBase2
	{
	public:
		//构造函数
		ConstBase2()
			: m_IData(0)
		{
			SN_LOG("ConstBase2 Construct Function.");
		}
		//拷贝构造函数
		ConstBase2(const ConstBase2& other)
		{
			m_IData = other.m_IData;
			SN_LOG("ConstBase2 CopyConstruct Function.");
		}
		//析构函数
		~ConstBase2()
		{
			SN_LOG("ConstBase2 DesConstruct Function.");
		}
		//赋值操作符
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
		//构造函数
		ConstBase()
		{
			SN_LOG("ConstBase Construct Function.");
		}
		//拷贝构造函数
		ConstBase(const ConstBase& other)
		{
			SN_LOG("ConstBase CopyConstruct Function.");
		}
		//析构函数
		~ConstBase()
		{
			SN_LOG("ConstBase DesConstruct Function.");
		}
		//赋值操作符
		ConstBase& operator= (const ConstBase& other)
		{
			SN_LOG("ConstBase Operator = Function.");
		}
		//如果加了const修饰符，那么传递进来的对象是不被允许修改的
		void FunA(ConstBase2& value)
		{
			value.SetValue(1);
			SN_LOG("传递引用");
		}
		//如果加了const修饰符，那么传递进来的对象是不被允许修改的
		void FunB(ConstBase2* value)
		{
			value->SetValue(2);
			SN_LOG("传递值:指针传递");
		}
		//值传递方式，会先调用ConstBase2的拷贝构造函数生成一个临时的对象
		//即使修改了这个对象，但是也不会影响原来的对象的值。
		//因为值传递会调用对象拷贝构造函数，因此对于对象中数据较小的时候，
		//性能消耗不太明显，但是如果数据较大的情况下，就比较大了。
		void FunC(ConstBase2 value)
		{
			value.SetValue(3);
			SN_LOG("传递值2:非指针传递");
		}
	};
}