//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
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
#include "GRICommands.h"
#include "GRICommons.h"
#include "GLPipelineResource.h"
namespace SkySnow
{
	class GLCommands : public GRICommands
	{
	public:
		GLCommands()
		{
		}
		virtual ~GLCommands()
		{
		}
		//Set Buffer
		virtual void GRISetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset) final override;
		//set ShaderPipelineState
		virtual void GRISetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState) final override;
		//Call Draw,that draw primitive
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) final override;
		
	private:
		//针对于glVertexAttribPointer的封装(设置数据的layout&告诉GPU数据如何读取)
		//在GL4.3及GL3.1将该api拆分为glVertexAttribFormat及glVertexAttribBinding
		void SetupVertexFormatBinding();
	private:
		//已经设置，将提交到GPU执行的pipelinestate
		//当使用PipelineCache时，该对象从外部设置，即从GRISetGraphicsPipelineState进行赋值
		GLGraphicPipelineState		m_PendingState;
		//已经存在于GPU中的pipelinestate
		GLGraphicPipelineState		m_ExistingState;
		PrimitiveType				m_PrimitiveType = PrimitiveType::PT_Num;
	};
}