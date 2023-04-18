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
    //=GLContext-Start======================================================================================================================
    GLContextMac::GLContextMac()
        : _VertexArrayObject(-1)
        , _GLContextState(GLContextState::NoUse)
    {
        
    }
    GLContextMac::~GLContextMac()
    {
    }

    void GLContextMac::CreateGLContext()
    {
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
        // 创建NSOpenGLPixelFormat
        NSOpenGLPixelFormatAttribute attrs[] = {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFAAlphaSize, 8,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            0
        };
        NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
        NSRect glViewRect = [contentView bounds];
        NSOpenGLView* glView = [[NSOpenGLView alloc] initWithFrame:glViewRect pixelFormat:pixelFormat];
        [pixelFormat release];
        
        if (nil != contentView)
        {
            //设置自适应大小glview
            [glView setAutoresizingMask:( NSViewHeightSizable |NSViewWidthSizable |NSViewMinXMargin |NSViewMaxXMargin |NSViewMinYMargin |NSViewMaxYMargin )];
            //将glview设置为子窗口
            [contentView addSubview:glView];
        }
        else
        {
            if (nil != nsWindow)
            {
                [nsWindow setContentView:glView];
            }
        }
        //获取上下文
        NSOpenGLContext* openGLContext = [glView openGLContext];
        //将当前上下文与当前线程绑定
        [openGLContext makeCurrentContext];
        //初始化拓展字段查询
        OpenGL::InitialExtensions();
        _GLContext = openGLContext;
        _View = glView;
        //default vao for this context
        glGenVertexArrays(1,&_VertexArrayObject);
        glBindVertexArray(_VertexArrayObject);
    }

    void GLContextMac::DestroyGLContext()
    {
        if(_VertexArrayObject != -1)
        {
            glDeleteVertexArrays(1, &_VertexArrayObject);
        }
        if(_GLContext != nullptr)
        {
            NSOpenGLView* glView = (NSOpenGLView*)_View;
            [glView release];
            NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
            [glContext release];
            _View       = nullptr;
            _GLContext  = nullptr;
        }
    }
    //todo:The context can only be rebound to the rendering thread when you switch screens
    void GLContextMac::MakeCurrContext()
    {
        if(_GLContextState == GLContextState::NoUse)
        {
            NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
            [glContext makeCurrentContext];
            _GLContextState = GLContextState::RenderingContext;
        }
    }
    //Each frame is called to exchange the rendered off-screen data to the up-screen data
    //to display the rendering of the corresponding window
    void GLContextMac::SwapBuffer()
    {
        NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
        [glContext flushBuffer];
    }
}
#endif
