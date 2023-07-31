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
#include "GLTexture.h"
#if PLATFORM == PLATFORM_MAC
#include <dlfcn.h>
#include <AvailabilityMacros.h>
#include <Cocoa/Cocoa.h>
namespace SkySnow
{
    void* CreateGLContextCore(void* inSareContext)
    {
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
        NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
        NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat: pixelFormat shareContext: (NSOpenGLContext*)inSareContext];
        [pixelFormat release];
        
        if(!context)
        {
            SN_LOG("Macos Create NSOpenGLContext Failure.");
        }
        //设置处置同步
        GLint interval = 0;
        [context setValues:&interval forParameter:NSOpenGLContextParameterSwapInterval];
        //设置表面不透明度（例如：设置为透明）
        int32 surfaceOpacity = 0;
        [context setValues:&surfaceOpacity forParameter:NSOpenGLContextParameterSurfaceOpacity];
        
        return context;
    }
    void GLMac::ImportAPIEntryPointer()
    {
    }
    //=GLContext-Start======================================================================================================================
    DriveContextMac::DriveContextMac(bool isExtern)
        :  _IsExtern(isExtern)
        , _VertexArrayObject(0)
        , _GLContext(nullptr)
        , _View(nullptr)
    {
    }
    DriveContextMac::~DriveContextMac()
    {
    }
    
    void DriveContextMac::ReleaseContext()
    {
        if(_VertexArrayObject)
        {
            glDeleteVertexArrays(1, &_VertexArrayObject);
        }
        if(!_IsExtern)
        {
            NSOpenGLView* glView = (NSOpenGLView*)_View;
            [glView release];
            _View = nullptr;
        }
        if(_GLContext)
        {
            NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
            [glContext release];
            _GLContext = nullptr;
        }
    }
    //todo:The context can only be rebound to the rendering thread when you switch screens
    void DriveContextMac::MakeCurrContext()
    {
        NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
        [glContext makeCurrentContext];
    }
    //Each frame is called to exchange the rendered off-screen data to the up-screen data
    //to display the rendering of the corresponding window
    void DriveContextMac::SwapBuffer()
    {
        NSOpenGLContext* glContext = (NSOpenGLContext*)_GLContext;
        [glContext flushBuffer];
    }

    DrivePlatform::DrivePlatform()
    {
        DriveInit();
        CreateDriveContext();
    }

    DrivePlatform::~DrivePlatform()
    {
        if (_RenderContext)
        {
            _RenderContext->ReleaseContext();
            delete _RenderContext;
            _RenderContext = nullptr;
        }
        if (_MainContext)
        {
            _MainContext->ReleaseContext();
            delete _MainContext;
            _MainContext = nullptr;
        }
    }

    DriveContextState DrivePlatform::GetDriveContextState()
    {
        NSOpenGLContext* context = [NSOpenGLContext currentContext];
        if (context == ((DriveContextMac*)_RenderContext)->_GLContext)
        {
            return DriveContextState::RenderingContext;
        }
        else if (context == ((DriveContextMac*)_MainContext)->_GLContext)
        {
            return DriveContextState::MainContext;
        }
        else if (context)
        {
            return DriveContextState::OtherContext;
        }
        else
        {
            return DriveContextState::NoUse;
        }
        return DriveContextState::NoUse;
    }

    DriveContext* DrivePlatform::CreateGLContextCoreFromViewport(void* windowHandle)
    {
        DriveContextMac* shareContext = new DriveContextMac(false);
        
        NSWindow* nsWindow = (NSWindow*)windowHandle;
        NSRect contentRect = [[nsWindow contentView] frame];
        NSOpenGLView* glView = [[NSOpenGLView alloc] initWithFrame:contentRect];
        NSOpenGLContext* glContext = (NSOpenGLContext*)CreateGLContextCore((NSOpenGLContext*)(((DriveContextMac*)_MainContext)->_GLContext));
        
        [glContext makeCurrentContext];
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        NSView* parentView = [nsWindow contentView];
        if(parentView)
        {
//            [glView setFrameSize:[nsWindow frame].size];
            [glView setAutoresizingMask:( NSViewHeightSizable |NSViewWidthSizable |NSViewMinXMargin |NSViewMaxXMargin |NSViewMinYMargin |NSViewMaxYMargin )];
            //将glview设置为子窗口
            [parentView addSubview:glView];
        }
        else
        {
            [nsWindow setContentView: glView];
        }
        [glContext setView: glView];
        
        shareContext->_WindowHandle = nsWindow;
        shareContext->_View = glView;
        shareContext->_GLContext = glContext;
        shareContext->_VertexArrayObject = vao;
        
        [NSOpenGLContext clearCurrentContext];
        return shareContext;
    }
    void DrivePlatform::DriveInit()
    {
        SN_LOG("Macos Not Import Function.");
    }

    void DrivePlatform::CreateDriveContext()
    {
        DriveContextMac* mainContextMac = new DriveContextMac();
        DriveContextMac* renderContextMac = new DriveContextMac();
        
        mainContextMac->_GLContext = CreateGLContextCore(nullptr);
        renderContextMac->_GLContext = CreateGLContextCore((NSOpenGLContext*)mainContextMac->_GLContext);
        
        [(NSOpenGLContext*)renderContextMac->_GLContext makeCurrentContext];
        glGenVertexArrays(1,&renderContextMac->_VertexArrayObject);
        glBindVertexArray(renderContextMac->_VertexArrayObject);
        
        glFlush();
        [NSOpenGLContext clearCurrentContext];
        
        [(NSOpenGLContext*)mainContextMac->_GLContext makeCurrentContext];
        glGenVertexArrays(1,&mainContextMac->_VertexArrayObject);
        glBindVertexArray(mainContextMac->_VertexArrayObject);
        
        OpenGL::InitialExtensions();
        OGLTexture::InitTextureFormat();
        _MainContext = mainContextMac;
        _RenderContext = renderContextMac;
        [NSOpenGLContext clearCurrentContext];
    }
}
#endif
