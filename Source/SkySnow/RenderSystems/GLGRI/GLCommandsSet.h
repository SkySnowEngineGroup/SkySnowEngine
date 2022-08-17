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
#include "GRIResource.h"
#include "GRICommandsSet.h"
#include "GRICommons.h"
#include "GLPipelineResource.h"
namespace SkySnow
{
	class GLCommandsSet : public GRICommandsSet
	{
	public:
		GLCommandsSet()
		{
		}
		virtual ~GLCommandsSet()
		{
		}
		//Set Buffer
		virtual void GRISetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset) final override;
		//set ShaderPipelineState
		virtual void GRISetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState) final override;
		//Call Draw,that draw primitive
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) final override;
		virtual void GRISetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState) final override;
		
	private:
		//�����glVertexAttribPointer�ķ�װ(�������ݵ�layout&����GPU������ζ�ȡ)
		//��GL4.3��GL3.1����api���ΪglVertexAttribFormat��glVertexAttribBinding
		void SetupVertexFormatBinding(GLGraphicPipelineState& psoState, GLBufferInfo* bufferInfo, int bufferIndex, int vertexCount);
		void CheckPrimitiveType(PrimitiveType primitiveType,int numPrimitives,GLenum& glPrimitiveType,int& numElements);
	private:
		//�Ѿ����ã����ύ��GPUִ�е�pipelinestate
		//��ʹ��PipelineCacheʱ���ö�����ⲿ���ã�����GRISetGraphicsPipelineState���и�ֵ
		GLGraphicPipelineState		m_PendingState;
		//�Ѿ�������GPU�е�pipelinestate
		GLGraphicPipelineState		m_ExistingState;
		PrimitiveType				m_PrimitiveType = PrimitiveType::PT_Num;
	};
}