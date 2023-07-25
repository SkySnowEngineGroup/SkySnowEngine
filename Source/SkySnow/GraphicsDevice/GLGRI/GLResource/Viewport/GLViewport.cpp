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
#include "GLViewport.h"
#include "GRIGLDrive.h"
#include "GLViewportResource.h"
#include "GLTexture.h"
namespace SkySnow
{
    GRIViewportStateRef GRIGLDrive::GRICreateViewport(void* windowHandle,uint32 width,uint32 height,PixelFormat format,bool isFullScreen)
    {
        return new GRIGLViewport(windowHandle,width,height,format,isFullScreen);
    }


    GRIGLViewport::GRIGLViewport(void* inWindowHandle,uint32 inWidth, uint32 inHeight, PixelFormat inFormat, bool inIsFullScreen = true)
        : GRIViewportState()
        , _WindowHandle(inWindowHandle)
        , _WindowWidth(inWidth)
        , _WindowHeight(inHeight)
        , _PixelFormat(inFormat)
        , _IsFullScreen(inIsFullScreen)
    {
#if PLATFORM == PLATFORM_WINDOW
        _GLContext = new GLContextWin();
#elif PLATFORM == PLATFORM_IOS
        _GLContext = new GLContextIos();
#elif PLATFORM == PLATFORM_MAC
        _GLContext = new GLContextMac();
#elif PLATFORM == PLATFORM_ANDROID
        _GLContext = new GLContextAndroid();
#elif  PLATFORM == PLATFORM_LINUX
        //            _GLContext = new GLContextLinux();
#endif
        _GLContext->CreateGLContext();
        OpenGL::InitialExtensions();
        OGLTexture::InitTextureFormat();
    }
}
