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
#include "GLWindow.h"
#include "GLProfiles.h"
#include "GLTexture.h"
#if PLATFORM == PLATFORM_WINDOW

#define DEFINE_APIENTRY_POINTER(FunType,Fun) FunType Fun = NULL;
        GL_APIENTRYPOINTER_DLL(DEFINE_APIENTRY_POINTER);
        GL_APIENTRYPOINTER(DEFINE_APIENTRY_POINTER);
        GL_APIENTRYPOINTS_OPTIONAL(DEFINE_APIENTRY_POINTER);
#undef DEFINE_APIENTRY_POINTER

namespace SkySnow
{
	PFNWGLGETPROCADDRESSPROC wglGetProcAddress = NULL;
	PFNWGLMAKECURRENTPROC wglMakeCurrent = NULL;
	PFNWGLCREATECONTEXTPROC wglCreateContext = NULL;
	PFNWGLDELETECONTEXTPROC wglDeleteContext = NULL;
	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = NULL;
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	PFNWGLGETCURRENTCONTEXTPROC wglGetCurrentContext = NULL;

	void CreateDummyWindow(HWND& hwnd, HDC& hdc)
	{
		hwnd = CreateWindowA("STATIC",
			"",
			WS_POPUP | WS_DISABLED,
			-32000, -32000, 0, 0, 
			NULL, NULL,
			GetModuleHandle(NULL),
			0);
		hdc = GetDC(hwnd);
		InitPixelFormatForDrive(hdc);
	}
	bool CreateGLContextCore(HGLRC& driveContext, HDC hdc,int majorVersion, int minorVersion, HGLRC shareContext)
	{
		wglMakeCurrent(nullptr, nullptr);
		int attribList[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
			WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		driveContext = wglCreateContextAttribsARB(hdc, shareContext, attribList);
		if (driveContext)
		{
			wglMakeCurrent(hdc, driveContext);
			return true;
		}
		else
		{
			SN_ERR("OpenGL %d.%d not supported by driver", majorVersion, minorVersion);
		}
		return false;
	}
	void InitPixelFormatForDrive(HDC hdc)
	{
		PIXELFORMATDESCRIPTOR pfd;
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		DescribePixelFormat(hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		int result = SetPixelFormat(hdc, pixelFormat, &pfd);
		if (!pixelFormat || !result)
		{
			SN_LOG("Failed to set pixel format for device context.");
		}
	}
	void ProcAddressInit(void* gl32Dll)
	{
		if (!gl32Dll)
		{
			SN_ERR("Failed To Open opengl32.dll.\n");
		}
		if (gl32Dll)
		{
			//必须通过opengl32的dll地址获取函数指针
			#define GET_WGLAPIENTRY_POINTER_DLL(WglFunType,WglFun) WglFun = (WglFunType)::GetProcAddress((HMODULE)gl32Dll, #WglFun);
					GL_APIENTRYPOINTER_DLL(GET_WGLAPIENTRY_POINTER_DLL);

			//可以通过wgl获取函数指针
			#define GET_APIENTRY_POINTER(FunType,Fun) Fun = (FunType)wglGetProcAddress(#Fun);
					GL_APIENTRYPOINTER(GET_APIENTRY_POINTER);
					GL_APIENTRYPOINTS_OPTIONAL(GET_APIENTRY_POINTER);

			//检索gl函数指针是否都已经初始化完毕
			#define CHECK_GLAPIENTRYPOINTS(FunType,Fun) if(Fun == NULL){SN_WARN("Failed to find entry point for %s",#Fun);}
					GL_APIENTRYPOINTER_DLL(CHECK_GLAPIENTRYPOINTS);
					GL_APIENTRYPOINTER(CHECK_GLAPIENTRYPOINTS);
					GL_APIENTRYPOINTS_OPTIONAL(CHECK_GLAPIENTRYPOINTS);
		}
	}

	DriveContextWin::DriveContextWin(bool isExtern)
		: _VertexArrayObject(0)
		, _FrameBufferObject(0)
		, _IsExtern(isExtern)
		, _Hdc(NULL)
		, _HWND(NULL)
		, _PixelFormat(0)
		, _GLContext(NULL)
	{
	}
	DriveContextWin::~DriveContextWin()
	{

	}

	void DriveContextWin::ReleaseContext()
	{
		// this can be done from any context shared with ours, as long as it's not nil.
        if(_VertexArrayObject != -1)
        {
            glDeleteVertexArrays(1, &_VertexArrayObject);
        }
		if (_FrameBufferObject)
		{
			glDeleteFramebuffers(1, &_FrameBufferObject);
			_FrameBufferObject = 0;
		}
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(_GLContext);
        ReleaseDC(_HWND, _Hdc);
		if (_HWND && !_IsExtern)
		{
			DestroyWindow(_HWND);
		}
		_HWND = NULL;
	}

	void DriveContextWin::MakeCurrContext()
	{
		BOOL result = wglMakeCurrent(_Hdc, _GLContext);
		wglSwapIntervalEXT(1);
		if (!result)
		{
			result = wglMakeCurrent(nullptr, nullptr);
		}
	}

	void DriveContextWin::SwapBuffer()
	{
		SwapBuffers(_Hdc);
	}

	DrivePlatform::DrivePlatform()
		: _MainContext(nullptr)
		, _RenderContext(nullptr)
	{
		DriveInit();
		CreateDriveContext();
	}

	DrivePlatform::~DrivePlatform()
	{
		SN_LOG("DrivePlatform DesConstruct.");
		if (_RenderContext)
		{
			_RenderContext->ReleaseContext();
			delete _RenderContext;
			_RenderContext = nullptr;
			SN_LOG("DrivePlatform Reclaiming GPU Resources(_RenderContext).");
		}
		if (_MainContext)
		{
			_MainContext->ReleaseContext();
			delete _MainContext;
			_MainContext = nullptr;
			SN_LOG("DrivePlatform Reclaiming GPU Resources(_MainContext).");
		}
	}

	DriveContext* DrivePlatform::CreateGLContextCoreFromViewport(void* windowHandle)
	{
		DriveContextWin* winMainContext = new DriveContextWin();
		winMainContext->_HWND = (HWND)windowHandle;;
		winMainContext->_Hdc = GetDC(winMainContext->_HWND);

		InitPixelFormatForDrive(winMainContext->_Hdc);

		DriveContextWin* parentDriveContext = (DriveContextWin*)_MainContext;
		bool success = CreateGLContextCore( winMainContext->_GLContext,
											winMainContext->_Hdc,
											_MajorVersion, _MinorVersion,
											parentDriveContext->_GLContext);
		if (success)
		{
			glGenVertexArrays(1, &winMainContext->_VertexArrayObject);
			glBindVertexArray(winMainContext->_VertexArrayObject);
			glGenFramebuffers(1, &winMainContext->_FrameBufferObject);
			wglMakeCurrent(nullptr, nullptr);
		}
		else
		{
			SN_LOG("CreateGLContextCoreFromViewport Create GLContext Failure.");
		}
		return winMainContext;
	}
	//Import Opengl32.dll and import function address
	void DrivePlatform::DriveInit()
	{
		#pragma warning(push)
		#pragma warning(disable:4191)
		HWND hwnd;
		HDC hdc;
		CreateDummyWindow(hwnd, hdc);

		void*  gl32Dll = (void*)::LoadLibraryA("opengl32.dll");
		if (gl32Dll)
		{
			wglGetProcAddress = (PFNWGLGETPROCADDRESSPROC)::GetProcAddress((HMODULE)gl32Dll, "wglGetProcAddress");
			wglMakeCurrent = (PFNWGLMAKECURRENTPROC)::GetProcAddress((HMODULE)gl32Dll, "wglMakeCurrent");
			wglCreateContext = (PFNWGLCREATECONTEXTPROC)::GetProcAddress((HMODULE)gl32Dll, "wglCreateContext");
			wglDeleteContext = (PFNWGLDELETECONTEXTPROC)::GetProcAddress((HMODULE)gl32Dll, "wglDeleteContext");
			wglGetCurrentContext = (PFNWGLGETCURRENTCONTEXTPROC)::GetProcAddress((HMODULE)gl32Dll, "wglGetCurrentContext");
		}

		HGLRC context = wglCreateContext(hdc);
		//Note In the windowOS, unbind the bound thread before binding glcontext to a new thread
		int result = wglMakeCurrent(hdc, context);

		if (gl32Dll)
		{
			wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
			wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
			wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
		}

		if (wglCreateContextAttribsARB)
		{
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(context);
			if (CreateGLContextCore(context, hdc, _MajorVersion, _MinorVersion, nullptr))
			{
				_SupportOpenGL = true;
			}
		}
		if (_SupportOpenGL)
		{
			ProcAddressInit(gl32Dll);
			OpenGL::InitialExtensions();
			OGLTexture::InitTextureFormat();
			if (gl32Dll)
			{
				::FreeLibrary((HMODULE)gl32Dll);
			}
		}
		#pragma warning(pop)
		if (context)
		{
			wglMakeCurrent(hdc, context);
			wglDeleteContext(context);
		}

		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);
	}

	void DrivePlatform::CreateDriveContext()
	{
		//Create MainContext
		DriveContextWin* winMainContext = new DriveContextWin(false);
		CreateDummyWindow(winMainContext->_HWND, winMainContext->_Hdc);
		if (CreateGLContextCore(winMainContext->_GLContext, winMainContext->_Hdc, _MajorVersion, _MinorVersion, nullptr))
		{
			glGenVertexArrays(1, &winMainContext->_VertexArrayObject);
			glBindVertexArray(winMainContext->_VertexArrayObject);
			glGenFramebuffers(1, &winMainContext->_VertexArrayObject);
		}
		else
		{
			SN_LOG("Window Create MainContext Failure.");
		}
		_MainContext = winMainContext;

		//Create ShareContext
		DriveContextWin* winRenderContext = new DriveContextWin(false);
		CreateDummyWindow(winRenderContext->_HWND, winRenderContext->_Hdc);
		if (CreateGLContextCore(winRenderContext->_GLContext, winRenderContext->_Hdc, _MajorVersion, _MinorVersion, winMainContext->_GLContext))
		{
			glGenVertexArrays(1, &winRenderContext->_VertexArrayObject);
			glBindVertexArray(winRenderContext->_VertexArrayObject);
			glGenFramebuffers(1, &winRenderContext->_VertexArrayObject);
			wglMakeCurrent(nullptr, nullptr);
		}
		else
		{
			SN_LOG("Window Create MainContext Failure.");
		}
		
		_RenderContext = winRenderContext;
	}

	void DrivePlatform::MakeNullContext()
	{
		if (wglGetCurrentContext())
		{
			wglMakeCurrent(NULL, NULL);
		}
	}

	DriveContextState DrivePlatform::GetDriveContextState()
	{
		HGLRC glContext = wglGetCurrentContext();
		if (glContext == ((DriveContextWin*)_RenderContext)->_GLContext)
		{
			return DriveContextState::RenderingContext;
		}
		else if (glContext == ((DriveContextWin*)_MainContext)->_GLContext)
		{
			return DriveContextState::MainContext;
		}
		else if (glContext)
		{
			return DriveContextState::OtherContext;
		}
		else
		{
			return DriveContextState::NoUse;
		}
		return DriveContextState::NoUse;
	}
}
#endif
