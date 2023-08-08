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
        
        //Some Engine Globle Interface
        virtual void Init() = 0;
        
        virtual void Exit() = 0;

		virtual void GRIDriveStart() = 0;

		virtual void GRIDriveEnd() = 0;

		virtual GRIFeature GetGRIFeatureType() = 0;
		//about one viewport
		virtual GRIViewportStateRef GRICreateViewport(void* windowHandle,uint32 width,uint32 height,PixelFormat format,bool isFullScreen) = 0;
		virtual void GRIBeginViewport(GRIViewportStateRef& viewPort, GRITexture2DRef& renderTexture) = 0;
		virtual void GRIEndViewport(GRIViewportStateRef& viewPort, bool present, bool lockToVsync) = 0;
		//GRICreate=======================================================================================================================
		//Create Vertex Shader
		virtual void GRICreateVertexShader(const char* vsCode, GRIVertexShaderRef& handle) = 0;
		//Create Fragment Shader
		virtual void GRICreateFragmentShader(const char* fsCode, GRIFragmentShaderRef& handle) = 0;
		//Create Pipeline Shader Stage State
		virtual void GRICreatePipelineShader(GRIPipelineShaderRef& handle) = 0;
		//Create Graphics Pipeline
		virtual void GRICreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo, GRIGraphicsPipelineRef& handle) = 0;
        //Create Compute Pipeline
        virtual void GRICreateComputePipeline(const GRICreateComputePipelineInfo& createInfo,GRIComputePipelineRef& handle) = 0;
		//Create Buffer:index vertex SSBO
		virtual void GRICreateBuffer(BufferUsageType usageType, int size,int stride,void* data, GRIBufferRef& handle) = 0;
        //Create Vertex Declaration for VertexBuffer
        virtual void GRICreateVertexDescriptor(const VertexElementList& vdel,GRIVertexDescriptorRef& handle) = 0;
        //Create Uniform Buffer
        virtual void GRICreateUniformBuffer(const UniformSlotList& contents,const char* ubName,UniformBufferUsageType ubType,GRIUniformBufferRef& handle) = 0;
        //Create Uniform Buffer Declaration
        virtual void GRICreateUniformDescriptor(const UniformBufferList& ubl,GRIUniformBufferDescriptorRef& handle) = 0;
        //Texture2D
        virtual void GRICreateTexture2D(uint32 sizex,uint32 sizey,uint8 format,uint32 numMips,uint32 numSamples,TextureUsageType usageType,uint8* data,GRITexture2DRef& handle) = 0;
        //Texture2DArray
		virtual void GRICreateTexture2DArray(uint32 sizex,uint32 sizey,uint32 sizez,uint8 format,uint32 numMips,uint32 numSamples,TextureUsageType usageType,uint8* data,GRITexture2DArrayRef& handle) = 0;
		//Texture3D
		virtual void GRICreateTexture3D(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips,TextureUsageType usageType,uint8* data,GRITexture3DRef& handle) = 0;
		//TextureCube
		virtual void GRICreateTextureCube(uint32 size, uint8 format,uint32 numMips, TextureUsageType usageType,uint8* data,GRITextureCubeRef& handle) = 0;
        //SamplerState
        virtual void GRICreateSampler(const SamplerState& sState,GRISamplerStateRef& handle) = 0;
		//RenderState Rasterizer
		virtual void GRICreateRasterizer(const RasterizerStateInfo& state,GRIRasterizerStateRef& handle) = 0;
		//RenderState DepthStencil
		virtual void GRICreateDepthStencil(const DepthStencilStateInfo& state,GRIDepthStencilStateRef& handle) = 0;
		//RenderState BlendState
		virtual void GRICreateBlendState(const BlendStateInfo& state,GRIBlendStateRef& handle) = 0;
		//GRICreate=======================================================================================================================

		//Lower Render Deive Interface,so vulkan&metal not override this interface
		//GRISet==========================================================================================================================
        //Grahpichs Pipeline Interface
		virtual void GRIBeginRenderPass(const RenderPassInfo& rpInfo,const char* passName) = 0;
		virtual void GRINextRenderSubPass() = 0;
		virtual void GRIEndRenderPass() = 0;
        //Texture Update Data
        virtual void GRIUpdateTexture2D(GRITexture2DRef& tex2D,uint32 mipLevel,Texture2DRegion region,uint32 pitch,const uint8* data) {};
        virtual void GRIUpdateTexture3D(GRITexture3DRef& tex3D, uint32 mipLevel,Texture3DRegion region,uint32 rowPitch,uint8 depthPitch,const uint8* data) {};
        virtual void GRIUpdateTexture2DArray(GRITexture2DArrayRef& tex2DArray,uint32 textureIndex, uint32 mipLevel, Texture2DRegion region, uint32 pitch,const uint8* data) {};
        virtual void GRIUpdateTextureCube(GRITextureCubeRef& texCube,uint32 faceIndex,uint32 mipLevel, Texture2DRegion region, uint32 pitch, const uint8* data) {};
        virtual void GRISetShaderTexture(GRIPipelineShaderRef& graphicsShader,GRITextureRef& texture,uint32 textureIndex) {};
        virtual void GRISetShaderSampler(GRIPipelineShaderRef& graphicsShader,GRISamplerStateRef& sampler,uint32 samplerIndex) {}
        
		//Set Uniform Buffer Descriptor(Uniform Buffer Layout)
		virtual void GRISetUniformBufferDescriptor(GRIUniformBufferDescriptorRef& descriptor) {}
		//Update Uniform Buffer Data or Update Uniform Data
		virtual void GRIUpdateUniformBuffer(GRIUniformBufferRef& buffer,const UniformSlotList& contents) {}
		//Set Curr ShaderPipeline Uniform Buffer Index
		virtual void GRISetShaderParameter(GRIPipelineShaderRef& graphicsShader, GRIUniformBufferRef& buffer,int32_t bufferIndex) {}
        
		virtual void GRISetBuffer(int bufferIndex, GRIBufferRef& buffer, int offset) {}
        
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) {}
        
		virtual void GRISetPipelineShader(GRIPipelineShaderRef& pipelineShaderState) {}
        
		virtual void GRISetGraphicsPipeline(GRIGraphicsPipelineRef& pipelineState) {}
        //Compute Pipeline Interface
        //
		//GRISet==========================================================================================================================
	};
};
