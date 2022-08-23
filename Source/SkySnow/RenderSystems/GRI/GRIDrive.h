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
#include "GRICommons.h"
#include "GRIResource.h"
#include "GRIResourceCreateInfo.h"
namespace SkySnow
{
	//根据不同平台创建不同的渲染API
	//渲染系统的接口将与Vulkan保持大体框架的一致，具体可看:vulkan_core.h
	//该部门接口主要为资源的创建&资源的重创建
	//渲染同步及锁机制，将在CommandBuffer&CommandBufferPool中实现
	//Commandbuffer encoding render commands are encoded in units of one pipeline and submitted in units of one pipeline 
	//Command commit to CommandBuffers,CommandBuffer commit to CommandQueue
	//CommandBufferPool alloc CommandBuffer
	//Commandbuffers are synchronized through events or memory barriers
	//Commandqueues are synchronized between semaphores
	//The CPU and GPU are synchronized through a fence
	//If the same thread has more than one encoder encoding it can have a CommandBufferPool of its own
	class GRIDrive
	{
	public:
		virtual ~GRIDrive() {}

		virtual GRIFeature GetGRIFeatureType() = 0;
		// Test:clear quad color
		virtual void GRIClearColor(float red, float green, float blue, float alpha) = 0;
		//GRICreate=======================================================================================================================
		//Create Vertex Shader
		virtual GRIVertexShaderRef GRICreateVertexShader(const char* vsCode) = 0;
		//Create Fragment Shader
		virtual GRIFragmentShaderRef GRTCreateFragmentShader(const char* fsCode) = 0;
		//Create Pipeline Shader Stage State
		virtual GRIPipelineShaderStateRef GRICreatePipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs) = 0;
		//Create Graphics Pipeline
		virtual GRIGraphicsPipelineStateRef GRICreateGraphicsPipelineState(const GRICreateGraphicsPipelineStateInfo& createInfo) = 0;
		//Create Buffer:index vertex SSBO
		virtual GRIBufferRef GRICreateBuffer(BufferUsageType usageType, int size,int stride,void* data) = 0;

		//vulkan is submit,metal is commit
		//virtual void Commit() = 0;
		//GRICreate=======================================================================================================================

		//GRISet==========================================================================================================================
		virtual void GRISetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset) = 0;
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) = 0;
		virtual void GRISetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState) = 0;
		virtual void GRISetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState) = 0;
		//GRISet==========================================================================================================================
	};
};
