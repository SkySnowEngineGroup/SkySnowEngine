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
#include "GLMac.h"
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_LINUX
#include <dlfcn.h>
#include <AvailabilityMacros.h>
#include <Cocoa/Cocoa.h>
#include "OSPlatform.h"
namespace SkySnow
{
    void GLMac::ImportAPIEntryPointer()
    {
        
    }
    //=GLContext-Start=========================================================================================================================
    // cpp local var
    static NSOpenGLPixelFormat* _PixelFormat    = nil;
    NSOpenGLPixelFormatAttribute Profile        = NSOpenGLProfileVersion3_2Core;
    const NSOpenGLPixelFormatAttribute PixelFormatAttributes[] =
    {
        NSOpenGLPFAOpenGLProfile,   Profile,
        NSOpenGLPFAColorSize    ,   24,
        NSOpenGLPFAAlphaSize    ,   8,
        NSOpenGLPFADepthSize    ,   24,
        NSOpenGLPFAStencilSize  ,   8,
        NSOpenGLPFADoubleBuffer ,   true,
        NSOpenGLPFAAccelerated  ,   true,
        NSOpenGLPFANoRecovery   ,   true,
        0                       ,   0,
    };
    
    NSOpenGLContext* CreateGLContextInternal(NSOpenGLContext* shareGLContext)
    {
        if(!_PixelFormat)
        {
            _PixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:PixelFormatAttributes];
            if(!_PixelFormat)
            {
                SN_ERR("Failed to initialize pixel format.\n");
            }
        }
        NSOpenGLContext* glContext = [[NSOpenGLContext alloc] initWithFormat: _PixelFormat shareContext: shareGLContext];
        int syncInterval = 0;
        [glContext setValues: &syncInterval forParameter: NSOpenGLCPSwapInterval];
        return glContext;
    }
    GLContextMac::GLContextMac()
        : _OpenGLDll(nullptr)
    {
        
    }
    GLContextMac::~GLContextMac()
    {
        
    }

    void GLContextMac::CreateGLContext()
    {
        DlOpen();

        NSObject* nativeWindow = (NSObject*)_GOSPlatformInfo->_NativeWindow;
        NSWindow* nsWindow = nil;
        NSView* contentView = nil;
        if ([nativeWindow isKindOfClass:[NSView class]])
        {
            contentView = (NSView*)nativeWindow;
        }
        else if ([nativeWindow isKindOfClass:[NSWindow class]])
        {
            nsWindow = (NSWindow*)nativeWindow;
            contentView = [nsWindow contentView];
        }

        NSOpenGLContext* CreateGLContextInternal(NSOpenGLContext* shareGLContext);
        _GLContext = CreateGLContextInternal(nil);

        NSRect glViewRect = [contentView bounds];
        NSOpenGLView* glView = [[NSOpenGLView alloc] initWithFrame:glViewRect pixelFormat:_PixelFormat];

        if (nil != contentView)
        {
            [glView setAutoresizingMask:( NSViewHeightSizable |
                    NSViewWidthSizable |
                    NSViewMinXMargin |
                    NSViewMaxXMargin |
                    NSViewMinYMargin |
                    NSViewMaxYMargin )];
            [contentView addSubview:glView];
        }
        else
        {
            if (nil != nsWindow)
                [nsWindow setContentView:glView];
        }
        NSOpenGLContext* glContext = [glView openGLContext];
        [_PixelFormat release];

        [glContext makeCurrentContext];
        GLint interval = 0;
        [_GLContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];
        int a = 10;
    }

    void GLContextMac::DestroyGLContext()
    {
        if(_OpenGLDll)
        {
            ::dlclose(_OpenGLDll);
        }
    }

    void GLContextMac::MakeCurrContext()
    {
        
    }

    void GLContextMac::DlOpen()
    {
        if(!_OpenGLDll)
        {
            _OpenGLDll = ::dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LOCAL|RTLD_LAZY);
        }
        if(!_OpenGLDll)
        {
            SN_ERR("Failed To Open /System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL Dll.\n");
        }
    }
    //=GLContext-End===========================================================================================================================
}
#endif
