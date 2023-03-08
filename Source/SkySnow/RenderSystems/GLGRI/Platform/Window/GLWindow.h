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
#include "LogAssert.h"
#include "UString.h"
#include "GL4.h"
#if PLATFORM == PLATFORM_WINDOW
namespace SkySnow
{
	typedef PROC(APIENTRYP PFNWGLGETPROCADDRESSPROC) (LPCSTR lpszProc);
	typedef BOOL(APIENTRYP PFNWGLMAKECURRENTPROC) (HDC hdc, HGLRC hglrc);
	typedef HGLRC(APIENTRYP PFNWGLCREATECONTEXTPROC) (HDC hdc);
	typedef BOOL(APIENTRYP PFNWGLDELETECONTEXTPROC) (HGLRC hglrc);

	extern PFNWGLGETPROCADDRESSPROC wglGetProcAddress;
	extern PFNWGLMAKECURRENTPROC wglMakeCurrent;
	extern PFNWGLCREATECONTEXTPROC wglCreateContext;
	extern PFNWGLDELETECONTEXTPROC wglDeleteContext;

	class GLWindow : public OpenGL4
	{
	public:
		static inline GRIFeature GetFeatureType()
		{
			return EOpenGL;
		}

		static void InitialExtensions()
		{
			UString version = (const char*)glGetString(GL_VERSION);
			std::vector<UString> res = version.Split('.');
			if (res.size() > 1)
			{
				_MajorVersion = atoi(res[0].C_Str());
				_MinorVersion = atoi(res[1].C_Str());
			}
			_ExtensionsStr = (const char*)glGetString(GL_EXTENSIONS);

			OpenGL4::InitialExtensions();
			if (_SupportVertexFormatBinding)
			{
				SN_LOG("Support VFB");
			}
		}
	};

    class GLContextWin : public GLContext
    {
    public:
        GLContextWin();
        ~GLContextWin();
        
        virtual void CreateGLContext() override;
        
        virtual void DestroyGLContext() override;
        
        virtual void MakeCurrContext() override;

    private:
		void OpenOpenGLLib();
		HGLRC CreateGLContextInternal(HDC hdc);
	private:
		void* _OpenGL32Dll;
		HDC _Hdc;
		int _PixelFormat;
		PIXELFORMATDESCRIPTOR _Pfd;
		HGLRC _Context;
    };
}
typedef SkySnow::GLWindow OpenGL;
#endif

