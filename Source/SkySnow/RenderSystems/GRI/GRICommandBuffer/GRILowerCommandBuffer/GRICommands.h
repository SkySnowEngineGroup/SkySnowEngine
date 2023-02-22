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
#include "GRIResource.h"
#include "GRIResourceCreateInfo.h"
namespace SkySnow
{
	/*
	 *These instructions are data structures encapsulated for OpenGL 
	 *and lower versions of dx. They are not required for metal&vulkan&dx12. 
	 *The unified interface encapsulated in CommandBuffer delivers rendering 
	 *instructions directly to the gpu
	*/
	class GRICommandBuffer;
	struct GRICommandBase
	{
		virtual void ExecuteCommand(GRICommandBuffer& cmdBuffer) = 0;
		GRICommandBase* _Next = nullptr;
	};

	template<typename T>
	struct GRICommand : public GRICommandBase
	{
	public:
		void ExecuteCommand(GRICommandBuffer& cmdBuffer) override final
		{
			T* cmd = static_cast<T*>(this);
			cmd->Execute(cmdBuffer);
			cmd->~T();
		}
	};
    //RenderDrive Interface
	//======================================================================================================================
	struct GRINullCommand : public GRICommand<GRINullCommand>
	{
		void Execute(GRICommandBuffer& cmdBuffer) {}
	};
	//======================================================================================================================
	// RenderResource Set 
	struct CmdSetBufferCommand : public GRICommand<CmdSetBufferCommand>
	{
		CmdSetBufferCommand(int BufferInfoId, GRIBuffer* buffer, int offset)
			: _BufferInfoId(BufferInfoId)
			, _Offset(offset)
			, _Buffer(buffer)
		{

		}
		void Execute(GRICommandBuffer& cmdBuffer);

		int _BufferInfoId;
		int _Offset;
		GRIBuffer* _Buffer;	
	};
	struct CmdDrawPrimitiveCommand : public GRICommand<CmdDrawPrimitiveCommand>
	{
		CmdDrawPrimitiveCommand(int numPrimitive, int numInstance)
			: _NumPrimitive(numPrimitive)
			, _NumInstance(numInstance)
		{
		}
		void Execute(GRICommandBuffer& cmdBuffer);
		int _NumPrimitive;
		int _NumInstance;
	};
	struct CmdSetPipelineShaderStateCommand : public GRICommand<CmdSetPipelineShaderStateCommand>
	{
		CmdSetPipelineShaderStateCommand(GRIPipelineShaderState* pipelineShaderState)
			: _PipelineShaderState(pipelineShaderState)
		{
		}
		void Execute(GRICommandBuffer& cmdBuffer);
		GRIPipelineShaderState* _PipelineShaderState;
	};

	struct CmdSetGraphicsPipelineStateCommand : public GRICommand<CmdSetGraphicsPipelineStateCommand>
	{
		CmdSetGraphicsPipelineStateCommand(GRIGraphicsPipelineState* pipelineState)
			: _PipelineState(pipelineState)
		{
		}
		void Execute(GRICommandBuffer& cmdBuffer);
		GRIGraphicsPipelineState* _PipelineState;
	};
	//======================================================================================================================
	// RenderResource Create
	// CreateVertexShader
	struct GRICreateVertexShaderCommand : public GRICommand<GRICreateVertexShaderCommand>
	{
        GRICreateVertexShaderCommand(GRIVertexShaderRef& handle,const char* vsCode)
			: _VsCode(vsCode)
			, _Handle(handle)
		{
		}
		void Execute(GRICommandBuffer& cmdBuffer);

		const char*			_VsCode;
		GRIVertexShaderRef	_Handle;
	};

	struct GRICreateFragmentShaderCommand : public GRICommand<GRICreateFragmentShaderCommand>
	{
		GRICreateFragmentShaderCommand(GRIFragmentShaderRef& handle, const char* vsCode)
			: _FsCode(vsCode)
			, _Handle(handle)
		{
		}
		void Execute(GRICommandBuffer& cmdBuffer);

		const char*				_FsCode;
		GRIFragmentShaderRef	_Handle;
	};

	struct GRICreatePipelineShaderStateCommand : public GRICommand<GRICreatePipelineShaderStateCommand>
	{
		GRICreatePipelineShaderStateCommand(GRIPipelineShaderStateRef& handle)
			: _Handle(handle)
		{
		}
		void Execute(GRICommandBuffer& cmdBuffer);
		GRIPipelineShaderStateRef _Handle;
	};

	struct GRICreateBufferCommand : public GRICommand<GRICreateBufferCommand>
	{
		GRICreateBufferCommand(GRIBufferRef& handle,BufferUsageType usageType, int size, int stride, void* data)
			: _Handle(handle)
			, _UsageType(usageType)
			, _Size(size)
			, _Stride(stride)
			, _Data(data)
		{
		}

		void Execute(GRICommandBuffer& cmdBuffer);
		BufferUsageType _UsageType;
		int				_Size;
		int				_Stride;
		void*			_Data;
		GRIBufferRef	_Handle;
	};

	struct GRICreateGraphicsPipelineStateCommand : public GRICommand<GRICreateGraphicsPipelineStateCommand>
	{
		GRICreateGraphicsPipelineStateCommand(const GRICreateGraphicsPipelineStateInfo& createInfo, GRIGraphicsPipelineStateRef& handle)
			: _PsoInfo(createInfo)
			, _Handle(handle)
		{

		}
		void Execute(GRICommandBuffer& cmdBuffer);

		GRICreateGraphicsPipelineStateInfo _PsoInfo;
		GRIGraphicsPipelineStateRef _Handle;
	};
}
