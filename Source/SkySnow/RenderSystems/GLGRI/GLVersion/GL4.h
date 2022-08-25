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
#include "GL3.h"
namespace SkySnow
{
	class OpenGL4 : public OpenGL3
	{
	public:
		//OpenGLµÄ4.3ºÍOpenGL ES 3.1ÐÂAPI
		static inline void BindVertexBuffer(GLuint bindingIndex, GLuint buffer, GLintptr offset, GLsizei stride)
		{
			glBindVertexBuffer(bindingIndex, buffer, offset, stride);
		}
		static inline void VertexAttribFormat(GLuint attribIndex, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset)
		{
			glVertexAttribFormat(attribIndex, size, type, normalized, relativeOffset);
		}
		static inline void VertexAttribIFormat(GLuint attribIndex, GLint size, GLenum type, GLuint relativeOffset)
		{
			glVertexAttribIFormat(attribIndex, size, type, relativeOffset);
		}
		static inline void VertexAttribBinding(GLuint attribIndex, GLuint bindingIndex)
		{
			glVertexAttribBinding(attribIndex, bindingIndex);
		}
		static inline void VertexBindingDivisor(GLuint bindingIndex, GLuint divisor)
		{
			glVertexBindingDivisor(bindingIndex, divisor);
		}

		static void InitialExtensions();
	};
}