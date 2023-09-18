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
        GRIGLViewport* viewport = new GRIGLViewport(_DrivePlatform,windowHandle, width, height, format, isFullScreen);
        _Viewports.push_back(viewport);
        return viewport;
    }

    void GRIGLDrive::GRIBeginViewport(GRIViewportStateRef& viewPort, GRITexture2DRef& renderTexture)
    {
        //Swith glcontext
        GRIGLViewport* glVP = dynamic_cast<GRIGLViewport*>(viewPort.GetReference());
        ((DriveContext*)glVP->GetDriveContext())->MakeCurrContext();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, DEFAUT_WADTH, DEFAUT_HEIGHT);
    }

    void GRIGLDrive::GRIEndViewport(GRIViewportStateRef& viewPort, bool present, bool lockToVsync)
    {
        GRIGLViewport* glVP = dynamic_cast<GRIGLViewport*>(viewPort.GetReference());
        
        ((DriveContext*)glVP->GetDriveContext())->SwapBuffer();
    }

    GRIGLViewport::GRIGLViewport(DrivePlatform* drivePlatform,void* inWindowHandle,uint32 inWidth, uint32 inHeight, PixelFormat inFormat, bool inIsFullScreen)
        : GRIViewportState()
        , _DrivePlatform(drivePlatform)
        , _WindowHandle(inWindowHandle)
        , _WindowWidth(inWidth)
        , _WindowHeight(inHeight)
        , _PixelFormat(inFormat)
        , _IsFullScreen(inIsFullScreen)
    {
        _DriveContext = _DrivePlatform->CreateGLContextCoreFromViewport(_WindowHandle);
    }

    GRIGLViewport::~GRIGLViewport()
    {
        SN_LOG("GRIGLViewport DesConstruct.");
        if (_DriveContext)
        {
            _DriveContext->ReleaseContext();
            delete _DriveContext;
            _DriveContext = nullptr;
            SN_LOG("GRIGLViewport Reclaiming GPU Resources.");
        }
    }
    namespace OGLViewport
    {
    }
}
