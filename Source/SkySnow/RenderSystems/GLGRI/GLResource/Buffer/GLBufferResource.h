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
#include "GLPlatformProfiles.h"
#include "GRIResource.h"
#include "GLBuffer.h"

namespace SkySnow
{
	//IndexBuffer
	//VertexBuffer
	//UniformBuffer
	//SSBO
	//MapBuffer&unMapBuffer
	//TranstBuffer
	//PackPixelBuffer&unPackPixelBuffer

	class GLBuffer : public GRIBuffer
	{
	public:
		GLBuffer()
			: GRIBuffer()
		{
		}

		GLBuffer(GLenum target,GLuint size,int stride,const void* data,bool streamDraw = false)
			: m_Target(target)
			, m_Size(size)
			, m_Data(data)
			, b_StreamDraw(streamDraw)
		{
			CreateBuffer(target,size);
		}

		~GLBuffer()
		{
		}
		void CreateBuffer(GLenum target,GLuint size)
		{
			glGenVertexArrays(1,&m_Vao);
			glBindVertexArray(m_Vao);

			OpenGL::GenBuffers(1,&m_GPUHandle);
			OGLBuffer::BindBuffer(GL_ARRAY_BUFFER,m_GPUHandle);
			OpenGL::BufferData(GL_ARRAY_BUFFER, size, m_Data, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			
			glBindBuffer(GL_ARRAY_BUFFER,0);
			glBindVertexArray(0);
		}

		void Bind()
		{
			glBindVertexArray(m_Vao);
		}
	public:
		GLuint m_Vao;
	private:
		bool b_StreamDraw;
		GLenum m_Target;
		int m_Size;
		int m_Stride;
		GLuint m_GPUHandle;
		
		const void* m_Data;
		
	};
}