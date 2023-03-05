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
#include "GL4.h"
#include "LogAssert.h"
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_LINUX

namespace SkySnow
{
#define APIENTRY_POINTER(Macro)\
        Macro(PFNGLVIEWPORTPROC, glViewport)\
        Macro(PFNGLCLEARPROC, glClear)\
        Macro(PFNGLCLEARCOLORPROC, glClearColor)\
        Macro(PFNGLGETERRORPROC, glGetError)

	class GLMac : public OpenGL4
	{
	public:
		static inline GRIFeature GetFeatureType()
		{
			return EOpenGL;
		}
        
        static void InitialExtensions()
        {
            ImportAPIEntryPointer();
            OpenGL4::InitialExtensions();
        }
    private:
        static void ImportAPIEntryPointer();

	};
    //maxosx not export opengl function
    class GLContextMac : public GLContext
    {
    public:
        GLContextMac();
        ~GLContextMac();
        
        virtual void CreateGLContext() override;
        
        virtual void DestroyGLContext() override;
        
        virtual void MakeCurrContext() override;
        
        virtual void SwapGLTemp() override;
    private:
        void DlOpen();
        
    private:
        void*    _OpenGLDll;
        void*    _GLContext;
        void*    _View;
    };
}
typedef SkySnow::GLMac OpenGL;
#endif
