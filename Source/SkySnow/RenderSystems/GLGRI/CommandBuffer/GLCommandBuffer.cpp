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
#include "GLCommandBuffer.h"
#include "GLShader.h"
#include "GLShaderResource.h"
#include "GLBufferResource.h"
#include "GLPipelineResource.h"
namespace SkySnow
{
	GLCommandBuffer::GLCommandBuffer()
		: GRICommandBufferBase()
	{

	}

	GLCommandBuffer::~GLCommandBuffer()
	{
	}

	void GLCommandBuffer::CmdReset()
	{

	}
	void GLCommandBuffer::CmdBeginCommandBuffer()
	{

	}
	void GLCommandBuffer::CmdEndCommandBuffer()
	{

	}

	void GLCommandBuffer::CmdBeginRenderPass()
	{

	}
	void GLCommandBuffer::CmdEndRenderPass()
	{

	}
	//ResourceCreate====================================================================
	GRIVertexShaderRef GLCommandBuffer::CreateVertexShader(const char* vsCode)
	{
		GRIVertexShaderRef handle = new GLVertexShader();
		Alloc_CommandCreate(GRICreateVertexShaderCommand, handle, vsCode);
		return handle;
	}

	GRIFragmentShaderRef GLCommandBuffer::CreateFragmentShader(const char* fsCode)
	{
		GRIFragmentShaderRef handle = new GLFragmentShader();
		Alloc_CommandCreate(GRICreateFragmentShaderCommand,handle,fsCode);
		return handle;
	}

	GRIPipelineShaderStateRef GLCommandBuffer::CreatePipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs)
	{
		GRIPipelineShaderStateRef handle = new GLPipelineShaderState(vs,fs);
		Alloc_CommandCreate(GRICreatePipelineShaderStateCommand,handle);
		return handle;
	}

	GRIBufferRef GLCommandBuffer::CreateBuffer(BufferUsageType usageType, int size, int stride, void* data)
	{
		GRIBufferRef handle = new GLBuffer(usageType, size, stride, data);
		Alloc_CommandCreate(GRICreateBufferCommand,handle,usageType, size, stride, data);
		return handle;
	}

	GRIGraphicsPipelineStateRef GLCommandBuffer::CreateGraphicsPipelineState(const GRICreateGraphicsPipelineStateInfo& createInfo)
	{
		GRIGraphicsPipelineStateRef handle = new GLGraphicPipelineState(createInfo);
		Alloc_CommandCreate(GRICreateGraphicsPipelineStateCommand,createInfo, handle);
		return handle;
	}
	//ResourceSet====================================================================
	void GLCommandBuffer::CmdSetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset)
	{
		Alloc_CommandSet(CmdSetBufferCommand)(BufferInfoId, buffer, offset);
	}
	void GLCommandBuffer::CmdDrawPrimitive(int numPrimitive, int numInstance)
	{
		Alloc_CommandSet(CmdDrawPrimitiveCommand)(numPrimitive, numInstance);
	}
	void GLCommandBuffer::CmdSetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState)
	{
		Alloc_CommandSet(CmdSetPipelineShaderStateCommand)(pipelineShaderState);
	}
	void GLCommandBuffer::CmdSetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState)
	{
		Alloc_CommandSet(CmdSetGraphicsPipelineStateCommand)(pipelineState);
	}
}