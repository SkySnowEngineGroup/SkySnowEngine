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
#include "GRIResource.h"
#include "GLViewport.h"
namespace SkySnow
{
	class GRIGLViewport : public GRIViewportState
	{
	public:
        GRIGLViewport(DrivePlatform* drivePlatform,void* inWindowHandle, uint32 inWidth, uint32 inHeight, PixelFormat inFormat, bool inIsFullScreen = true);

        ~GRIGLViewport();
        
        virtual void* GetDriveContext() final override
        {
            return _DriveContext;
        }

        virtual void* GetWindowHandle() final override
        {
            return _WindowHandle;
        }

        virtual GRITexture2DRef GetBackBuffer() final override
        {
            return _BackTexture;
        }
        
        virtual PixelFormat GetWindowPixelFormat() const override
        {
            return _PixelFormat;
        }

        virtual uint32 GetWindowWidth() const override
        {
            return _WindowWidth;
        }

        virtual uint32 GetWindowHeight() const override
        {
            return _WindowHeight;
        }

        virtual bool IsFullScreen() const override
        {
            return _IsFullScreen;
        }
    private:
        void*           _WindowHandle;
        DriveContext*   _DriveContext;
        GRITexture2DRef _BackTexture;
        uint32          _WindowWidth;
        uint32          _WindowHeight;
        PixelFormat     _PixelFormat;
        bool            _IsFullScreen;
        DrivePlatform*  _DrivePlatform;
	};
}
