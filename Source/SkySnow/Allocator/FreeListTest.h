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
//Note:����һЩ��Ҫ���ǵ�ʵ�����⣬��Ҫһ�������ܼ��ڴ涼���õ��ڴ������Ҫ��Բ�ͬҵ�񳡾��Լ�����ʵ�ַ�ʽ���д���
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
//4. Buddy allocation(��������), automatic merging, can handle continuous multi - frame GPU memory management
//5. Thread - safe memory pool, suitable for multi - threaded processing
//And so on, these situations need to be taken into account
#include <iostream>
using namespace std;
namespace SkySnow
{
	//operator new operator delete
	//operator new[] operator delete[]
	//malloc free
	//new malloc������
	//1. malloc��free��c\c++���Եı�׼�⺯����new/delete��c++��������������Զ�ҡ������ͷ��ڴ�
	//2. new��malloc�빹�캯���Ľ���壬new������ָ�����������Ϣ����malloc��ָ����void���ͣ���Ҫǿת
	//3. new�����ڴ�ʧ�ܣ��׳��쳣��malloc����NULL
	//4. new��delete���Ա����أ���malloc������
	//5. new��delete���Զ����ù��캯������������������malloc��free����
	//6. malloc�����ڴ�ʧ�ܿ�realloc���·��䣬����new������
	//7. new���������Ƿ��Ӧ������Ӧ�ᱣ�棬malloc�����������ж�
	//8. new �ڲ�ʵ���˴�С�ļ��㡢����ת���ȹ�������malloc��Ҫ�����С������ת��
	//�ײ��߼�
	//1.new T����
	//	1.1. ����operator new(sizeof(T))���ú����ĺ���ԭ��Ϊvoid* operator new(size_t size)
	//	1.2. ����operator new�е�malloc(set_new_handle)���������ɹ������أ�
	//		 ����ʧ�ܣ�����ԭ�����ڴ�ռ䲻�㣩����ȡӦ�Դ�ʩset_new_handler�����Ӧ�Դ�ʩû�У��׳�һ���쳣
	//	1.3. ����һ�����캯�������캯����ʾ�������������Զ��ϳ�
	//2.delete p
	//	2.1. ����һ����������
	//	2.2. ����operator delete���ͷſռ��ַ
	//	2.3. ����free����
	//3.new T[N]
	//	3.1. ����operator new[] (N*sizeof(T))����������Ŀռ��ͷ�����4���ֽڵĿռ䣬�������N
	//	3.2. ����operator new����
	//	3.3. ����malloc����
	//	3.4. ����N�ι��캯�����������N������
	//	3.5. ���ص�һ���������ڵ��׵�ַ������ԭ�ռ�ĵ�ַ������ԭ�ռ�ĵ�ַ���ƫ��4��λ��
	//4.delete[] p
	//	4.1. ȡ��N���ڿռ��ǰ�ĸ��ֽ��У�{*((int*)P - 1) [(int*)((int)p - 4)]}
	//	4.2. ����N����������
	//	4.3. ����operator delete[] (p)
	//	4.4. ����operator delete
	//	4.5. ����free����

	//����һ��stl�ڲ���allocator������ʵ�ַ�ʽ�����ڴ�ռ�������빹�캯���ĵ��÷ֿ�
	//Ҳ��������������new�����õ�����������
	//����stl������Դ���г����ܿ����ĸ�������˵���佫new T�ײ�Ĳ�����ֿ�����
	//���������˳����������˵�ġ�
	//�����vector������˵����Reserve�������ǵ��õ�Allocator������δ���ù��캯��
	//��Resize��������˳�������Reserve��������������Construct�����������Reserve��Resize�ײ������
	//Resize���vector���������г�ʼ����ֵ�ģ��ı����size��������push_back�������������������ĩβ��ӣ�ֻ����[]������
	//Reserve���vector��������ֻ�������ڴ棬�ı����Capacity��������[]���ʣ�ֻ����push_back��instert����
	//push_back() ������β�����Ԫ��ʱ�����Ȼᴴ�����Ԫ�أ�Ȼ���ٽ����Ԫ�ؿ��������ƶ��������У�����ǿ����Ļ����º������������ǰ���������Ԫ�أ���
	//c++11�� emplace_back() ��ʵ��ʱ������ֱ��������β���������Ԫ�أ�ʡȥ�˿������ƶ�Ԫ�صĹ���
	template<typename T>
	struct Stl_Allocator
	{
		T* Allocator(size_t size)
		{
			//new T����������operator new��operator new ����malloc
			return (T*)::operator new(sizeof(T) * size);
		}

		void Deallocator(void* ptr,size_t size)
		{
			//�ͷŶ����ڴ�
			::operator delete(ptr, sizeof(T) * size);
		}

		void Construct(T* ptr,const T& val)
		{
			//�ö�λnew��ָ���ڴ��Ϲ�������,����T�Ŀ������캯��
			new ((void*)ptr) T(val);
		}

		void Destroy(T* ptr)
		{
			//��ʾ�ĵ��ö������������
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
