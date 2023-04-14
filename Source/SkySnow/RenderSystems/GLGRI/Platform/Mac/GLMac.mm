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
    {
        
    }
    GLContextMac::~GLContextMac()
    {
    }

    void GLContextMac::CreateGLContext()
    {
        NSObject* nativeWindow = (NSObject*)_GOSPlatformInfo->_NativeWindow;
        NSView* view = [[nativeWindow contentView] retain];
        
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
        // 创建NSOpenGLContext
        NSOpenGLContext *openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
        // 设置当前上下文
        [openGLContext makeCurrentContext];
        // 将OpenGL上下文与窗口关联
        [openGLContext setView:view];
        
        OpenGL::InitialExtensions();
        _GLContext = openGLContext;
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
        [_GLContext release];
    }

    void GLContextMac::MakeCurrContext()
    {
        NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
        [glContext makeCurrentContext];
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }
    
    void GLContextMac::SwapBuffer()
    {
        NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
        [glContext flushBuffer];
    }
    
}
#endif
