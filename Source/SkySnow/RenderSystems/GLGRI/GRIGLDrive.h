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
#include "GLPlatformProfiles.h"
#include "GRIDrive.h"
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

		~GRIGLDrive() {}
		//GRICreate=================================================================================================================================
		GRIFeature GetGRIFeatureType() override { return OpenGL::GetFeatureType(); }
		//Test Demo
		virtual void GRIClearColor(float red, float green, float blue, float alpha) final override;
		//Create Vertex Shader
		virtual GRIVertexShaderRef GRICreateVertexShader(const char* vsCode) final override;
		//Create Fragment Shader
		virtual GRIFragmentShaderRef GRTCreateFragmentShader(const char* fsCode) final override;
		//Create Shader State
		virtual GRIPipelineShaderStateRef GRICreatePipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs) final override;
		//Create Pipeline State 
		virtual GRIGraphicsPipelineStateRef GRICreateGraphicsPipelineState(const GRICreateGraphicsPipelineStateInfo& createInfo) final override;
		virtual GRIBufferRef GRICreateBuffer(BufferUsageType usageType, int size,int stride, void* data) final override;
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
		//�����glVertexAttribPointer�ķ�װ(�������ݵ�layout&����GPU������ζ�ȡ)
		//��GL4.3��GL3.1����api���ΪglVertexAttribFormat��glVertexAttribBinding
		void SetupVertexFormatBinding(GLGraphicPipelineState& psoState, GLBufferInfo* bufferInfo, int bufferIndex, int vertexCount);
		void CheckPrimitiveType(PrimitiveType primitiveType, int numPrimitives, GLenum& glPrimitiveType, int& numElements);
	private:
		//��Ҫ�ύ��GPUִ�е�pipelinestate
		GLGraphicPipelineState		m_PendingState;
		//�Ѿ�������GPU�е�pipelinestate
		GLGraphicPipelineState		m_ExistingState;
		//ͼԪ��������
		PrimitiveType				m_PrimitiveType = PrimitiveType::PT_Num;
		//Cache�������״̬�Ļ���
		GLGraphicPipelineStateCache m_PipelineCache;
	};
}