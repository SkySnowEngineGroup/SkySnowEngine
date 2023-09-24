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
#include "GRICreate.h"
#include "GRIGLDrive.h"
#include "GRILowerCommandBufferQueue.h"
namespace SkySnow
{
	GRIDrive* GRICreate::CreateTargetGRI()
	{
#if PLATFORM == PLATFORM_WINDOW
        return WindowOSCreateGRI();
#elif PLATFORM == PLATFORM_IOS
        
#elif PLATFORM == PLATFORM_MAC
		return MacOSCreateGRI();
#elif PLATFORM == PLATFORM_ANDROID
        
#elif  PLATFORM == PLATFORM_LINUX
        
#endif
	}

	GRIDrive* GRICreate::WindowOSCreateGRI()
	{
		//can create OpenGL Vulkan,SkySnow plan not support DX 
		//Windows platform can support OpenGL, Vulakn GRI
#if GRI_PLATFORM == GRI_GL
		return new GRIGLDrive();
#elif GRI_PLATFORM == GRI_VULKAN

#endif
		return nullptr;
	}
	GRIDrive* GRICreate::MacOSCreateGRI()
	{
#if GRI_PLATFORM == GRI_GL
		return new GRIGLDrive();
#elif GRI_PLATFORM == GRI_METAL

#endif
		return nullptr;
	}

    GRICommandBufferQueue* GRICreate::CreateTargetCBQueue()
    {
#if PLATFORM == PLATFORM_WINDOW
        return WindowOSCreateCBQueue();
#elif PLATFORM == PLATFORM_IOS
        
#elif PLATFORM == PLATFORM_MAC
        return MacOSCreateCBQueue();
#elif PLATFORM == PLATFORM_ANDROID
        
#elif  PLATFORM == PLATFORM_LINUX
        
#endif
    }
    GRICommandBufferQueue* GRICreate::WindowOSCreateCBQueue()
    {
#if GRI_PLATFORM == GRI_GL
        return new GRILowerCommandBufferQueue();
#elif GRI_PLATFORM == GRI_VULKAN

#endif
        return nullptr;
    }
    GRICommandBufferQueue* GRICreate::MacOSCreateCBQueue()
    {
#if GRI_PLATFORM == GRI_GL
        return new GRILowerCommandBufferQueue();
#elif GRI_PLATFORM == GRI_METAL

#endif
        return nullptr;
    }
}
