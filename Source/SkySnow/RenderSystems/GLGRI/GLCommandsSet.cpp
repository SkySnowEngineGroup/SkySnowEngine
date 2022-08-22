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
		//glVertexAttribPointer
		/*
			缺陷1: offset为指针非整数，cpu侧进行整数到指针的转换，GPU侧进行指针到整数的转换(这是一个糟糕的设计思路)
			缺陷2: 合并两个逻辑上完全独立的操作: 1. 如何从内存提取数据 2. 数据是什么样的
		OpenGL的4.3和OpenGL ES 3.1添加若干替代功能用于指定顶点数组:glVertexAttribFormat,glBindVertexBuffers等
			单独的glVertexAttribPointer函数，类似一下伪代码功能
			void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
			{
				glVertexAttrib*Format(index, size, type, normalized, 0);
				glVertexAttribBinding(index, index);
				GLuint buffer;
				glGetIntegerv(GL_ARRAY_BUFFER_BINDING, buffer);
				if(buffer == 0)
					glErrorOut(GL_INVALID_OPERATION); //Give an error.

				if(stride == 0)
					stride = CalcStride(size, type);

				GLintptr offset = reinterpret_cast<GLintptr>(pointer);
				glBindVertexBuffer(index, buffer, offset, stride);
			}
		*/
		
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