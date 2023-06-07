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
#include "GLTexture.h"
#include "GLProfiles.h"
#include "GRICommons.h"
#include "RefCounted.h"
#include "GRIResource.h"
namespace SkySnow
{
    extern GLTextureFormat GGLTextureFormat[PixelFormat::PF_End];
    class GLBaseTexture
    {
    public:
        GLBaseTexture(
            uint32 inSizeX,
            uint32 inSizeY,
            uint32 inSizeZ,
            uint32 inNumLevel,
            uint32 inNumSamples,
            PixelFormat inFormat,
            bool inIsCubemap,
            TextureUsageType inTUT
        )
            : _GpuHandle(0)
            , _Target(-1)
            , _SizeX(inSizeX)
            , _SizeY(inSizeY)
            , _SizeZ(inSizeZ)
            , _NumLevel(inNumLevel)
            , _NumSamples(inNumSamples)
            , _PixelFormat(inFormat)
            , _IsCubemap(inIsCubemap)
            , _TextureUT(inTUT)
        {
        }
        virtual ~GLBaseTexture()
        {
        }

        GLuint GetGpuHandle()
        {
            return _GpuHandle;
        }
    protected:
        void CreateTexture();
    public:
        bool                _IsCubemap;
        GLuint              _GpuHandle;
        GLenum              _Target;
        uint32              _SizeX;
        uint32              _SizeY;
        uint32              _SizeZ;
        uint32              _NumLevel;
        uint32              _NumSamples;
        PixelFormat         _PixelFormat;
        TextureUsageType    _TextureUT;
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
            : GRITexture2D(GRT_Texture2D)
            , GLBaseTexture(inSizeX,inSizeY,0,inNumLevel,inNumSamples,inFormat,false,inTUT)
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
            : GRITexture2DArray()
            , GLBaseTexture(inSizeX, inSizeY, inSizeZ, inNumLevel, inNumSamples,inFormat, false, inTUT)
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
            : GRITexture3D(GRT_Texture3D)
            , GLBaseTexture(inSizeX, inSizeY, inSizeZ, inNumLevel, inNumSamples,inFormat, false, inTUT)
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
            : GRITextureCube()
            , GLBaseTexture(inSize,inSize,0,inNumLevel,inNumSamples,inFormat,true,inTUT)
        {
        }
    };
}
