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

#if PLATFORM == PLATFORM_WINDOW
#include "OSPlatform.h"
namespace SkySnow
{
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	void GLWindow::ImportAPIEntryPointer()
	{
		//获取拓展的函数指针
		#define GET_APIENTRY_POINTER(FunType,Fun) Fun = (FunType)wglGetProcAddress(#Fun);
		APIENTRY_POINTER(GET_APIENTRY_POINTER);
	}


	GLContextWin::GLContextWin()
		: _OpenGL32Dll(nullptr)
	{

	}
	GLContextWin::~GLContextWin()
	{

	}

	void GLContextWin::CreateGLContext()
	{
		DlOpen();
		#define GET_WGL_APIENTRY_POINTER(FunType,Wgl_Fun) Wgl_Fun = (FunType)(void*)::GetProcAddress( (HMODULE)_OpenGL32Dll, #Wgl_Fun);
		//WGL_APIENTRY_POINTER(GET_WGL_APIENTRY_POINTER);

		_Hdc = GetDC((HWND)_GOSPlatformInfo->_NativeWindow);
		HWND hwnd = CreateWindowA("STATIC", "", WS_POPUP | WS_DISABLED, -32000, -32000, 0, 0, NULL, NULL, GetModuleHandle(NULL), 0);
		HDC hdc = GetDC(hwnd);
		
		HGLRC context = CreateGLContextInternal(hdc);

		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
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

	}

	void GLContextWin::DlOpen()
	{
		if (!_OpenGL32Dll)
		{
			_OpenGL32Dll = (void*)::LoadLibraryA("opengl32.dll");
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
}
#endif
