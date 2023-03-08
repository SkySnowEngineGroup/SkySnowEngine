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
        
		//GRICreate=================================================================================================================================
		GRIFeature GetGRIFeatureType() override { return OpenGL::GetFeatureType(); }
		//Test Demo
		virtual void GRIClearColor(float red, float green, float blue, float alpha) final override;
		//Create Vertex Shader
		virtual void GRICreateVertexShader(const char* vsCode, GRIVertexShaderRef& handle) final override;
		//Create Fragment Shader
		virtual void GRICreateFragmentShader(const char* fsCode, GRIFragmentShaderRef& handle) final override;
		//Create Shader State
		virtual void GRICreatePipelineShaderState(GRIPipelineShaderStateRef& handle) final override;
		//Create Pipeline State 
		virtual void GRICreateGraphicsPipelineState(const GRICreateGraphicsPipelineStateInfo& createInfo, GRIGraphicsPipelineStateRef& handle) final override;
		virtual void GRICreateBuffer(BufferUsageType usageType, int size, int stride, void* data, GRIBufferRef& handle) final override;
		//GRICreate=================================================================================================================================

		//GRISet====================================================================================================================================
		//Set Buffer
		virtual void GRISetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset) final override;
		//set ShaderPipelineState
		virtual void GRISetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState) final override;
		//Call Draw,that draw primitive
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) final override;
		virtual void GRISetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState) final override;
		//GRISet====================================================================================================================================

	private:
		//针对于glVertexAttribPointer的封装(设置数据的layout&告诉GPU数据如何读取)
		//在GL4.3及GL3.1将该api拆分为glVertexAttribFormat及glVertexAttribBinding
		void SetupVertexFormatBinding(GLGraphicPipelineState& psoState, GLBufferInfo* bufferInfo, int bufferIndex, int vertexCount);
		void CheckPrimitiveType(PrimitiveType primitiveType, int numPrimitives, GLenum& glPrimitiveType, int& numElements);
	private:
		//将要提交到GPU执行的pipelinestate
		GLGraphicPipelineState		_PendingState;
		//已经存在于GPU中的pipelinestate
		GLGraphicPipelineState		_ExistingState;
		//图元绘制类型
		PrimitiveType				_PrimitiveType = PrimitiveType::PT_Num;
		//Cache中有相关状态的缓存
		GLGraphicPipelineStateCache _PipelineCache;
        GLContext*                  _GLContext;
	};
}
