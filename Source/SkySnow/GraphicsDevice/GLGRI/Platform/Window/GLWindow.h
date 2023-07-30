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
#include "LogAssert.h"
#include "UString.h"
#include "GL4.h"
#if PLATFORM == PLATFORM_WINDOW
namespace SkySnow
{
	//Initial PixelFormat
	static void InitPixelFormatForDrive(HDC hdc);

	static void ProcAddressInit(void* gl32Dll);

	static bool CreateGLContextCore(HGLRC& driveContext, HDC hdc, int majorVersion, int minorVersion, HGLRC shareContext);

	static void CreateDummyWindow(HWND& hwnd, HDC& hdc);

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

    class DriveContextWin : public DriveContext
    {
    public:
		friend class DrivePlatform;
		DriveContextWin(bool isExtern = true);
        ~DriveContextWin();
        
        virtual void ReleaseContext() override;
        
        virtual void MakeCurrContext() override;

		virtual void SwapBuffer() override;
	private:
		bool					_IsExtern = true;
		int						_PixelFormat;
        GLuint					_VertexArrayObject;
		GLuint					_FrameBufferObject;
		HDC						_Hdc;
        HWND					_HWND;
		HGLRC					_GLContext;
    };
}
typedef SkySnow::GLWindow OpenGL;
#endif

