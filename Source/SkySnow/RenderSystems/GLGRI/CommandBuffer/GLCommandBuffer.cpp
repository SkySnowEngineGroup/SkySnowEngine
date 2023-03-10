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
	GLRenderCommandBuffer::GLRenderCommandBuffer()
		: GRIRenderCommandBuffer()
	{

	}

	GLRenderCommandBuffer::~GLRenderCommandBuffer()
	{
	}

	void GLRenderCommandBuffer::CmdReset()
	{

	}
	void GLRenderCommandBuffer::CmdBeginCommandBuffer()
	{

	}
	void GLRenderCommandBuffer::CmdEndCommandBuffer()
	{

	}

	void GLRenderCommandBuffer::CmdBeginRenderPass()
	{

	}
	void GLRenderCommandBuffer::CmdEndRenderPass()
	{

	}

	void GLRenderCommandBuffer::CmdBeginViewport()
	{
		Alloc_CommandSet(CmdBeginViewportCommand)();
	}

	void GLRenderCommandBuffer::CmdEndViewport()
	{
		Alloc_CommandSet(CmdEndViewportCommand)();
	}
	//ResourceCreate====================================================================
	GRIVertexShaderRef GLRenderCommandBuffer::CreateVertexShader(const char* vsCode)
	{
		GRIVertexShaderRef handle = new GLVertexShader();
		Alloc_CommandCreate(GRICreateVertexShaderCommand, handle, vsCode);
		return handle;
	}

	GRIFragmentShaderRef GLRenderCommandBuffer::CreateFragmentShader(const char* fsCode)
	{
		GRIFragmentShaderRef handle = new GLFragmentShader();
		Alloc_CommandCreate(GRICreateFragmentShaderCommand,handle,fsCode);
		return handle;
	}

	GRIPipelineShaderStateRef GLRenderCommandBuffer::CreatePipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs)
	{
		GRIPipelineShaderStateRef handle = new GLPipelineShaderState(vs,fs);
		Alloc_CommandCreate(GRICreatePipelineShaderStateCommand,handle);
		return handle;
	}

	GRIBufferRef GLRenderCommandBuffer::CreateBuffer(BufferUsageType usageType, int size, int stride, void* data)
	{
		GRIBufferRef handle = new GLBuffer(usageType, size, stride, data);
		Alloc_CommandCreate(GRICreateBufferCommand,handle,usageType, size, stride, data);
		return handle;
	}

	GRIGraphicsPipelineStateRef GLRenderCommandBuffer::CreateGraphicsPipelineState(const GRICreateGraphicsPipelineStateInfo& createInfo)
	{
		GRIGraphicsPipelineStateRef handle = new GLGraphicPipelineState(createInfo);
		Alloc_CommandCreate(GRICreateGraphicsPipelineStateCommand,createInfo, handle);
		return handle;
	}
	//ResourceSet====================================================================
	void GLRenderCommandBuffer::CmdSetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset)
	{
		Alloc_CommandSet(CmdSetBufferCommand)(BufferInfoId, buffer, offset);
	}
	void GLRenderCommandBuffer::CmdDrawPrimitive(int numPrimitive, int numInstance)
	{
		Alloc_CommandSet(CmdDrawPrimitiveCommand)(numPrimitive, numInstance);
	}
	void GLRenderCommandBuffer::CmdSetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState)
	{
		Alloc_CommandSet(CmdSetPipelineShaderStateCommand)(pipelineShaderState);
	}
	void GLRenderCommandBuffer::CmdSetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState)
	{
		Alloc_CommandSet(CmdSetGraphicsPipelineStateCommand)(pipelineState);
	}
}