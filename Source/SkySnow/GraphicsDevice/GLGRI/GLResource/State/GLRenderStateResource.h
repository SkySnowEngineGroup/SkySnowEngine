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
#include "GRICommons.h"
#include "GRIResource.h"
namespace SkySnow
{

    class GRIGLSamplerState : public GRISamplerState
    {
    public:
        GRIGLSamplerState()
            : GRISamplerState()
            , _GpuHandle(-1)
            , _WrapS(GL_REPEAT)
            , _WrapT(GL_REPEAT)
            , _WrapR(GL_REPEAT)
            , _LodBias(0)
            , _MinFilter(GL_NEAREST)
            , _MagFilter(GL_NEAREST)
            , _MaxAnisotropy(1)
            , _CompareMode(GL_NONE)
            , _CompareFunc(GL_ALWAYS)
        {
        }
    public:
        GLuint  _GpuHandle;
        GLenum  _WrapS;
        GLenum  _WrapT;
        GLenum  _WrapR;
        GLint   _LodBias;
        GLint   _MinFilter;
        GLint   _MagFilter;
        GLint   _MaxAnisotropy;
        GLint   _CompareMode;
        GLint   _CompareFunc;
    };
}
