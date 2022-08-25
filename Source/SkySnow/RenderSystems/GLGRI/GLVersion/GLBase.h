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
#include "GLProfiles.h"
#include "UString.h"
#include <string>
//关于API版本，即核心标准库中，可以在此网站查询:https://docs.gl/
namespace SkySnow
{
	class OpenGLBase
	{
	public:
		//static inline GRIFeature GetFeatureType() { return ENone; }

		static inline GLuint CreateShader(GLenum shadertype) 
		{ 
			return glCreateShader(shadertype); 
		}

		static inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
		{
			glBufferSubData(target,offset,size,data);
		}
		static inline void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
		{
			glBufferData(target,size,data,usage);
		}
		//卷绕法绑定\索引法绑定\SSBO的绑定
		static inline void BindBuffer(GLenum type,GLuint buffer)
		{
			glBindBuffer(type, buffer);
		}

		static inline bool SupportVertexFormatBinding() { return _SupportVertexFormatBinding; };
		static inline GLuint GetMajorVersion() { return _MajorVersion; };
		static inline GLuint GetMinorVersion() { return _MinorVersion; };
		static void InitialExtensions();
	protected:
		static bool		_SupportVertexFormatBinding;
		static GLuint	_MajorVersion;
		static GLuint	_MinorVersion;
		static UString  _ExtensionsStr;
	};
}