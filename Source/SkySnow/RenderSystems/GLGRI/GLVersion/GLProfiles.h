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
/*
    WindowOS  : Import GLFunction Self,Include ThiryParty/Khronos/OpenGL.
                    Use DLL Pointer Address Import
                    Use wglGetPropAddress Import
                        GL Common Function Pointer
                        GL Option Function Pointer
    MacOS     : Not Import GLFunction Self,Include OS GL Header,And MacOS Use GL version below 4.x(<GL4.x).
                MacOS10.14 stop OpenGL Interface,so OpenGL Interface Support Simple
    LinuxOS   : Not Support OS.
    AndroidOS : Not Import GLFunction,Include OS GL Header,But Check Expansion String.
    IosOS     : Not Import GLFunction,Include OS GL Header,But Check Expansion String.
 */
#pragma once
#include "PlatformProfiles.h"
#include "GRICommons.h"
#if PLATFORM == PLATFORM_ANDROID
#	include <GLES3/gl3.h>
#	include <GLES3/gl3ext.h>
#elif PLATFORM == PLATFORM_IOS
#	include <OpenGLES/ES3/gl.h>
#	include <OpenGLES/ES3/glext.h>
	//GPU Simd
#	if __has_include(<simd/simd.h>)
#		ifndef WBSIMD
#			define WBSIMD
#		endif
#	endif
#elif PLATFORM == PLATFORM_WINDOW || PLATFORM == PLATFORM_MAC
#	define GLFW_INCLUDE_NONE
#	include <stdarg.h>
#	include <stdio.h>
#	include <GLFW/glfw3.h>
#   if PLATFORM == PLATFORM_WINDOW
#       define GLFW_EXPOSE_NATIVE_WIN32
#       define GLFW_EXPOSE_NATIVE_WGL
#       include "GLImport.h"
#       define USE_GL4  1
#   elif PLATFORM == PLATFORM_MAC
#       define GLFW_EXPOSE_NATIVE_COCOA
#       define GLFW_EXPOSE_NATIVE_NSGL
#       define GL_SILENCE_DEPRECATION
#       include <OpenGL/OpenGL.h>
#       include <OpenGL/gl3.h>
#       include <OpenGL/gl3ext.h>
#       define USE_GL4  0
#   endif
#   include <GLFW/glfw3native.h>
#endif // 0

#define Num_GL_Vertex_Attribute 16

//About OS Platform Device:Example Window for Window(OSWindow) 
//                         for window(WindowHandle) for Android(NativeWindow)
//About OS Platform Context:Example GLContext
class GLContext
{
public:
    GLContext(){};
    
    virtual ~GLContext(){};
    
    virtual void CreateGLContext() = 0;
    
    virtual void DestroyGLContext() = 0;
    
    virtual void MakeCurrContext() = 0;
    
};


