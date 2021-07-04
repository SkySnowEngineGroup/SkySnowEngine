//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
// Open source is written by wangcan(crygl)、liuqian(SkySnow)、zhangshuangxue(Calence)
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
#include "PlatformProfiles.h"

#if PLATFORM == PLATFORM_ANDROID
#	include <GLES3/gl3.h>
#	include <GLES3/gl3ext.h>
#elif PLATFORM == PLATFORM_IOS
#	include <OpenGLES/ES3/gl.h>
#	include <OpenGLES/ES3/glext.h>
	//GPU加速使用
#	if __has_include(<simd/simd.h>)
#		ifndef WBSIMD
#			define WBSIMD
#		endif
#	endif
#elif PLATFORM == PLATFORM_WINDOW || PLATFORM == PLATFORM_MAC
#	define GLFW_INCLUDE_NONE
#	include <stdarg.h>
#	include <stdio.h>
#	include <glad/gl.h>
#	include <GLFW/glfw3.h>
#endif // 0
