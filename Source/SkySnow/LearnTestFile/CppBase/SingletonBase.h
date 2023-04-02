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
#include "Ptr.h"
#include <mutex>
#include "LogAssert.h"
namespace SkySnowLearning
{
	//懒汉模式
	class LazySingleton
	{
	private:
		LazySingleton()
		{
			SN_LOG("LazySingleton Construct.");
		}
	public:
		LazySingleton(const LazySingleton& other) = delete;
		LazySingleton& operator =(const LazySingleton& other) = delete;
		~LazySingleton()
		{
			SN_LOG("LazySingleton Destruct.");
		}
		void Release()
		{
			if (m_Instance)
			{
				delete m_Instance;
				m_Instance = nullptr;
			}
		}
		static LazySingleton* GetInstance()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new LazySingleton();
			}
			return m_Instance;
		}
	private:
		static LazySingleton* m_Instance;
	};
	LazySingleton* LazySingleton::m_Instance = nullptr;
	//懒汉模式下:使用匿名内部类来管理内存回收
	class LazySingletonLocalSt
	{
	private:
		LazySingletonLocalSt()
		{
			SN_LOG("LazySingletonLocalSt Construct.");
		}
		class GC
		{
		public:
			~GC()
			{
				if (m_Instance)
				{
					delete m_Instance;
					m_Instance = nullptr;
				}
			}
		};
	public:
		LazySingletonLocalSt(const LazySingletonLocalSt& other) = delete;
		LazySingletonLocalSt& operator =(const LazySingletonLocalSt& other) = delete;
		~LazySingletonLocalSt()
		{
			SN_LOG("LazySingletonLocalSt Destruct.");
		}

		static LazySingletonLocalSt* GetInstance()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new LazySingletonLocalSt();
			}
			return m_Instance;
		}
	private:
		static LazySingletonLocalSt* m_Instance;
		static GC gc;
	};
	LazySingletonLocalSt* LazySingletonLocalSt::m_Instance = nullptr;
	//懒汉模式的单例:线程安全，智能指针管理内存
	class LazySingletonTS
	{
	private:
		LazySingletonTS()
		{
			SN_LOG("LazySingletonTS Construct.");
		}
		
	public:
		LazySingletonTS(const LazySingletonTS& other) = delete;
		LazySingletonTS& operator =(const LazySingletonTS& other) = delete;
		~LazySingletonTS()
		{
			SN_LOG("LazySingletonTS Destruct.");
		}

		static std::shared_ptr<LazySingletonTS> GetInstance()
		{
			if (m_Instance == nullptr)
			{
				std::lock_guard<std::mutex> lk(m_Mutex);
				if (m_Instance == nullptr)
				{
					m_Instance = std::shared_ptr<LazySingletonTS>(new LazySingletonTS());
				}
			}
			return m_Instance;
		}

	private:
		static std::shared_ptr<LazySingletonTS> m_Instance;
		static std::mutex m_Mutex;
	};
	std::shared_ptr<LazySingletonTS> LazySingletonTS::m_Instance = nullptr;
	std::mutex LazySingletonTS::m_Mutex;

	//懒汉局部静态变量模式:线程安全的
	class LazySingletonLocal
	{
	private:
		LazySingletonLocal()
		{
			SN_LOG("LazySingletonLocal Construct.");
		}
	public:
		LazySingletonLocal(const LazySingletonLocal& other) = delete;
		LazySingletonLocal& operator =(const LazySingletonLocal& other) = delete;
		~LazySingletonLocal()
		{
			SN_LOG("LazySingletonLocal Destruct.");
		}

		static LazySingletonLocal* GetInstance()
		{
			static LazySingletonLocal instance;
			return &instance;
		}
	private:

	};

	//懒汉模式: 线程安全的单例
	class HungrySingleton
	{
	private:
		HungrySingleton()
		{
			SN_LOG("HungrySingleton Construct.");
		}
		class GC
		{
			~GC()
			{
				if (m_Instance)
				{
					delete m_Instance;
					m_Instance = nullptr;
				}
			}
		};
	public:
		HungrySingleton(const HungrySingleton& other) = delete;
		HungrySingleton& operator =(const HungrySingleton& other) = delete;
		~HungrySingleton()
		{
			SN_LOG("HungrySingleton Destruct.");
		}

		static HungrySingleton* GetInstance()
		{
			return m_Instance;
		}

	private:
		static HungrySingleton* m_Instance;
		static GC m_Gc;
	};
	HungrySingleton* HungrySingleton::m_Instance = new HungrySingleton();
}