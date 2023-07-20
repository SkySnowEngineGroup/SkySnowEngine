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
		GRIGLViewport(void* inWindowHandle, void* inDeviceContext, uint32 inWidth, uint32 inHeight, PixelFormat inFormat, bool inIsFullScreen = true)
			: GRIViewportState()
            , _WindowHandle(inWindowHandle)
            , _DeviceContext(inDeviceContext)
            , _WindowWidth(inWidth)
            , _WindowHeight(inHeight)
            , _PixelFormat(inFormat)
            , _IsFullScreen(inIsFullScreen)
		{
		}
        
        virtual void* GetDeviceContext() final override;

        virtual void* GetWindowHandle() final override;

        virtual GRITexture2DRef GetBackBuffer() final override;
        
        virtual PixelFormat GetWindowPixelFormat() const { return _PixelFormat;}

        virtual uint32 GetWindowWidth() const { return _WindowWidth;}

        virtual uint32 GetWindowHeight() const { return _WindowHeight;}

        virtual bool IsFullScreen() const { return _IsFullScreen; }
    private:
        void*           _WindowHandle;
        void*           _DeviceContext;
        uint32          _WindowWidth;
        uint32          _WindowHeight;
        PixelFormat     _PixelFormat;
        bool            _IsFullScreen;
	};
}
