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
#include "GL3.h"
#include "LogAssert.h"
#if PLATFORM == PLATFORM_MAC
//MacOS use System GLFunction and use low GL4.x
namespace SkySnow
{
	class GLMac : public OpenGL3
	{
	public:
		static inline GRIFeature GetFeatureType()
		{
			return EOpenGL;
		}
        
        static void InitialExtensions()
        {
            ImportAPIEntryPointer();
            OpenGL3::InitialExtensions();
        }
    private:
        static void ImportAPIEntryPointer();

	};
    //maxosx not export opengl function
    class DriveContextMac : public DriveContext
    {
    public:
        DriveContextMac();
        ~DriveContextMac();
        
        virtual void CreateGLContext(void* inNativeWindow) override;
        
        virtual void DestroyGLContext() override;
        
        virtual void MakeCurrContext() override;
        
        virtual void SwapBuffer() override;
        
    private:
        GLContextState  _GLContextState;
        GLuint          _VertexArrayObject;
        void*           _GLContext;
        void*           _View;
    };
}
typedef SkySnow::GLMac OpenGL;
#endif
