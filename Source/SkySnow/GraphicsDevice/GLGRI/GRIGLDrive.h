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

#include "GRIDrive.h"
#if PLATFORM == PLATFORM_ANDROID
#	include "GLESAndroid.h"
#elif PLATFORM == PLATFORM_IOS
#	include "GLESIos.h"
#elif PLATFORM == PLATFORM_WINDOW
#	include "GLWindow.h"
#elif PLATFORM == PLATFORM_MAC
#	include "GLMac.h"
#endif

#include "GLPipelineResource.h"
#include "GLViewportResource.h"
namespace SkySnow
{
	/*
		brief: Each real-time rendering API (GRI) unifies the base class of the external interface. 
			   Different rendering APIs inherit from this class and implement the functions of 
			   different APIs with the same capability
	*/
    //TODO: Function description and parameter description
	class GRIGLDrive : public GRIDrive
	{
	public:
		GRIGLDrive();

        ~GRIGLDrive();
        
        virtual void Init() final override;
        
        virtual void Exit() final override;

		virtual void GRIBeginViewport(GRIViewportStateRef& viewPort, GRITexture2DRef& renderTexture) final override;
		virtual void GRIEndViewport(GRIViewportStateRef& viewPort, bool present, bool lockToVsync) final override;
        virtual GRIViewportStateRef GRICreateViewport(void* windowHandle,uint32 width,uint32 height,PixelFormat format,bool isFullScreen) final override;
		//GRICreate=================================================================================================================================
		GRIFeature GetGRIFeatureType() override { return OpenGL::GetFeatureType(); }
		//Create Vertex Shader
		virtual void GRICreateVertexShader(const char* vsCode, GRIVertexShaderRef& handle) final override;
		//Create Fragment Shader
		virtual void GRICreateFragmentShader(const char* fsCode, GRIFragmentShaderRef& handle) final override;
		//Create Shader State
		virtual void GRICreatePipelineShader(GRIPipelineShaderRef& handle) final override;
		//Create Render Pipeline
		virtual void GRICreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo, GRIGraphicsPipelineRef& handle) final override;
        //Create Compute Pipeline
        virtual void GRICreateComputePipeline(const GRICreateComputePipelineInfo& createInfo,GRIComputePipelineRef& handle) final override;
		virtual void GRICreateBuffer(BufferUsageType usageType, int size, int stride, void* data, GRIBufferRef& handle) final override;
        //Create Vertex Declaration for VertexBuffer
		virtual void GRICreateVertexDescriptor(const VertexElementList& vdel,GRIVertexDescriptorRef& handle) final override;
		//Create Uniform Buffer
		virtual void GRICreateUniformBuffer(const UniformSlotList& contents,const char* ubName,UniformBufferUsageType ubType,GRIUniformBufferRef& handle) final override;
		//Create Uniform Buffer Declaration
		virtual void GRICreateUniformDescriptor(const UniformBufferList& ubl, GRIUniformBufferDescriptorRef& handle) final override;
		//Texture2D
        //create mipmap texture,you will pack all mipmap data to one data,SkySnowEngine not support generate mipmap texture
		virtual void GRICreateTexture2D(uint32 sizex, uint32 sizey, uint8 format, uint32 numMips, uint32 numSamples, TextureUsageType usageType, uint8* data,GRITexture2DRef& handle) final override;
		//Texture2DArray
		virtual void GRICreateTexture2DArray(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips, uint32 numSamples, TextureUsageType usageType,uint8* data,GRITexture2DArrayRef& handle) final override;
		//Texture3D
		virtual void GRICreateTexture3D(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips,TextureUsageType usageType,uint8* data,GRITexture3DRef& handle) final override;
		//TextureCube
		virtual void GRICreateTextureCube(uint32 size, uint8 format, uint32 numMips, TextureUsageType usageType,uint8* data,GRITextureCubeRef& handle) final override;
		//SamplerState
		virtual void GRICreateSampler(const SamplerState& sState, GRISamplerStateRef& handle) final override;
		//RenderState Rasterizer
		virtual void GRICreateRasterizer(const RasterizerStateInfo& state, GRIRasterizerStateRef& handle) final override;
		//RenderState DepthStencil
		virtual void GRICreateDepthStencil(const DepthStencilStateInfo& state, GRIDepthStencilStateRef& handle) final override;
		//RenderState BlendState
		virtual void GRICreateBlendState(const BlendStateInfo& state, GRIBlendStateRef& handle) final override;
		//GRICreate=================================================================================================================================

		//GRIUpdateData=============================================================================================================================
		//Set Uniform Buffer Descriptor(Uniform Buffer Layout)
		virtual void GRISetUniformBufferDescriptor(GRIUniformBufferDescriptorRef& descriptor) final override;
		//Update Uniform Buffer Data or Update Uniform Data
		virtual void GRIUpdateUniformBuffer(GRIUniformBufferRef& buffer, const UniformSlotList& contents) final override;
		//Update Texture2D Data
        //if updload mipmap data,you need call this function for numMap count
		virtual void GRIUpdateTexture2D(GRITexture2DRef& tex2D, uint32 mipLevel, Texture2DRegion region, uint32 pitch, const uint8* data) final override;
		//Update Texture3D Data and Texture2DArray
        //if updload mipmap data,you need call this function for numMap count
		virtual void GRIUpdateTexture3D(GRITexture3DRef& tex3D, uint32 mipLevel, Texture3DRegion region, uint32 rowPitch, uint8 depthPitch, const uint8* data) final override;
		//Update TextureCube Data
        //if updload mipmap data,you need call this function for numMap count
		virtual void GRIUpdateTexture2DArray(GRITexture2DArrayRef& tex2DArray, uint32 textureIndex, uint32 mipLevel, Texture2DRegion region, uint32 pitch, const uint8* data) final override;
		virtual void GRIUpdateTextureCube(GRITextureCubeRef& texCube, uint32 faceIndex, uint32 mipLevel, Texture2DRegion region, uint32 pitch, const uint8* data) final override;
		//GRISet====================================================================================================================================
		//Set Buffer VertexBuffer(StreamSource)
		virtual void GRISetBuffer(int bufferIndex, GRIBufferRef& buffer, int offset) final override;
		//set ShaderPipelineState
		virtual void GRISetPipelineShader(GRIPipelineShaderRef& pipelineShaderState) final override;
		//Set Graphics Pipeline State
		virtual void GRISetGraphicsPipeline(GRIGraphicsPipelineRef& pipelineState) final override;
		//Set Curr ShaderPipeline Uniform Buffer Index
		virtual void GRISetShaderParameter(GRIPipelineShaderRef& graphicsShader, GRIUniformBufferRef& buffer, int32_t bufferIndex) final override;
		//Set Texture2D Texture2DArray Texture3D  TextureCube
		virtual void GRISetShaderTexture(GRIPipelineShaderRef& graphicsShader, GRITextureRef& texture, uint32 textureIndex) final override;
		//Set Texture Sampler State
		virtual void GRISetShaderSampler(GRIPipelineShaderRef& graphicsShader, GRISamplerStateRef& sampler, uint32 samplerIndex) final override;
		//GRISet====================================================================================================================================
		//GRIDraw Submit============================================================================================================================
		//Call Draw,that draw primitive
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) final override;
	private:
        //vertex Element setup
		void SetupVertexFormatBinding(GLGraphicPipeline& psoState, GRIGLVertexDescriptor* vertexDec, int bufferIndex, int vertexCount);
		void CheckPrimitiveType(PrimitiveType primitiveType, int numPrimitives, GLenum& glPrimitiveType, int& numElements);
        void BindPipelineShaderState(GLGraphicPipeline& contextState);
        void BindUniformBuffer(GLGraphicPipeline& contextState);
        void BindTextureForDraw(GLGraphicPipeline& contextState);
	private:
		//this drawcall setup GraphicsPipeline state
		GLGraphicPipeline					_PendingState;
		//aleardly setup GraphicsPipeline state
		GLGraphicPipeline   				_ExistingState;
		std::vector<GRIViewportStateRef>	_Viewports;
		DrivePlatform*						_DrivePlatform = nullptr;
	};
}
