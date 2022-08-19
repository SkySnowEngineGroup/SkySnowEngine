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
#include "GLCommandsSet.h"
#include "GLBufferResource.h"
#include "GLPipelineResource.h"
namespace SkySnow
{
	void GLCommandsSet::GRISetBuffer(int BufferInfoId, GRIBuffer* buffer,int offset)
	{
		GLBuffer* bufferGL = dynamic_cast<GLBuffer*>(buffer);
		m_PendingState._BufferInfo[BufferInfoId]._GpuHandle = bufferGL->_GpuHandle;
		m_PendingState._BufferInfo[BufferInfoId]._Stride = bufferGL->GetStride();
		m_PendingState._BufferInfo[BufferInfoId]._Offset = offset;
		m_PendingState._BufferInfo[BufferInfoId]._BufferType = bufferGL->_BufferType;
	}

	void  GLCommandsSet::GRISetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState)
	{
		m_PendingState._ShaderStateInfo._GpuHandle = static_cast<GLPipelineShaderState*>(pipelineShaderState)->_ProgramId;
	}

	void GLCommandsSet::GRISetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState)
	{
		m_PendingState._PrimitiveType = (PrimitiveType)static_cast<GLGraphicPipelineState*>(pipelineState)->_PrimitiveType;
	}

	void GLCommandsSet::GRIDrawPrimitive(int numPrimitive, int numInstance)
	{
		GLenum drawMode = GL_TRIANGLES;
		int numElements;
		CheckPrimitiveType(m_PendingState._PrimitiveType,numPrimitive, drawMode,numElements);
		
		SetupVertexFormatBinding(m_PendingState, m_PendingState._BufferInfo, Num_GL_Vertex_Attribute, numElements);
		if (numInstance > 1)
		{

		}
		else
		{
			glUseProgram(m_PendingState._ShaderStateInfo._GpuHandle);
			glDrawArrays(drawMode, 0, numElements);
			//glDisableVertexAttribArray(0);
		}
	}

	//privateFunction ==============================================================
	void GLCommandsSet::SetupVertexFormatBinding(GLGraphicPipelineState& psoState, GLBufferInfo* bufferInfo, int bufferIndex, int vertexCount)
	{
		GLBufferInfo& bInfo = bufferInfo[0];
		glBindBuffer(bInfo._BufferType, bInfo._GpuHandle);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, bInfo._Stride,
							  GL_FLOAT, GL_FALSE, 
							  bInfo._Stride * sizeof(GLfloat),
			                  (GLvoid*)bInfo._Offset);
		
	}

	void GLCommandsSet::CheckPrimitiveType(PrimitiveType primitiveType, int numPrimitives, GLenum& glPrimitiveType, int& numElements)
	{
		glPrimitiveType = GL_TRIANGLES;
		numElements = numPrimitives;
		switch (primitiveType)
		{
		case PrimitiveType::PT_Lines:
			glPrimitiveType = GL_LINES;
			numElements = numPrimitives * 2;
			break;
		case PrimitiveType::PT_Point_Strip:
			glPrimitiveType = GL_POINTS;
			numElements = numPrimitives;
			break;
		case PrimitiveType::PT_Trangles:
			glPrimitiveType = GL_TRIANGLES;
			numElements = numPrimitives * 3;
			break;
		case PrimitiveType::PT_Trangle_Strip:
			glPrimitiveType = GL_TRIANGLE_STRIP;
			numElements = numPrimitives + 2;
			break;
		default:
			SN_LOG("There is no primitive matching type:%d",primitiveType);
			break;
		}
	}
}