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
//        #define GET_APIENTRY_POINTER(FunType,Fun) Fun = (FunType)dlsym(RTLD_SELF, #Fun);
//                APIENTRY_POINTER(GET_APIENTRY_POINTER);
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
        if(!glContext)
        {
            SN_ERR("GLContext is null.");
        }
        return glContext;
    }
    GLContextMac::GLContextMac()
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
        if(!contentView)
        {
            SN_ERR("contentView is null.");
        }
        
        NSOpenGLPixelFormatAttribute profile = NSOpenGLProfileVersion3_2Core;
        NSOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
            NSOpenGLPFAOpenGLProfile, profile,
            NSOpenGLPFAColorSize,     24,
            NSOpenGLPFAAlphaSize,     8,
            NSOpenGLPFADepthSize,     24,
            NSOpenGLPFAStencilSize,   8,
            NSOpenGLPFADoubleBuffer,  true,
            NSOpenGLPFAAccelerated,   true,
            NSOpenGLPFANoRecovery,    true,
            0,                        0,
        };
        NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
        NSRect glViewRect = [contentView bounds];
        NSOpenGLView* glView = [[NSOpenGLView alloc] initWithFrame:glViewRect pixelFormat:pixelFormat];

        [pixelFormat release];
        
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
        [glContext makeCurrentContext];
        GLint interval = 0;
        [glContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];
        void (^set_view)(void) = ^(void)
        {
            [glContext setView:glView];
        };

        if([NSThread isMainThread])
        {
            set_view();
        }
        else
        {
            dispatch_sync(dispatch_get_main_queue(),set_view);
        }
        OpenGL::InitialExtensions();
        _GLContext = glContext;
    }

    void GLContextMac::DestroyGLContext()
    {
//        if(_OpenGLDll)
//        {
//            ::dlclose(_OpenGLDll);
//        }
    }

    void GLContextMac::MakeCurrContext()
    {
        
    }
//    void GLContextMac::SwapGLTemp()
//    {
////        bool vsync = !!(_flags&BGFX_RESET_VSYNC);
//        GLint interval = 1;
//        NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
//        [glContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];
//        
//        void (^update_view)(void) = ^(void) {
//            [glContext update];
//        };
//
//        if([NSThread isMainThread])
//        {
//            update_view();
//        }
//        else
//        {
//            dispatch_sync(dispatch_get_main_queue(),update_view);
//        }
//        glViewport(0,0,DEFAUT_WADTH,DEFAUT_HEIGHT);
//        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//        glClearColor(1,0,0,1);
//        
////        NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
//        [glContext makeCurrentContext];
//        [glContext flushBuffer];
//    }
    
    //use MacOS GL Function Pointer, So Not Get Dll Pointer And Not Import GLFunction By OpenGL DLL
    void GLContextMac::DlOpen()
    {
//        if(!_OpenGLDll)
//        {
//            _OpenGLDll = ::dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LOCAL|RTLD_LAZY);
//        }
//        if(!_OpenGLDll)
//        {
//            SN_ERR("Failed To Open /System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL Dll.\n");
//        }
    }
    //=GLContext-End===========================================================================================================================
}
#endif
