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
//Note:这是一些需要考虑的实际问题，想要一个灵活及性能及内存都良好的内存管理，需要针对不同业务场景以及各种实现方式进行处理
//This is an example of a memory pool. The real engine can't be so simple. 
//It's just a simple review of some basic concepts of memory pools.
//This is a simple freelist method. The real engine is definitely not such a simple method.
//Multiple business scenarios must be considered
//1. and multi-threaded access conflicts and efficiency issues (minimum locks and thread local variables) must be considered.
//2. Address shaders Offset avoids the problem of inefficient cacheline (processing an offset during allocation),
//3. considers the memory shrinking scheme (Slab processing method), 
//4. and needs to deal with the situation where multiple CPUs access the same cache in the case of multi-core (paging processing)

//According to the usage scenarios of the engine, various implementation schemes of memory allocation need to be considered.
//1. Linear memory allocation; it is linear growth, suitable for the processing of rendering state dataand skeletal animation data of each frame, 
//   and it is easy to support lockfreeand index increment operations
//2. Stack allocator; suitable for level resource loading, can be released on demand, as the backend of other allocators
//3. Freelist allocation is suitable for particle effect buffer pool, but its memory is not continuous, which will cause cache_lineand multiple 
//   CPUs to access the same cached data, which should be considered
//4. Buddy allocation(伙伴分配器), automatic merging, can handle continuous multi - frame GPU memory management
//5. Thread - safe memory pool, suitable for multi - threaded processing
//And so on, these situations need to be taken into account
#include <iostream>
using namespace std;
namespace SkySnow
{
	//operator new operator delete
	//operator new[] operator delete[]
	//malloc free
	//new malloc的区别
	//1. malloc与free是c\c++语言的标准库函数，new/delete是c++的运算符，都可以动摇申请和释放内存
	//2. new是malloc与构造函数的结合体，new出来的指针带有类型信息，而malloc的指针是void类型，需要强转
	//3. new申请内存失败，抛出异常，malloc返回NULL
	//4. new和delete可以被重载，但malloc不可以
	//5. new和delete会自动调用构造函数和析构函数，但是malloc与free不会
	//6. malloc申请内存失败可realloc重新分配，但是new不可以
	//7. new会检查类型是否对应，不对应会保存，malloc不进行类型判断
	//8. new 内部实现了大小的计算、类型转换等工作，单malloc需要计算大小及类型转换
	//底层逻辑
	//1.new T类型
	//	1.1. 调用operator new(sizeof(T))，该函数的函数原型为void* operator new(size_t size)
	//	1.2. 调用operator new中的malloc(set_new_handle)，如果申请成功，返回；
	//		 申请失败（可能原因是内存空间不足），采取应对措施set_new_handler，如果应对措施没有，抛出一个异常
	//	1.3. 调用一个构造函数。构造函数显示给出，编译器自动合成
	//2.delete p
	//	2.1. 调用一个析构函数
	//	2.2. 调用operator delete，释放空间地址
	//	2.3. 调用free函数
	//3.new T[N]
	//	3.1. 调用operator new[] (N*sizeof(T))，会在申请的空间的头部多给4个字节的空间，用来存放N
	//	3.2. 调用operator new函数
	//	3.3. 调用malloc函数
	//	3.4. 调用N次构造函数，构造出来N个对象
	//	3.5. 返回第一个对象所在的首地址，不是原空间的地址，而是原空间的地址向后偏移4个位置
	//4.delete[] p
	//	4.1. 取出N（在空间的前四个字节中）{*((int*)P - 1) [(int*)((int)p - 4)]}
	//	4.2. 调用N次析构函数
	//	4.3. 调用operator delete[] (p)
	//	4.4. 调用operator delete
	//	4.5. 调用free函数

	//这是一个stl内部的allocator的类似实现方式，将内存空间的申请与构造函数的调用分开
	//也是上面所描述的new的内置的两个操作。
	//这在stl的容器源码中常常能看到的概念，其简单来说，其将new T底层的操作拆分开来了
	//但是其调用顺序是上面所说的。
	//针对于vector容器来说，其Reserve函数，是调用的Allocator，但并未调用构造函数
	//其Resize函数，是顺序调用了Reserve函数，并调用了Construct函数，这就是Reserve与Resize底层的区别
	//Resize后的vector容器，是有初始化初值的，改变的是size，不能用push_back函数，用这个是在容器末尾添加，只能用[]操作符
	//Reserve后的vector容器，是只申请了内存，改变的是Capacity，不能用[]访问，只能用push_back及instert插入
	//push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；
	//c++11中 emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程
	template<typename T>
	struct Stl_Allocator
	{
		T* Allocator(size_t size)
		{
			//new T操作，调用operator new，operator new 调用malloc
			return (T*)::operator new(sizeof(T) * size);
		}

		void Deallocator(void* ptr,size_t size)
		{
			//释放对象内存
			::operator delete(ptr, sizeof(T) * size);
		}

		void Construct(T* ptr,const T& val)
		{
			//用定位new在指定内存上构建对象,调用T的拷贝构造函数
			new ((void*)ptr) T(val);
		}

		void Destroy(T* ptr)
		{
			//显示的调用对象的析构函数
			ptr->~T();
		}
	};

	template<int ObjSize, int NumObj = 10>
	class FreeListTest
	{
	private:
		struct FreeNode
		{
			FreeNode*	m_Next;
			char		m_Data[ObjSize];
		};

		struct MemoryBlock
		{
			MemoryBlock*	m_Next;
			FreeNode		m_Data[NumObj];
		};

	public:
		FreeListTest()
			: m_FreeNodeHeader(nullptr)
			, m_MemoryBlockHeader(nullptr)
		{
		}

		~FreeListTest()
		{
			MemoryBlock* ptr;
			while (m_MemoryBlockHeader)
			{
				ptr = m_MemoryBlockHeader->m_Next;
				delete m_MemoryBlockHeader;
				m_MemoryBlockHeader = ptr;
			}
		}
		void* Malloc();
		void Free(void* ptr);
	private:
		FreeNode* m_FreeNodeHeader;
		MemoryBlock* m_MemoryBlockHeader;
	};

	template<int ObjSize, int NumObj>
	void* FreeListTest<ObjSize, NumObj>::Malloc()
	{
		if (m_FreeNodeHeader == nullptr)
		{
			MemoryBlock* newBlock = new MemoryBlock();
			newBlock->m_Next = nullptr;
			m_FreeNodeHeader = &newBlock->m_Data[0];

			for (int i = 1; i < NumObj; i++)
			{
				newBlock->m_Data[i - 1].m_Next = &newBlock->m_Data[i];
			}
			newBlock->m_Data[NumObj - 1].m_Next = nullptr;

			if (m_MemoryBlockHeader == nullptr)
			{
				m_MemoryBlockHeader = newBlock;
			}
			else
			{
				newBlock->m_Next = m_MemoryBlockHeader;
				m_MemoryBlockHeader = newBlock;
			}
		}

		void* freeNode = m_FreeNodeHeader;
		m_FreeNodeHeader = m_FreeNodeHeader->m_Next;
		return freeNode;
	}

	template<int ObjSize, int NumObj>
	void FreeListTest<ObjSize, NumObj>::Free(void* ptr)
	{
		FreeNode* pNode = (FreeNode*)ptr;
		pNode->m_Next = m_FreeNodeHeader;
		m_FreeNodeHeader = pNode;
	}
}
