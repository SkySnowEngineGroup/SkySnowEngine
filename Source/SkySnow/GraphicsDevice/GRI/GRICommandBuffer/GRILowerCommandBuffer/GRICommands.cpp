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
	void CmdBeginViewportCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRIBeginViewport();
	}
	void CmdEndViewportCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRIEndViewport();
	}
	void CmdSetBufferCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRISetBuffer(_BufferInfoId, _Buffer, _Offset);
	}
	void CmdDrawPrimitiveCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRIDrawPrimitive(_NumPrimitive, _NumInstance);
	}
	void CmdSetPipelineShaderCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRISetPipelineShader(_PipelineShaderState);
	}
	void CmdSetGraphicsPipelineCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRISetGraphicsPipeline(_PipelineState);
	}
	//===============================================================================
	void GRICreateVertexShaderCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRICreateVertexShader(_VsCode, _Handle);
	}

	void GRICreateFragmentShaderCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRICreateFragmentShader(_FsCode, _Handle);
	}

	void GRICreatePipelineShaderCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRICreatePipelineShader(_Handle);
	}

	void GRICreateBufferCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		 GRI->GRICreateBuffer(_UsageType, _Size, _Stride, _Data, _Handle);
	}

	void GRICreateGraphicsPipelineCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		GRI->GRICreateGraphicsPipeline(_PsoInfo,_Handle);
	}

    void GRICreateVertexDescriptorCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        GRI->GRICreateVertexDescriptor(_VertexElements, _Handle);
    }
}
