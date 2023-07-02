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
namespace SkySnow
{
    struct GLTextureFormat
    {
        GLTextureFormat()
            : _GLFormat(GL_NONE)
            , _GLType(GL_NONE)
            , _IsCompressed(false)
            , _IsBGRA(false)
        {
            _GLInternalFormat[0] = GL_NONE;
            _GLInternalFormat[1] = GL_NONE;
            _GLSizeInternalFormat[0] = GL_NONE;
            _GLSizeInternalFormat[1] = GL_NONE;
        }
        
        GLTextureFormat(GLenum inInternalFormat,
                        GLenum inInternalFormatSrgb,
                        GLenum inFormat,
                        GLenum inType,
                        bool   inIsCompressed,
                        bool   inIsBGRA
                        )
            : _GLFormat(inFormat)
            , _GLType(inType)
            , _IsCompressed(inIsCompressed)
            , _IsBGRA(inIsBGRA)
        {
            _GLInternalFormat[0] = inInternalFormat;
            _GLInternalFormat[1] = inInternalFormatSrgb;
            _GLSizeInternalFormat[0] = inInternalFormat;
            _GLSizeInternalFormat[1] = inInternalFormatSrgb;
        }
        //0 is rgb,1 is srgb
        GLenum _GLInternalFormat[2];
        GLenum _GLSizeInternalFormat[2];
        GLenum _GLFormat;
        GLenum _GLType;
        bool   _IsCompressed;
        bool   _IsBGRA;
    };
//    extern GLTextureFormat GGLTextureFormat[PixelFormat::PF_End];
    //Texture2D/Texture2DArray
    //Texture3D
    //TextureCube
    //UnPackBuffer
    //Sampler:2D/2DArray/3D/Cube
    //Texture Stage(引擎只支持不可变纹理)
    namespace OGLTexture
    {
        inline uint32 CalMaxMipmapLevel(uint32 size)
        {
            uint32 mipCount = 1;
            while(size >>= 1)
            {
                mipCount ++;
            }
            return mipCount;
        }
        inline uint32 CalMaxMipmapLevel(uint32 width,uint32 height)
        {
            return CalMaxMipmapLevel(width > height ? width : height);
        }

        inline bool IsPowerOftwo(uint32 value)
        {
            return ((value & (value - 1)) == 0);
        }
        inline uint32 CalMaxMipmapLevel(uint32 width,uint32 height,uint32 depth)
        {
            return CalMaxMipmapLevel(width > height ? width : height,depth);
        }
    
        template<typename TextureType>
        void CreateTextureInternal(TextureType* texture,uint32 sizex,uint32 sizey,uint32 sizez,uint8 format,uint32 numMips,uint32 numSamples,TextureUsageType usageType,uint8* data);
        bool TexStorageImage(GLenum target,uint32 mipLevel,GLenum internalFormat,uint32 sizex,uint32 sizey,uint32 sizez,GLenum format,GLenum type);
        void TexImage(GLenum target,uint32 numSamples,GLint mipLevel,GLint internalFormat,uint32 sizex, uint32 sizey,uint32 sizez,GLint border,GLenum format,GLenum type,const GLvoid* data);
        void TexSubImage(GLenum target,uint32 numSamples,GLint mipLevel,GLint offsetx,GLint offsety,GLint offsetz,uint32 sizex, uint32 sizey,uint32 sizez,GLenum format,GLenum type,const GLvoid* data);
        void CompressedTexImage(GLenum target,GLint mipLevel,GLenum internalFormat,uint32 sizex, uint32 sizey,uint32 sizez,GLint border,GLsizei imageSize,const GLvoid* data);
        void CompressedTexSubImage(GLenum target,GLint mipLevel,GLint offsetx,GLint offsety,GLint offsetz,uint32 sizex, uint32 sizey,uint32 sizez,GLenum format,GLsizei imageSize,const GLvoid* data);
        bool HasTextureUsageType(TextureUsageType curr,TextureUsageType target);

		void SetupTextureFormat(PixelFormat pFormat, const GLTextureFormat& glFormat);

        void InitTextureFormat();
    }


}
