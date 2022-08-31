//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by sunguoqiang(SunGQ1987),wangcan(crygl),
//							 liuqian(SkySnow),zhangshuangxue(Calence)
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
using namespace std;
using namespace SkySnow;
namespace SkySnowLearning
{
	class CommandBuffer;
	class BufferT;
	template<typename T>
	class Handle
	{
	public:
		Handle()
			: _Data(nullptr)
		{
		}
		Handle(T* data)
			: _Data(data)
		{
		}
	public:
		//这里可以是指针，也可以是智能指针
		//如果是智能指针，驱动层就需要考虑风险指针的回收机制
		//如果是指针，那么对应的可以将Destroy函数也作为命令，回收机制放到RenderGraph中
		T* _Data;
	};
	//此处为GPUResource的封装抽象，这里是示例
	class BufferT
	{
	public:
		BufferT()
		{
			SN_LOG("BufferT Construct.");
		}

		void Log()
		{
			SN_LOG("BufferT Log Function.");
		}
	};
	using CreateHandle = Handle<BufferT>;
	//该函数对应驱动层的具体接口，这里是示例
	void SetBufferD(BufferT* buffer)
	{
		SN_LOG("Call SetBufferD.");
	}
	//该函数对应驱动层的具体接口，这里是示例
	BufferT* CreateBufferD()
	{
		SN_LOG("Call CreateBufferD.");
		return new BufferT();
	}
	

	class GRICommandBase
	{
	private:
		using CMDExeAndDes = void(*)(CommandBuffer& commandBuffer, GRICommandBase* cmd);
	public:
		GRICommandBase(CMDExeAndDes cmdFun)
			: _CallBackFun(cmdFun)
			, _Next(nullptr)
		{
		}

		void ExecuteCmd(CommandBuffer& commandBuffer)
		{
			_CallBackFun(commandBuffer,this);
		}
	public:
		GRICommandBase* _Next;
	private:
		CMDExeAndDes _CallBackFun;
	};
	template<typename Cmd>
	class GRICommand : public GRICommandBase
	{
	public:
		GRICommand()
			: GRICommandBase(CMDExeAndDes)
		{
		}
		static void CMDExeAndDes(CommandBuffer& commandBuffer, GRICommandBase* cmd)
		{
			Cmd* t_cmd = (Cmd*)cmd;
			t_cmd->Execute(commandBuffer);
			t_cmd->~Cmd();
		}
	};

	struct SetBuffer : public GRICommand<SetBuffer>
	{
		SetBuffer(CreateHandle handle)
			: _Handle(handle)
		{
		}
		void Execute(CommandBuffer& commandBuffer)
		{
			SetBufferD(_Handle._Data);
		}
	public:
		CreateHandle _Handle;
	}; 

	struct CreateBuffer :public GRICommand<CreateBuffer>
	{
	public:
		CreateBuffer(CreateHandle handle)
			: _Handle(handle)
		{
		}

		void Execute(CommandBuffer& commandBuffer)
		{
			_Handle._Data = CreateBufferD();
		}
	public:
		CreateHandle _Handle;
	};

	class CommandBuffer
	{
	public:
		CommandBuffer()
			: _Head(new GRICommandBase(nullptr))
		{
		}

		~CommandBuffer()
		{
			if (_Head)
			{
				delete _Head;
				_Head = nullptr;
			}
		}
		void EncoderSetBuffer(CreateHandle ch)
		{
			SetBuffer* sb = new SetBuffer(ch);
			_Curr->_Next = sb;
			_Curr = _Curr->_Next;
		}
		CreateHandle EncoderCreateBuffer()
		{
			Handle<BufferT> handle;
			if (handle._Data == nullptr)
			{
				SN_LOG("Data is Null.");
			}
			CreateBuffer* cb = new CreateBuffer(handle);
			_Curr->_Next = cb;
			_Curr = _Curr->_Next;
			return handle;
		}

		void RenderCmd()
		{
			GRICommandBase* cmdTemp;
			cmdTemp = _Head->_Next;
			while (cmdTemp)
			{
				cmdTemp->ExecuteCmd(*this);
				cmdTemp = cmdTemp->_Next;
			}
		}
	private:
		GRICommandBase* _Head;
		GRICommandBase* _Curr{ _Head };
	};
}
