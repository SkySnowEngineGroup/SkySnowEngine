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
#include "GRIResource.h"
#include "GLTexture.h"
namespace SkySnow
{
    class GLBaseTexture
    {
    public:
        GLBaseTexture(bool inIsCubemap)
            : _GpuHandle(0)
            , _Target(-1)
            , _IsCubemap(inIsCubemap)
            , _Attachment(GL_NONE)
        {
        }
        virtual ~GLBaseTexture()
        {
            SN_LOG("GLBaseTexture DesConstruct.");
            if (_GpuHandle)
            {
                glDeleteTextures(1, &_GpuHandle);
                SN_LOG("GLBaseTexture Reclaiming GPU Resources.");
            }
        }

        GLuint GetGpuHandle()
        {
            return _GpuHandle;
        }
    public:
        bool                _IsCubemap;
        GLuint              _GpuHandle;
        GLenum              _Target;
        GLenum              _Attachment;
    };

    class GRIGLTexture2D : public GRITexture2D , public GLBaseTexture
    {
    public:
		GRIGLTexture2D(
            uint32 inSizeX,
			uint32 inSizeY,
			uint32 inNumLevel,
			uint32 inNumSamples,
			PixelFormat inFormat,
			TextureUsageType inTUT
        )
            : GRITexture2D(inSizeX,inSizeY,inNumLevel,inNumSamples,inFormat,inTUT)
            , GLBaseTexture(false)
        {
        }
    };

    class GRIGLTexture2DArray : public GRITexture2DArray , public GLBaseTexture
    {
    public:
		GRIGLTexture2DArray(
            uint32 inSizeX,
			uint32 inSizeY,
			uint32 inSizeZ,
			uint32 inNumLevel,
			uint32 inNumSamples,
			PixelFormat inFormat,
			TextureUsageType inTUT
        )
			: GRITexture2DArray(inSizeX,inSizeY,inSizeZ,inNumLevel,inNumSamples,inFormat,inTUT)
            , GLBaseTexture(false)
        {
        }
    };

    class GRIGLTexture3D : public GRITexture3D , public GLBaseTexture
    {
    public:
		GRIGLTexture3D(
            uint32 inSizeX,
			uint32 inSizeY,
			uint32 inSizeZ,
			uint32 inNumLevel,
			uint32 inNumSamples,
			PixelFormat inFormat,
			TextureUsageType inTUT
        )
            : GRITexture3D(inSizeX, inSizeY, inSizeZ, inNumLevel, inNumSamples, inFormat, inTUT)
            , GLBaseTexture(false)
        {
        }
    };

    class GRIGLTextureCube : public GRITextureCube, public GLBaseTexture
    {
    public:
		GRIGLTextureCube(
            uint32 inSize,
			uint32 inNumLevel,
			uint32 inNumSamples,
			PixelFormat inFormat,
			TextureUsageType inTUT
        )
            : GRITextureCube(inSize, inNumLevel, inNumSamples, inFormat, inTUT)
            , GLBaseTexture(true)
        {
        }
    };
}
