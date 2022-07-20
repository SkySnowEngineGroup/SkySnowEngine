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
#include "GLCommands.h"
#include "GLRealTimeGRI.h"
#include "GLBufferResource.h"
#include "GLPipelineResource.h"
namespace SkySnow
{
	void GLCommands::GRISetBuffer(int BufferInfoId, GRIBuffer* buffer,int offset)
	{
		GLBuffer* vertexBuffer = dynamic_cast<GLBuffer*>(buffer);
		m_PendingState.vertexBufferInfo[BufferInfoId].gpuHandle = vertexBuffer->m_Vao;
		m_PendingState.vertexBufferInfo[BufferInfoId].stride = vertexBuffer->GetStride();
		m_PendingState.vertexBufferInfo[BufferInfoId].offset = offset;
	}

	void  GLCommands::GRISetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState)
	{
		m_PendingState.shaderStateInfo.gpuHandle = static_cast<GLPipelineShaderState*>(pipelineShaderState)->m_ProgramId;
	}

	void GLCommands::GRIDrawPrimitive(int numPrimitive, int numInstance)
	{
		if (numInstance > 1)
		{

		}
		else
		{
			glUseProgram(m_PendingState.shaderStateInfo.gpuHandle);
			SetupVertexFormatBinding();
			glBindVertexArray(m_PendingState.vertexBufferInfo[0].gpuHandle);
			glDrawArrays(GL_TRIANGLES, 0, numPrimitive);
			//glBindVertexArray(0);
		}
	}


	void GLCommands::SetupVertexFormatBinding()
	{

	}
}