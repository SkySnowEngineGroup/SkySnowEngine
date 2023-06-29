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
#include "GLProfiles.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "UString.h"
#include "GLImport.h"
//For core library standards, check the website:https://docs.gl/

//Macros define the body of functions that contain optimizations and high version imports.
//These are functions that are defined in base but not implemented by GLX.h
#define VOID_BODYFUN {}
#define RETURN_BODY(RETURNVALUE){return RETURNVALUE;}

namespace SkySnow
{
	class OpenGLBase
	{
	public:
        //default None Support
		static inline GRIFeature GetFeatureType() { return ENone; }
        static inline bool SupportVertexFormatBinding() { return _SupportVertexFormatBinding; };
        static inline bool SupportUniformBuffer(){return true;}
        static inline bool SupportASTC(){return  false;}
        //GL4.2,GLES3.0
        static inline bool SupportStorageTexture() {return true;}
        
        static inline GLuint GetMajorVersion() { return _MajorVersion; };
        
        static inline GLuint GetMinorVersion() { return _MinorVersion; };
        //base Function Not define this,All of the functions defined here are extended or higher versions
        static inline void BindVertexBuffer(GLuint bindingIndex, GLuint buffer, GLintptr offset, GLsizei stride) VOID_BODYFUN
        static inline void VertexAttribFormat(GLuint attribIndex, GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset)VOID_BODYFUN
        static inline void VertexAttribIFormat(GLuint attribIndex, GLint size, GLenum type, GLuint relativeOffset) VOID_BODYFUN
        static inline void VertexAttribBinding(GLuint attribIndex, GLuint bindingIndex) VOID_BODYFUN
        static inline void VertexBindingDivisor(GLuint bindingIndex, GLuint divisor) VOID_BODYFUN
        static inline bool TexStorage3D(GLenum target, GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type)VOID_BODYFUN
        static inline bool TexStorage2D(GLenum target, GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLenum format,GLenum type)VOID_BODYFUN
		

		static void InitialExtensions();
	protected:
		static bool		_SupportVertexFormatBinding;
		static GLuint	_MajorVersion;
		static GLuint	_MinorVersion;
		static UString  _ExtensionsStr;
	};
}
