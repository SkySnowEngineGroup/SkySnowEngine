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
/*
	在Nuwa引擎中，不在像UE或者Bgfx一样，在window&linux&Mac中不在引擎底层中进行API导入
	BGFX&UE框架大致是:
					GPU接口:	RenderContextI(BGFX)		OpenGLRHI(UE)
					GPU资源:	OpenGLResource(BGFX)		OpenGLRHIResource(UE)
					GPUEnv:		OpenGLEnvironment(BGFX)		OpenGLHardwareInterface(UE)
					APIImport:	glimport_xx(BGFX)			OpenGL_xx(UE)
	具体含义:
			GPU接口:这一层是向CommandBuffer提供编码命令接口，或者说Command就
					是包裹这一层的接口，而单独抽象出来，各个平台虽然api不同，
					但是接口是一致
			GPU资源:这一层是对GPU资源进行划分与分类，以供GPU接口层调用，逻辑
					与拓展性更高一些
			GPUEnv: 这一层是针对各个API版本的函数进行封装，并对各个平台的渲染上下文
					进行封装，这样版本控制以及扩展都是可以灵活定制与转换的
			APIImport:这一层是使用opengl的回调接口来自己注册一些api接口，这么做的
					 原因是，接口可以自己掌控，对待不同显卡产商的支持，灵活处理

	在Nuwa中我们将APIImport层去掉，去掉原因是，暂时还没有过多精力处理这些问题
	但是Nuwa会保留GPUEnv、GPUResource以及GPU接口的三层封装，如果后期针对渲染优
	化，需要自己导入一些函数以及宏定义时，我们将会把这最底层添加进来，虽然我们
	去掉这一层设计，但是我们会保留架构的拓展性，以便后面可以拓展它。
*/
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
