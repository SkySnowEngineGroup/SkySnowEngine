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
#include "GRIModule.h"
#include "GRIDrive.h"

namespace SkySnow
{
	void CmdBeginViewportCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
		Drive()->GRIBeginViewport(_ViewPort,_RenderTexture);
	}
	void CmdEndViewportCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRIEndViewport(_ViewPort,_Present,_LockToVsync);
	}
	void CmdSetBufferCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRISetBuffer(_BufferInfoId, _Buffer, _Offset);
	}
	void CmdDrawPrimitiveCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRIDrawPrimitive(_NumPrimitive, _NumInstance);
	}
	void CmdSetPipelineShaderCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRISetPipelineShader(_PipelineShaderState);
	}
	void CmdSetGraphicsPipelineCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRISetGraphicsPipeline(_PipelineState);
	}
    void CmdSetShaderParameterCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        Drive()->GRISetShaderParameter(_PipelineShader, _UniformBuffer, _UBIndex);
    }
    void CmdUpdateUniformBufferCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        Drive()->GRIUpdateUniformBuffer(_UniformBuffer, _UBData);
    }

    void CmdSetUniformBufferDescriptorCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        Drive()->GRISetUniformBufferDescriptor(_UBDescriptor);
    }
    
    void CmdSetShaderTextureCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        Drive()->GRISetShaderTexture(_ShaderPipeline, _Texture, _TextureIndex);
    }
    
    void CmdSetShaderSamplerCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        Drive()->GRISetShaderSampler(_ShaderPipeline, _Sampler, _SamplerIndex);
    }
	//===============================================================================
    void GRIFlushResourceReleaseCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        GRIResManager::Instance().FlushResource();
    }
	void GRICreateVertexShaderCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateVertexShader(_ResourceData, _Handle);
	}

	void GRICreateFragmentShaderCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateFragmentShader(_ResourceData, _Handle);
	}

	void GRICreatePipelineShaderCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreatePipelineShader(_Handle);
	}

	void GRICreateBufferCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateBuffer(_UsageType, _Size, _Stride, _ResourceData, _Handle);
	}

	void GRICreateGraphicsPipelineCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateGraphicsPipeline(_PsoInfo,_Handle);
	}

    void GRICreateVertexDescriptorCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        Drive()->GRICreateVertexDescriptor(_VertexElementList, _Handle);
    }

    void GRICreateUniformBufferCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        Drive()->GRICreateUniformBuffer(_USlotList,_UBName,_UBType,_Handle);
    }
    
    void GRICreateUniformDescriptorCommand::Execute(GRICommandBufferBase& cmdBuffer)
    {
        Drive()->GRICreateUniformDescriptor(_UBSlotList, _Handle);
    }

	void GRICreateTexture2DCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateTexture2D(_Sizex, _Sizey, _Format, _NumMips, _NumSamples, _UsageType, _ResourceData, _Handle);
	}

	void GRICreateTexture2DArrayCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateTexture2DArray(_Sizex,_Sizey,_Sizez,_Format,_NumMips,_NumSamples,_UsageType, _ResourceData,_Handle);
	}

	void GRICreateTexture3DCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateTexture3D(_Sizex,_Sizey,_Sizez,_Format,_NumMips,_UsageType, _ResourceData,_Handle);
	}

	void GRICreateTextureCubeCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateTextureCube(_Size,_Format,_NumMips,_UsageType, _ResourceData,_Handle);
	}

	void GRICreateSamplerCommand::Execute(GRICommandBufferBase& cmdBuffer)
	{
        Drive()->GRICreateSampler(_State,_Handle);
	}
}
