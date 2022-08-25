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

	void TestFun() 
	{
		SN_LOG("Call this TestFun.");
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

	struct TestFunA : public GRICommand<TestFunA>
	{
		TestFunA()
		{
		}
		void Execute(CommandBuffer& commandBuffer)
		{
			TestFun();
		}
	}; 

	class CommandBuffer
	{
	public:
		void EncoderTestFun()
		{
			TestFunA* ca = new TestFunA();
			root = ca;
		}

		void RenderCmd()
		{
			GRICommandBase* cmd = root;
			cmd->ExecuteCmd(*this);
		}
	private:
		GRICommandBase* root;
	};
}
