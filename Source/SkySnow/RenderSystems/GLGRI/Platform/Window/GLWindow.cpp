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
#include "OSPlatform.h"

#if PLATFORM == PLATFORM_WINDOW


#define DEFINE_APIENTRY_POINTER(FunType,Fun) FunType Fun = NULL;
        GL_APIENTRYPOINTER_DLL(DEFINE_APIENTRY_POINTER);
        GL_APIENTRYPOINTER(DEFINE_APIENTRY_POINTER);
        GL_APIENTRYPOINTS_OPTIONAL(DEFINE_APIENTRY_POINTER);
        //WGL_APIENTRYPOINTER_DLL(DEFINE_APIENTRY_POINTER);
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

	GLContextWin::GLContextWin()
		: _OpenGL32Dll(nullptr)
	{

	}
	GLContextWin::~GLContextWin()
	{

	}

	void GLContextWin::CreateGLContext()
	{
		OpenOpenGLLib();

		_Hdc = GetDC((HWND)_GOSPlatformInfo->_NativeWindow);
		HWND hwnd = CreateWindowA("STATIC", "", WS_POPUP | WS_DISABLED, -32000, -32000, 0, 0, NULL, NULL, GetModuleHandle(NULL), 0);
		HDC hdc = GetDC(hwnd);
		
		HGLRC context = CreateGLContextInternal(hdc);

		wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

		int32_t attrs[] =
		{
			WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
			WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_ALPHA_BITS_ARB,     8,
			WGL_COLOR_BITS_ARB,     32,
			WGL_DEPTH_BITS_ARB,     24,
			WGL_STENCIL_BITS_ARB,   0,
			WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
			WGL_SAMPLES_ARB,        0,
			WGL_SAMPLE_BUFFERS_ARB, GL_FALSE,
			0
		};
		
		int result;
		uint32_t numFormats = 0;
		do
		{
			result = wglChoosePixelFormatARB(_Hdc, attrs, NULL, 1, &_PixelFormat, &numFormats);
			if (0 == result
				|| 0 == numFormats)
			{
				attrs[3] >>= 1;
				attrs[1] = attrs[3] == 0 ? 0 : 1;
			}

		} while (0 == numFormats);

		DescribePixelFormat(_Hdc, _PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &_Pfd);

		result = SetPixelFormat(_Hdc, _PixelFormat, &_Pfd);
		int32_t contextAttrs[9] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 1,
			WGL_CONTEXT_FLAGS_ARB, true,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};
		_Context = wglCreateContextAttribsARB(_Hdc, 0, contextAttrs);
		if (NULL == _Context)
		{
			// nVidia doesn't like context profile mask for contexts below 3.2?
			contextAttrs[6] = WGL_CONTEXT_PROFILE_MASK_ARB == contextAttrs[6] ? 0 : contextAttrs[6];
			_Context = wglCreateContextAttribsARB(_Hdc, 0, contextAttrs);
		}
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(context);
		DestroyWindow(hwnd);

		if (NULL == _Context)
		{
			_Context = CreateGLContextInternal(_Hdc);
		}
		result = wglMakeCurrent(_Hdc, _Context);
		wglSwapIntervalEXT(0);
        //window export opengl function
        OpenGL::InitialExtensions();
	}

	void GLContextWin::DestroyGLContext()
	{
        if(_OpenGL32Dll)
        {
            ::FreeLibrary( (HMODULE)_OpenGL32Dll);
        }
	}

	void GLContextWin::MakeCurrContext()
	{
		wglMakeCurrent(_Hdc, _Context);
	}

	void GLContextWin::OpenOpenGLLib()
	{
		if (!_OpenGL32Dll)
		{
			//获取opengl32dll函数地址
			_OpenGL32Dll = (void*)::LoadLibraryA("opengl32.dll");
			//必须通过opengl32的dll地址获取函数指针
			//#define GET_WGLAPIENTRY_POINTER_DLL(WglFunType,WglFun) WglFun = (WglFunType)::GetProcAddress((HMODULE)_OpenGL32Dll, #WglFun);
			//WGL_APIENTRYPOINTER_DLL(GET_WGLAPIENTRY_POINTER_DLL);
			//GL_APIENTRYPOINTER_DLL(GET_WGLAPIENTRY_POINTER_DLL);

			////可以通过wgl获取函数指针
			//#define GET_APIENTRY_POINTER(FunType,Fun) Fun = (FunType)wglGetProcAddress(#Fun);
			//GL_APIENTRYPOINTER(GET_APIENTRY_POINTER);
			//GL_APIENTRYPOINTS_OPTIONAL(GET_APIENTRY_POINTER);
			//检索gl函数指针是否都已经初始化完毕
			//#define CHECK_GLAPIENTRYPOINTS(FunType,Fun) if(Fun == NULL){SN_WARN("Failed to find entry point for %s",#Fun);}
			//WGL_APIENTRYPOINTER_DLL(CHECK_GLAPIENTRYPOINTS);
			//GL_APIENTRYPOINTER_DLL(CHECK_GLAPIENTRYPOINTS);
			//GL_APIENTRYPOINTER(CHECK_GLAPIENTRYPOINTS);
			//GL_APIENTRYPOINTS_OPTIONAL(CHECK_GLAPIENTRYPOINTS);
		}
		if (!_OpenGL32Dll)
		{
			SN_ERR("Failed To Open opengl32.dll.\n");
		}
	}

	HGLRC GLContextWin::CreateGLContextInternal(HDC hdc)
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
		int result;
		result = SetPixelFormat(hdc, pixelFormat, &pfd);
		HGLRC context = wglCreateContext(hdc);
		result = wglMakeCurrent(hdc, context);
		return context;
	}

	void PlatformDeviceContextInit()
	{
		void* dllPointer = (void*)::LoadLibraryA("opengl32.dll");
		//必须通过opengl32的dll地址获取函数指针
		#define GET_WGLAPIENTRY_POINTER_DLL(WglFunType,WglFun) WglFun = (WglFunType)::GetProcAddress((HMODULE)dllPointer, #WglFun);
		//WGL_APIENTRYPOINTER_DLL(GET_WGLAPIENTRY_POINTER_DLL);
		GL_APIENTRYPOINTER_DLL(GET_WGLAPIENTRY_POINTER_DLL);
		wglGetProcAddress = (PFNWGLGETPROCADDRESSPROC)::GetProcAddress((HMODULE)dllPointer, "wglGetProcAddress");
		wglMakeCurrent = (PFNWGLMAKECURRENTPROC)::GetProcAddress((HMODULE)dllPointer, "wglMakeCurrent");
		wglCreateContext = (PFNWGLCREATECONTEXTPROC)::GetProcAddress((HMODULE)dllPointer, "wglCreateContext");
		wglDeleteContext = (PFNWGLDELETECONTEXTPROC)::GetProcAddress((HMODULE)dllPointer, "wglDeleteContext");

		//可以通过wgl获取函数指针
		#define GET_APIENTRY_POINTER(FunType,Fun) Fun = (FunType)wglGetProcAddress(#Fun);
		GL_APIENTRYPOINTER(GET_APIENTRY_POINTER);
		GL_APIENTRYPOINTS_OPTIONAL(GET_APIENTRY_POINTER);

		//检索gl函数指针是否都已经初始化完毕
		#define CHECK_GLAPIENTRYPOINTS(FunType,Fun) if(Fun == NULL){SN_WARN("Failed to find entry point for %s",#Fun);}
		//WGL_APIENTRYPOINTER_DLL(CHECK_GLAPIENTRYPOINTS);
		GL_APIENTRYPOINTER_DLL(CHECK_GLAPIENTRYPOINTS);
		GL_APIENTRYPOINTER(CHECK_GLAPIENTRYPOINTS);
		GL_APIENTRYPOINTS_OPTIONAL(CHECK_GLAPIENTRYPOINTS);
	}
}
#endif
