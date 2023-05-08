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
#include "GLCreateCommandBuffer.h"
#include "GLShaderResource.h"
#include "GLPipelineResource.h"
#include "GRIPipelineCache.h"
#include "GRI.h"
namespace SkySnow
{
	GLCreateCommandBuffer::GLCreateCommandBuffer()
	{

	}

	GLCreateCommandBuffer::~GLCreateCommandBuffer()
	{

	}
	//ResourceCreate====================================================================
	GRIVertexShaderRef GLCreateCommandBuffer::CreateVertexShader(const char* vsCode)
	{
		GRIVertexShaderRef handle = new GLVertexShader();
		Alloc_CommandCreate(GRICreateVertexShaderCommand, handle, vsCode);
		return handle;
	}

	GRIFragmentShaderRef GLCreateCommandBuffer::CreateFragmentShader(const char* fsCode)
	{
		GRIFragmentShaderRef handle = new GLFragmentShader();
		Alloc_CommandCreate(GRICreateFragmentShaderCommand, handle, fsCode);
		return handle;
	}

	GRIPipelineShaderRef GLCreateCommandBuffer::CreatePipelineShader(GRIVertexShader* vs, GRIFragmentShader* fs)
	{
		GRIPipelineShaderRef handle = new GLPipelineShader(vs, fs);
		Alloc_CommandCreate(GRICreatePipelineShaderCommand, handle);
		return handle;
	}

	GRIBufferRef GLCreateCommandBuffer::CreateBuffer(BufferUsageType usageType, int size, int stride, void* data)
	{
		GRIBufferRef handle = new GLBuffer(usageType, size, stride, data);
		Alloc_CommandCreate(GRICreateBufferCommand, handle, usageType, size, stride, data);
		return handle;
	}

	GRIGraphicsPipelineRef GLCreateCommandBuffer::CreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo)
	{
		GRIGraphicsPipelineRef handle;
		bool flag = _GPipelineCache->GetGraphicsPipeline<GLGraphicPipeline>(createInfo, handle);
		if (!flag)
			Alloc_CommandCreate(GRICreateGraphicsPipelineCommand, createInfo, handle);
		return handle;
	}
}