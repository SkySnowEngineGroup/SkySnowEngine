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
	//���ݲ�ͬƽ̨������ͬ����ȾAPI
	//��Ⱦϵͳ�Ľӿڽ���Vulkan���ִ����ܵ�һ�£�����ɿ�:vulkan_core.h
	//�ò��Žӿ���ҪΪ��Դ�Ĵ���&��Դ���ش���
	//��Ⱦͬ���������ƣ�����CommandBuffer&CommandBufferPool��ʵ��
	class GRICommandsCreate
	{
	public:
		virtual ~GRICommandsCreate() {}

		virtual GRIFeature GetGRIFeatureType() = 0;
		// Test:clear quad color
		virtual void GRIClearColor(float red, float green, float blue, float alpha) = 0;
		//Rendering Resource Create CMD
		/*
			�ӿڶ������ִ���ȾAPI����һ�£�����shader�����������ɫ�����ڴ���ShaderPipelineState��ʱ��
			������shader�Լ�������ɫ���������(�����OpenGL���������Ƿ�֧��BinaryShader��separateshader[Depend PipelineObject])
			����shader��һ����װΪShaderResourceView
			bgfx����һ��˼·�ǣ���drawcall����view�������֣�ÿһ��view�����Լ���һЩdrawcall����
		*/
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
	};
};