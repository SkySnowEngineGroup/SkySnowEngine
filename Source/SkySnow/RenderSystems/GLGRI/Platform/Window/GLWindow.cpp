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
namespace SkySnow
{
	void GLWindow::GetAPIEntryPointer()
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
		//#define GET_WGL_APIENTRY_POINTER(FunType,Wgl_Fun) Wgl_Fun = (FunType)(void*)::GetProcAddress( (HMODULE)_OpenGL32Dll, #Wgl_Fun);
		//WGL_APIENTRY_POINTER(GET_WGL_APIENTRY_POINTER);
	}

	void GLContextWin::DestroyGLContext()
	{

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
			SN_ERR("Failed to open opengl32.dll.\n");
		}
	}
}
#endif
