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
namespace SkySnow
{
	/*
		brief: Each real-time rendering API (GRI) unifies the base class of the external interface. 
			   Different rendering APIs inherit from this class and implement the functions of 
			   different APIs with the same capability
	*/
	class GRIGLDrive : public GRIDrive
	{
	public:
		GRIGLDrive();

        ~GRIGLDrive();
        
        virtual void Init() final override;
        
        virtual void Exit() final override;

		virtual void GRIBeginViewport() final override;
		virtual void GRIEndViewport() final override;
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
		virtual void GRICreateVertexDescriptor(const VertexDescriptorElementList& vdel,GRIVertexDescriptorRef& handle) final override;
		//Create Uniform Buffer
		virtual void GRICreateUniformBuffer(const UniformBufferSlot& contents, GRIUniformBufferRef& handle) final override;
		//Create Uniform Buffer Declaration
		virtual void GRICreateUniformDescriptor(const GRICreateUniformBufferDescriptorInfo& info, GRIUniformBufferDescriptorRef& handle) final override;
		//GRICreate=================================================================================================================================

		//GRISet====================================================================================================================================
		//Set Uniform Buffer Descriptor(Uniform Buffer Layout)
		virtual void GRISetUniformBufferDescriptor(GRIUniformBufferDescriptor* descriptor) final override;
		//Update Uniform Buffer Data or Update Uniform Data
		virtual void GRIUpdateUniformBuffer(GRIUniformBuffer* buffer, const UniformBufferSlot& contents) final override;
		//Set Curr ShaderPipeline Uniform Buffer Index
		virtual void GRISetShaderParameter(GRIPipelineShader* graphicsShader, GRIUniformBuffer* buffer, int32_t bufferIndex) final override;
		//Set Buffer
		virtual void GRISetBuffer(int bufferIndex, GRIBuffer* buffer, int offset) final override;
		//set ShaderPipelineState
		virtual void GRISetPipelineShader(GRIPipelineShader* pipelineShaderState) final override;
		//Call Draw,that draw primitive
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) final override;
		virtual void GRISetGraphicsPipeline(GRIGraphicsPipeline* pipelineState) final override;
		//GRISet====================================================================================================================================

	private:
        //vertex Element setup
		void SetupVertexFormatBinding(GLGraphicPipeline& psoState, GRIGLVertexDescriptor* vertexDec, int bufferIndex, int vertexCount);
		void CheckPrimitiveType(PrimitiveType primitiveType, int numPrimitives, GLenum& glPrimitiveType, int& numElements);
	private:
		//this drawcall setup GraphicsPipeline state
		GLGraphicPipeline		    _PendingState;
		//aleardly setup GraphicsPipeline state
		GLGraphicPipeline   		_ExistingState;
        GLContext*                  _GLContext;
	};
}
