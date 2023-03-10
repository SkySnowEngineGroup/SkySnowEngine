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
#include "GRICommands.h"
#include "GRICommandBuffer.h"
#include "GRI.h"
namespace SkySnow
{
	void CmdBeginViewportCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRIBeginViewport();
	}
	void CmdEndViewportCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRIEndViewport();
	}
	void CmdSetBufferCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRISetBuffer(_BufferInfoId, _Buffer, _Offset);
	}
	void CmdDrawPrimitiveCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRIDrawPrimitive(_NumPrimitive, _NumInstance);
	}
	void CmdSetPipelineShaderStateCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRISetPipelineShaderState(_PipelineShaderState);
	}
	void CmdSetGraphicsPipelineStateCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRISetGraphicsPipelineState(_PipelineState);
	}
	//===============================================================================
	void GRICreateVertexShaderCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRICreateVertexShader(_VsCode, _Handle);
	}

	void GRICreateFragmentShaderCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRICreateFragmentShader(_FsCode, _Handle);
	}

	void GRICreatePipelineShaderStateCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRICreatePipelineShaderState(_Handle);
	}

	void GRICreateBufferCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		 GRI->GRICreateBuffer(_UsageType, _Size, _Stride, _Data, _Handle);
	}

	void GRICreateGraphicsPipelineStateCommand::Execute(GRICommandBuffer& cmdBuffer)
	{
		GRI->GRICreateGraphicsPipelineState(_PsoInfo,_Handle);
	}
}