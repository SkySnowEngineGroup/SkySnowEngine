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
#include "GRIGLDrive.h"
#include "GLTextureResource.h"
#include "GLTexture.h"
#include <iostream>
#include <algorithm>
namespace SkySnow
{
    GLTextureFormat GGLTextureFormat[PixelFormat::PF_End];
    void GRIGLDrive::GRICreateTexture2D(uint32 sizex, uint32 sizey, uint8 format, uint32 numMips, uint32 numSamples, TextureUsageType usageType, uint8* data,GRITexture2DRef& handle)
    {
        OGLTexture::CreateTextureInternal<GRIGLTexture2D>(dynamic_cast<GRIGLTexture2D*>(handle.GetReference()), sizex, sizey, 1, format, numMips, numSamples, usageType, data);
    }
    
    void GRIGLDrive::GRICreateTexture2DArray(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips, uint32 numSamples, TextureUsageType usageType,uint8* data,GRITexture2DArrayRef& handle)
    {
        OGLTexture::CreateTextureInternal<GRIGLTexture2DArray>(dynamic_cast<GRIGLTexture2DArray*>(handle.GetReference()), sizex, sizey, sizez, format, numMips, 1, usageType, data);
    }

    void GRIGLDrive::GRICreateTexture3D(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips,TextureUsageType usageType,uint8* data,GRITexture3DRef& handle)
    {
        OGLTexture::CreateTextureInternal<GRIGLTexture3D>(dynamic_cast<GRIGLTexture3D*>(handle.GetReference()), sizex, sizey, sizez, format, numMips, 1, usageType, data);
    }
    void GRIGLDrive::GRICreateTextureCube(uint32 size, uint8 format, uint32 numMips, TextureUsageType usageType,uint8* data,GRITextureCubeRef& handle)
    {
        OGLTexture::CreateTextureInternal<GRIGLTextureCube>(dynamic_cast<GRIGLTextureCube*>(handle.GetReference()), size, size, 1, format, numMips, 1, usageType, data);
    }
    //纹理更新规则
    /*
        1. Texture2D: MipCount = 0~10  Width * Height = 4 * 4
            Example更新数据参数: MipLevel = 0, Data = {4*4}
        2. Texture2DArray: MipCount = 0~10  Width * Height * Depth = 4 * 4 * 4
            Example更新数据参数: MipLevel = 0, arrayIndex = 0 Data = {4*4}
        3. Texture3D: MipCount = 0~10  Width * Height * Depth = 4 * 4 * 4
            Example更新数据参数: MipLevel = 0, Data = {4*4|4*4|4*4|4*4}
        4. TextureCube: MipCount = 0~10  Width * Height = 4 * 4  6个面
            Example更新数据参数: MipLevel = 0, faceindex = 1 Data = {4*4}
     */
    void GRIGLDrive::GRIUpdateTexture2D(GRITexture2DRef& tex2D, uint32 mipLevel, Texture2DRegion region, uint32 pitch, const uint8* data)
    {
        GRIGLTexture2D* glTexture = dynamic_cast<GRIGLTexture2D*>(tex2D.GetReference());
        
        const Texture2DRegion uRegion    = region;
        const PixelFormatInfo formatInfo = GPixelFormats[tex2D->GetFormat()];
        const GLTextureFormat texFormat  = GGLTextureFormat[tex2D->GetFormat()];
        
        bool isCompressed          = texFormat._IsCompressed;
        GLenum glFormat            = texFormat._GLFormat;
        GLenum glType              = texFormat._GLType;
        GLenum glTarget            = glTexture->_Target;
        uint32 formatBpp           = formatInfo._ByteSize;
        //Row align
        glPixelStorei(GL_UNPACK_ROW_LENGTH, pitch / formatBpp);
        //pixel align
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if (isCompressed)
        {
            const int imageSize = (uRegion._Width / formatInfo._BlockSizeX) * (uRegion._Height / formatInfo._BlockSizeY) * formatInfo._ByteSize;
            glCompressedTexSubImage2D(glTarget, mipLevel, uRegion._DestX, uRegion._DestY, uRegion._Width, uRegion._Height, imageSize,glFormat, data);
        }
        else
        {
            glTexSubImage2D(glTarget, mipLevel, uRegion._DestX, uRegion._DestY, uRegion._Width, uRegion._Height, glFormat, glType, data);
        }
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    }
    //depthPitch 是当前miplevel级别图像的大小
    void GRIGLDrive::GRIUpdateTexture3D(GRITexture3DRef& tex3D, uint32 mipLevel, Texture3DRegion region, uint32 rowPitch, uint8 depthPitch, const uint8* data)
    {
        GRIGLTexture3D* glTex = dynamic_cast<GRIGLTexture3D*>(tex3D.GetReference());
        const Texture3DRegion uRegion = region;
        const PixelFormatInfo formatInfo = GPixelFormats[glTex->GetFormat()];
        const GLTextureFormat texFormat = GGLTextureFormat[glTex->GetFormat()];
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        const bool sRgb = OGLTexture::HasTextureUsageType(glTex->GetTextureUsageType(), TextureUsageType::TUT_sRGB);
        if (texFormat._IsCompressed)
        {
            OGLTexture::CompressedTexSubImage(
                glTex->_Target,
                mipLevel,
                uRegion._DestX, uRegion._DestY, uRegion._DestZ,
                uRegion._Width, uRegion._Height, uRegion._Depth,
                texFormat._GLInternalFormat[sRgb],
                depthPitch * uRegion._Depth,
                data
            );
        }
        else
        {
            glPixelStorei(GL_UNPACK_ROW_LENGTH, uRegion._Width / formatInfo._BlockSizeX);
            glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, uRegion._Height / formatInfo._BlockSizeY);

            OGLTexture::TexSubImage(
                glTex->_Target, 
                0,
                mipLevel, 
                uRegion._DestX, uRegion._DestY, uRegion._DestZ, 
                uRegion._Width, uRegion._Height, uRegion._Depth, 
                texFormat._GLFormat, 
                texFormat._GLType,
                data);
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    }

    void GRIGLDrive::GRIUpdateTexture2DArray(GRITexture2DArrayRef& tex2DArray, uint32 textureIndex, uint32 mipLevel, Texture2DRegion region, uint32 pitch, const uint8* data)
    {
        GRIGLTexture2DArray* glTex = dynamic_cast<GRIGLTexture2DArray*>(tex2DArray.GetReference());
        const Texture2DRegion uRegion = region;
        const PixelFormatInfo formatInfo = GPixelFormats[glTex->GetFormat()];
        const GLTextureFormat texFormat = GGLTextureFormat[glTex->GetFormat()];

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        const bool sRgb = OGLTexture::HasTextureUsageType(glTex->GetTextureUsageType(), TextureUsageType::TUT_sRGB);

        if (texFormat._IsCompressed)
        {
            const int imageSize = (uRegion._Width / formatInfo._BlockSizeX) * (uRegion._Height / formatInfo._BlockSizeY) * formatInfo._ByteSize;
            OGLTexture::CompressedTexSubImage(glTex->_Target,
                mipLevel,
                uRegion._DestX, uRegion._DestY, textureIndex,
                uRegion._Width, uRegion._Height, 1, 
                texFormat._GLInternalFormat[sRgb], 
                imageSize,
                data);
        }
        else
        {
            glPixelStorei(GL_UNPACK_ROW_LENGTH, pitch / formatInfo._ByteSize);
            // 更新 Miplevel = n 与特定层的纹理数据
            OGLTexture::TexSubImage(glTex->_Target,
                0,
                mipLevel,
                uRegion._DestX, uRegion._DestY, textureIndex,
                uRegion._Width,uRegion._Height,1,
                texFormat._GLFormat,
                texFormat._GLType,
                data);
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    }
    void GRIGLDrive::GRIUpdateTextureCube(GRITextureCubeRef& texCube, uint32 faceIndex, uint32 mipLevel, Texture2DRegion region, uint32 pitch, const uint8* data)
    {
        GRIGLTextureCube* glTex = dynamic_cast<GRIGLTextureCube*>(texCube.GetReference());
        const Texture2DRegion uRegion = region;
        const PixelFormatInfo formatInfo = GPixelFormats[glTex->GetFormat()];
        const GLTextureFormat texFormat = GGLTextureFormat[glTex->GetFormat()];

        GLenum intentTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        const bool sRgb = OGLTexture::HasTextureUsageType(glTex->GetTextureUsageType(), TextureUsageType::TUT_sRGB);
        if (texFormat._IsCompressed)
        {
            const int imageSize = (uRegion._Width / formatInfo._BlockSizeX) * (uRegion._Height / formatInfo._BlockSizeY) * formatInfo._ByteSize;
            OGLTexture::CompressedTexSubImage(intentTarget,
                mipLevel,
                uRegion._DestX, uRegion._DestY, 0,
                uRegion._Width, uRegion._Height, 1,
                texFormat._GLInternalFormat[sRgb],
                imageSize,
                data);
        }
        else
        {
            glPixelStorei(GL_UNPACK_ROW_LENGTH, pitch / formatInfo._ByteSize);
            // 更新 MipLevel = n 与特定层的纹理数据
            OGLTexture::TexSubImage(glTex->_Target,
                0,
                mipLevel,
                uRegion._DestX, uRegion._DestY, 0,
                uRegion._Width, uRegion._Height, 0,
                texFormat._GLFormat,
                texFormat._GLType,
                data);
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    }

    //Texture Internal call function
    namespace OGLTexture
    {
        template<typename TextureType>
        void CreateTextureInternal(TextureType* glTex,uint32 sizex,uint32 sizey,uint32 sizez,uint8 format,uint32 numMips,uint32 numSamples,TextureUsageType usageType,uint8* data)
        {          
            const PixelFormat pFormat        = (PixelFormat)format;
            const GLTextureFormat& gpFormat  = GGLTextureFormat[pFormat];
            const PixelFormatInfo formatInfo = GPixelFormats[glTex->GetFormat()];
            bool isSrgb                      = OGLTexture::HasTextureUsageType(usageType,TextureUsageType::TUT_sRGB);
            GLenum glFormat                  = gpFormat._GLFormat;
            GLenum glType                    = gpFormat._GLType;
            GLenum internalFotmat            = gpFormat._GLInternalFormat[isSrgb];
            //if numSimples not 1, so this mrt texture(Msaa)
            GLenum target                    = GL_NONE;
            GLenum attachment                = GL_NONE;
            EGRIResourceType resourceType = glTex->GetType();
            switch (resourceType)
            {
                case GRT_Texture2D:
                    target = numSamples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
                    break;
                case GRT_Texture2DArray:
                    target = GL_TEXTURE_2D_ARRAY;
                    numSamples = 1;
                    break;
                case GRT_Texture3D:
                    target = GL_TEXTURE_3D;
                    numSamples = 1;
                    break;
                case GRT_TextureCube:
                    target = GL_TEXTURE_CUBE_MAP;
                    numSamples = 1;
                    break;
                default:
                    SN_WARN("EGRIResourceType:%d not support.",resourceType);
                    break;
            }
            //numMip = 0 Indicates a complete mip structure
            //numMip = 1 mipmap is disabled
            //numMip > 1 Externally defined Mipmap chain.Externally, divide the widthand height by 2 for jumping data
            //mipmap Source Data is
            //MipmapData[Mipmap级别数] = {每个级别的压缩图像数据};
            //  4*4 cubemap  {4*4|4*4|4*4|4*4|4*4|4*4} {2*2|2*2|2*2|2*2|2*2|2*2} {1*1|1*1|1*1|1*1|1*1|1*1}
            //      target次序: px nx py ny pz nz
            //  4 * 4 * 3 Texture2D_Array {4*4|4*4|4*4} {2*2|2*2|2*2} {1*1|1*1|1*1}
            if (numMips == 0 && numSamples <= 1)
            {
                numMips = OGLTexture::CalMaxMipmapLevel(sizex, sizey);
            }
            else if (numMips == 0 && numSamples > 1)
            {
                numMips = 1;
            }
            //创建纹理对象
            GLuint texId;
            glGenTextures(1, &texId);
            glBindTexture(target, texId);
            
            if(numSamples > 1)
            {
                glTexImage2DMultisample(target, numSamples, internalFotmat, sizex, sizey, GL_TRUE);
            }
            else
            {
                //Texture Paramerer State
                glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                if (OGLTexture::IsPowerOftwo(sizex) || OGLTexture::IsPowerOftwo(sizey))
                {
                    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
                }
                else
                {
                    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                }
                //TODO: GL_TEXTURE_MAX_ANISOTROPY_EXT
                glTexParameteri(target, GL_TEXTURE_MIN_FILTER, numMips > 1 ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
                glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
                glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, numMips - 1);
                if (gpFormat._GLInternalFormat[isSrgb] == GL_NONE)
                {
                    SN_WARN("Texture format '%s' not supported.", formatInfo._Name);
                }
                if (gpFormat._IsBGRA && !OGLTexture::HasTextureUsageType(usageType, TextureUsageType::TUT_RenderTarget))
                {
                    glTexParameteri(target, GL_TEXTURE_SWIZZLE_R, GL_BLUE);
                    glTexParameteri(target, GL_TEXTURE_SWIZZLE_B, GL_RED);
                }
                //申请纹理内存
                if(!gpFormat._IsCompressed)
                {
                    if(!OGLTexture::TexStorageImage(target, numMips, internalFotmat, sizex, sizey, sizez, glFormat, glType))
                    {
                        const GLenum firstTarget = glTex->_IsCubemap ? GL_TEXTURE_CUBE_MAP_POSITIVE_X : target;
                        const uint32 numTargets = glTex->_IsCubemap ? 6 : 1;
                        bool isArray = target == GL_TEXTURE_2D_ARRAY;
                        for(uint32 mipIndex = 0; mipIndex < numMips; mipIndex++)
                        {
                            uint32 image_w = std::max<uint32>(1,(sizex >> mipIndex));
                            uint32 image_h = std::max<uint32>(1,(sizey >> mipIndex));
                            uint32 image_d = isArray ? sizez : std::max<uint32>(1,(sizez >> mipIndex));
                            for(uint32 targetIndex = 0; targetIndex < numTargets; targetIndex++)
                            {
                                OGLTexture::TexImage(target + firstTarget, 0, mipIndex, internalFotmat,image_w, image_h, image_d, 0, glFormat, glType, nullptr);
                            }
                        }
                    }
                }
                else
                {
                    uint32 dataOffset = 0;
                    const GLenum firstTarget = glTex->_IsCubemap ? GL_TEXTURE_CUBE_MAP_POSITIVE_X : target;
                    const uint32 numTargets = glTex->_IsCubemap ? 6 : 1;
                    bool isArray = target == GL_TEXTURE_2D_ARRAY;
                    for(int mipIndex = 0; mipIndex < numMips; mipIndex++)
                    {
                        uint32 image_w = std::max<uint32>(1, (sizex >> mipIndex));
                        uint32 image_h = std::max<uint32>(1, (sizey >> mipIndex));
                        uint32 image_d = isArray ? sizez : std::max<uint32>(1, (sizez >> mipIndex));
                        uint32 image_size = (image_w / formatInfo._BlockSizeX)* (image_h / formatInfo._BlockSizeY)* formatInfo._ByteSize;
                        image_size = image_size * image_d;
                        for(int targetIndex = 0; targetIndex < numTargets; targetIndex ++)
                        {
                            OGLTexture::CompressedTexImage(target,mipIndex,internalFotmat,image_w,image_h,image_d,image_d,image_size,nullptr);
                        }
                    }
                }
            }
            //加载纹理数据
            if(data)
            {
                uint32 dataOffset = 0;
                const GLenum firstTarget = glTex->_IsCubemap ? GL_TEXTURE_CUBE_MAP_POSITIVE_X : target;
                const uint32 numTargets = glTex->_IsCubemap ? 6 : 1;
                bool isArray = target == GL_TEXTURE_2D_ARRAY;
                for (int mipIndex = 0; mipIndex < numMips; mipIndex++)
                {
                    uint32 image_w = std::max<uint32>(1, (sizex >> mipIndex));
                    uint32 image_h = std::max<uint32>(1, (sizey >> mipIndex));
                    uint32 image_d = isArray ? sizez : std::max<uint32>(1, (sizez >> mipIndex));
                    uint32 image_size = (image_w / formatInfo._BlockSizeX) * (image_h / formatInfo._BlockSizeY) * formatInfo._ByteSize;
                    image_size = image_size * image_d;
                    
                    for(int targetIndex = 0; targetIndex < numTargets; targetIndex ++)
                    {
                        if(!gpFormat._IsCompressed)
                        {
                            OGLTexture::TexSubImage(firstTarget + targetIndex, 0, mipIndex, 0, 0, 0, image_w, image_h, image_d, glFormat, glType, data + dataOffset);
                        }
                        else
                        {
                            OGLTexture::CompressedTexSubImage(firstTarget + targetIndex, mipIndex, 0, 0, 0, image_w, image_h, image_d, glFormat, image_size, data + dataOffset);
                        }
                        dataOffset += image_size;
                    }
                }
            }
            //Depth/Sampler/DepthStencil/ShadowDepth
            if(OGLTexture::HasTextureUsageType(usageType,TextureUsageType::TUT_RenderTarget))
            {
                attachment = GL_COLOR_ATTACHMENT0;
            }
            else if(OGLTexture::HasTextureUsageType(usageType,TextureUsageType::TUT_DepthStencilRenderTarget))
            {
                attachment = (format == PF_DepthStencil) ? GL_DEPTH_STENCIL_ATTACHMENT : GL_DEPTH_ATTACHMENT;
            }
            else if(OGLTexture::HasTextureUsageType(usageType, TextureUsageType::TUT_ResolveRenderTarget))
            {
                if(format == PF_DepthStencil)
                {
                    attachment = GL_DEPTH_STENCIL_ATTACHMENT;
                }
                else if(format == PF_ShadowDepth || format == PF_D24)
                {
                    attachment = GL_DEPTH_ATTACHMENT;
                }
                else
                {
                    attachment = GL_COLOR_ATTACHMENT0;
                }
            }
            glBindTexture(target, 0);
            glTex->_GpuHandle  = texId;
            glTex->_Target     = target;
            glTex->_Attachment = attachment;
        }
        bool TexStorageImage(GLenum target,uint32 mipLevel,GLenum internalFormat,uint32 sizex,uint32 sizey,uint32 sizez,GLenum format,GLenum type)
        {
            if(target == GL_TEXTURE_2D_ARRAY || target == GL_TEXTURE_3D)
            {
                if(!OpenGL::TexStorage3D(target, mipLevel, internalFormat, sizex, sizey, sizez, format, type))
                {
                    return false;
                }
            }
            else
            {
                if(!OpenGL::TexStorage2D(target, mipLevel, internalFormat, sizex, sizey, format, type))
                {
                    return false;
                }
            }
        }
        void TexImage(GLenum target,uint32 numSamples,GLint mipLevel,GLint internalFormat,uint32 sizex, uint32 sizey,uint32 sizez,GLint border,GLenum format,GLenum type,const GLvoid* data)
        {
            //GL_PROXY_TEXTURE_3D 代理纹理，用于查询是否支持某种格式(较为鸡肋功能)
            if(target == GL_TEXTURE_3D || target == GL_TEXTURE_CUBE_MAP_ARRAY || target == GL_TEXTURE_2D_ARRAY)
            {
                //GL_TEXTURE_CUBE_MAP_ARRAY GLES3.2\GL4.x
                glTexImage3D(target,mipLevel,internalFormat,sizex,sizey,sizez,border,format,type,data);
            }
            else if (target == GL_TEXTURE_2D_MULTISAMPLE)//TODO: GL_TEXTURE_2D_MULTISAMPLE_ARRAY
            {
                glTexImage2DMultisample(target,numSamples,internalFormat,sizex,sizey,GL_TRUE);
            }
            else if(target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
            {
                //TODO:
            }
            else//target: GL_TEXTURE_2D、GL_TEXTURE_CUBE_MAP_XX_X.....
            {
                glTexImage2D(target,mipLevel,internalFormat,sizex,sizey,border,format,type,data);
            }
        }

        void TexSubImage(GLenum target,uint32 numSamples,GLint mipLevel,GLint offsetx,GLint offsety,GLint offsetz,uint32 sizex, uint32 sizey,uint32 sizez,GLenum format,GLenum type,const GLvoid* data)
        {
            if(data == nullptr)
            {
                SN_WARN("TextureData is Nullptr.");
                return;
            }
            if(target == GL_TEXTURE_3D || target == GL_TEXTURE_2D_ARRAY || target == GL_TEXTURE_CUBE_MAP_ARRAY)
            {
                glTexSubImage3D(target,mipLevel,offsetx,offsety,offsetz,sizex,sizey,sizez,format,type,data);
            }
            else if(target == GL_TEXTURE_2D_MULTISAMPLE)
            {
                glTexImage2DMultisample(target,numSamples,format,sizex,sizey,false);
            }
            else if(target == GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
            {
                //TODO: 如果有这方面的多重采样数组需求，可以去支持，目前看暂时没有什么场景需要这个能力
            }
            else//target: GL_TEXTURE_2D、GL_TEXTURE_CUBE_MAP_XX_X.....
            {
                glTexSubImage2D(target,mipLevel,offsetx,offsety,sizex,sizey,format,type,data);
            }
        }
        
        void CompressedTexImage(GLenum target,GLint mipLevel,GLenum internalFormat,uint32 sizex, uint32 sizey,uint32 sizez,GLint border,GLsizei imageSize,const GLvoid* data)
        {
            if(!OpenGL::SupportASTC())
            {
                SN_WARN("Not Support Compressed.");
                return;
            }
            if(target == GL_TEXTURE_3D || target == GL_TEXTURE_2D_ARRAY || target == GL_TEXTURE_CUBE_MAP_ARRAY)
            {
                //GL_TEXTURE_CUBE_MAP_ARRAY: GLES3.2(width != height  go wrong)
                glCompressedTexImage3D(target,mipLevel,internalFormat,sizex,sizey,sizez,border,imageSize,data);
            }
            else//target: GL_TEXTURE_2D,GL_TEXTURE_CUBE_MAP_XXX_X....
            {
                glCompressedTexImage2D(target,mipLevel,internalFormat,sizex,sizey,border,imageSize,data);
            }
        }
        
        void CompressedTexSubImage(GLenum target,GLint mipLevel,GLint offsetx,GLint offsety,GLint offsetz,uint32 sizex, uint32 sizey,uint32 sizez,GLenum format,GLsizei imageSize,const GLvoid* data)
        {
            if(!OpenGL::SupportASTC())
            {
                SN_WARN("Not Support Compressed.");
                return;
            }
            if(target == GL_TEXTURE_3D || target == GL_TEXTURE_2D_ARRAY || target == GL_TEXTURE_CUBE_MAP_ARRAY)
            {
                glCompressedTexSubImage3D(target,mipLevel,offsetx,offsety,offsetz,sizex,sizey,sizez,format,imageSize,data);
            }
            else//target: GL_TEXTURE_2D,GL_TEXTURE_CUBE_MAP_XXX_X....
            {
                glCompressedTexSubImage2D(target,mipLevel,offsetx,offsety,sizex,sizey,format,imageSize,data);
            }
        }
        
        bool HasTextureUsageType(TextureUsageType curr,TextureUsageType target)
        {
            return ((uint64)curr) & ((uint64)target);
        }
        
        void SetupTextureFormat(PixelFormat pFormat, const GLTextureFormat& glFormat)
		{
            GGLTextureFormat[pFormat] = glFormat;
            GPixelFormats[pFormat]._IsSupport = (glFormat._GLFormat != GL_NONE && (glFormat._GLInternalFormat[0] != GL_NONE || glFormat._GLInternalFormat[1] != GL_NONE));
		}
    
        void InitTextureFormat()
        {
            // Initial texture format
            for (int32 i = 0; i < PF_End; ++i)
            {
                SetupTextureFormat(PixelFormat(i), GLTextureFormat());
            }
            SetupTextureFormat(PF_None, GLTextureFormat());
            //                                  GLTexture Format: InternalFormat   InternalFormatSRGB       Format                  Type        bCompressed bBGRA
            SetupTextureFormat(PF_R8,                GLTextureFormat(GL_R8,             GL_R8,              GL_RED,             GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_R8_UINT,           GLTextureFormat(GL_R8UI,           GL_R8UI,            GL_RED_INTEGER,     GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PR_R8_SINT,           GLTextureFormat(GL_R8I,            GL_R8I,             GL_RED_INTEGER,     GL_BYTE,            false, false));
            SetupTextureFormat(PF_R16F,              GLTextureFormat(GL_R16F,           GL_R16F,            GL_RED,             GL_HALF_FLOAT,      false, false));
            SetupTextureFormat(PF_R16F_FILTER,       GLTextureFormat(GL_R16F,           GL_R16F,            GL_RED,             GL_HALF_FLOAT,      false, false));
            SetupTextureFormat(PF_R16_UINT,          GLTextureFormat(GL_R16UI,          GL_R16UI,           GL_RED_INTEGER,     GL_UNSIGNED_SHORT,  false, false));
            SetupTextureFormat(PF_R16_SINT,          GLTextureFormat(GL_R16I,           GL_R16I,            GL_RED_INTEGER,     GL_SHORT,           false, false));
            SetupTextureFormat(PF_R32F,              GLTextureFormat(GL_R32F,           GL_R32F,            GL_RED,             GL_FLOAT,           false, false));
            SetupTextureFormat(PF_R32_UINT,          GLTextureFormat(GL_R32UI,          GL_R32UI,           GL_RED_INTEGER,     GL_UNSIGNED_INT,    false, false));
            SetupTextureFormat(PF_R32_SINT,          GLTextureFormat(GL_R32I,           GL_R32I,            GL_RED_INTEGER,     GL_INT,             false, false));
            //SetupTextureFormat(PF_R64_UINT,        GLTextureFormat());
            SetupTextureFormat(PF_G8,                GLTextureFormat(GL_R8,             GL_R8,              GL_RED,             GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_G16,               GLTextureFormat(GL_R16,            GL_R16,             GL_RED,             GL_UNSIGNED_SHORT,  false, false));
            SetupTextureFormat(PF_A8,                GLTextureFormat(GL_R8,             GL_R8,              GL_RED,             GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_R8G8,              GLTextureFormat(GL_RG8,            GL_RG8,             GL_RG,              GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_R8G8_UINT,         GLTextureFormat(GL_RG8UI,          GL_RG8UI,           GL_RG_INTEGER,      GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_R16G16_UINT,       GLTextureFormat(GL_RG16UI,         GL_RG16UI,          GL_RG_INTEGER,      GL_UNSIGNED_SHORT,  false, false));
            SetupTextureFormat(PF_R32G32_UINT,       GLTextureFormat(GL_RG32UI,         GL_RG32UI,          GL_RG_INTEGER,      GL_UNSIGNED_INT,    false, false));
            SetupTextureFormat(PF_G16R16,            GLTextureFormat(GL_RG16,           GL_RG16,            GL_RG,              GL_UNSIGNED_SHORT,  false, false));
            SetupTextureFormat(PF_G16R16F,           GLTextureFormat(GL_RG16F,          GL_RG16F,           GL_RG,              GL_HALF_FLOAT,      false, false));
            SetupTextureFormat(PF_G16R16F_FILTER,    GLTextureFormat(GL_RG16F,          GL_RG16F,           GL_RG,              GL_HALF_FLOAT,      false, false));
            SetupTextureFormat(PF_G16R16_SNORM,      GLTextureFormat(GL_RG16_SNORM,     GL_RG16_SNORM,      GL_RG,              GL_SHORT,           false, false));
            SetupTextureFormat(PF_G32R32F,           GLTextureFormat(GL_RG32F,          GL_RG32F,           GL_RG,              GL_FLOAT,           false, false));
            SetupTextureFormat(PF_R5G6B5_UNORM,      GLTextureFormat(GL_RGB565,         GL_RGB565,          GL_RGB,             GL_UNSIGNED_SHORT_5_6_5, false, false));
            SetupTextureFormat(PF_R8G8B8,            GLTextureFormat(GL_RGB8,           GL_SRGB8,           GL_RGB,             GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_R8G8B8A8,          GLTextureFormat(GL_RGBA8,          GL_SRGB8_ALPHA8,    GL_RGBA,            GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_RGB_Float,         GLTextureFormat(GL_R11F_G11F_B10F, GL_R11F_G11F_B10F,  GL_RGB,             GL_UNSIGNED_INT_10F_11F_11F_REV, false, false));
            SetupTextureFormat(PF_R11G11B10_Float,   GLTextureFormat(GL_R11F_G11F_B10F, GL_R11F_G11F_B10F,  GL_RGB,             GL_UNSIGNED_INT_10F_11F_11F_REV, false, false));
            SetupTextureFormat(PF_R32G32B32_UINT,    GLTextureFormat(GL_RGB32UI,        GL_RGB32UI,         GL_RGB_INTEGER,     GL_UNSIGNED_INT,    false, false));
            SetupTextureFormat(PF_R32G32B32_SINT,    GLTextureFormat(GL_RGB32I,         GL_RGB32I,          GL_RGB_INTEGER,     GL_INT,             false, false));
            SetupTextureFormat(PF_R32G32B32F,        GLTextureFormat(GL_RGB32F,         GL_RGB32F,          GL_RGB,             GL_FLOAT,           false, false));
            SetupTextureFormat(PF_R8G8B8A8_UINT,     GLTextureFormat(GL_RGBA8UI,        GL_RGBA8UI,         GL_RGBA_INTEGER,    GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_R8G8B8A8_SNORM,    GLTextureFormat(GL_RGBA8,          GL_RGBA8,           GL_RGBA,            GL_UNSIGNED_BYTE,   false, false));
            SetupTextureFormat(PF_R16G16B16A16_UINT, GLTextureFormat(GL_RGBA16UI,       GL_RGBA16UI,        GL_RGBA_INTEGER,    GL_UNSIGNED_SHORT,  false, false));
            SetupTextureFormat(PF_R16G16B16A16_SINT, GLTextureFormat(GL_RGBA16I,        GL_RGBA16I,         GL_RGBA_INTEGER,    GL_SHORT,           false, false));
            SetupTextureFormat(PF_RGBA_Float,        GLTextureFormat(GL_RGBA16F,        GL_RGBA16F,         GL_RGBA,            GL_HALF_FLOAT,      false, false));
            //bool bNeedsToSwizzleRedBlue = GL5551Format != GL_UNSIGNED_SHORT_5_5_5_1;
            SetupTextureFormat(PF_B5G5R5A1_UNORM,    GLTextureFormat(GL_RGB5_A1,        GL_RGB5_A1,         GL_RGBA,            GL_UNSIGNED_SHORT_5_5_5_1, false, false));
            //SetupTextureFormat(PF_A8R8G8B8,        GLTextureFormat());
            SetupTextureFormat(PF_A16B16G16R16,      GLTextureFormat(GL_RGBA16F,        GL_RGBA16F,         GL_RGBA,            GL_HALF_FLOAT,      false, false));
            SetupTextureFormat(PF_A2B10G10R10,       GLTextureFormat(GL_RGB10_A2,       GL_RGB10_A2,        GL_RGBA,            GL_UNSIGNED_INT_2_10_10_10_REV, false, false));
            SetupTextureFormat(PF_A32B32G32R32F,     GLTextureFormat(GL_RGBA32F,        GL_RGBA32F,         GL_RGBA,            GL_FLOAT,           false, false));
    #if PLATFORM == PLATFORM_WINDOW || PLATFORM == PLATFORM_ANDROID || PLATFORM == PLATFORM_IOS
            SetupTextureFormat(PF_ASTC_4x4,         GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_4x4_KHR,    GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR,    GL_RGBA,    GL_UNSIGNED_BYTE, true, false));
            SetupTextureFormat(PF_ASTC_6x6,         GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_6x6_KHR,    GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR,    GL_RGBA,    GL_UNSIGNED_BYTE, true, false));
            SetupTextureFormat(PF_ASTC_8x8,         GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_8x8_KHR,    GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR,    GL_RGBA,    GL_UNSIGNED_BYTE, true, false));
            SetupTextureFormat(PF_ASTC_10x10,       GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_10x10_KHR,  GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR,  GL_RGBA,    GL_UNSIGNED_BYTE, true, false));
            SetupTextureFormat(PF_ASTC_12x12,       GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_12x12_KHR,  GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR,  GL_RGBA,    GL_UNSIGNED_BYTE, true, false));
            //SetupTextureFormat(PF_ETC1,            GLTextureFormat());
            SetupTextureFormat(PF_ETC2_RGB,         GLTextureFormat(GL_COMPRESSED_RGB8_ETC2,            GL_COMPRESSED_SRGB8_ETC2,                   GL_RGBA,    GL_UNSIGNED_BYTE, true, false));
            SetupTextureFormat(PF_ETC2_RGBA,        GLTextureFormat(GL_COMPRESSED_RGBA8_ETC2_EAC,       GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,        GL_RGBA,    GL_UNSIGNED_BYTE, true, false));
            SetupTextureFormat(PF_ETC2_R11_EAC,     GLTextureFormat(GL_COMPRESSED_R11_EAC,              GL_COMPRESSED_R11_EAC,                      GL_RED,     GL_UNSIGNED_BYTE, true, false));
            SetupTextureFormat(PF_ETC2_RG11_EAC,    GLTextureFormat(GL_COMPRESSED_RG11_EAC,             GL_COMPRESSED_RG11_EAC,                     GL_RG,      GL_UNSIGNED_BYTE, true, false));
    #endif
            SetupTextureFormat(PF_D24,              GLTextureFormat(GL_DEPTH_COMPONENT16,   GL_DEPTH_COMPONENT16,   GL_DEPTH_COMPONENT, GL_UNSIGNED_INT,        false, false));//todo
            SetupTextureFormat(PF_DepthStencil,     GLTextureFormat(GL_DEPTH24_STENCIL8,    GL_NONE,                GL_DEPTH_STENCIL,   GL_UNSIGNED_INT_24_8,   false, false));
            SetupTextureFormat(PF_ShadowDepth,      GLTextureFormat(GL_DEPTH_COMPONENT16,   GL_DEPTH_COMPONENT16,   GL_DEPTH_COMPONENT, GL_UNSIGNED_INT,        false, false));//todo
        }
    }
}
