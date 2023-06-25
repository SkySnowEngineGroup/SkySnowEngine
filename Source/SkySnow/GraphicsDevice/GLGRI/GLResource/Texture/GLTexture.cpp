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
        GRIGLTexture2D* tex2D = dynamic_cast<GRIGLTexture2D*>(handle.GetReference());
        
        const PixelFormat pFormat        = (PixelFormat)format;
        const GLTextureFormat& gpFormat  = GGLTextureFormat[pFormat];
        const PixelFormatInfo formatInfo = GPixelFormats[tex2D->GetFormat()];
        
        bool isSrgb                      = OGLTexture::HasTextureUsageType(usageType,TextureUsageType::TUT_sRGB);
        GLenum glFormat                  = gpFormat._GLFormat;
        GLenum glType                    = gpFormat._GLType;
        GLenum internalFotmat            = gpFormat._GLInternalFormat[isSrgb];
        //if numSimples not 1, so this mrt texture(Msaa)
        GLenum target                    = numSamples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
        GLenum attachment                = GL_NONE;
		//numMip = 0 Indicates a complete mip structure
		//numMip = 1 mipmap is disabled
		//numMip > 1 Externally defined Mipmap chain.Externally, divide the widthand height by 2 for jumping data
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

        if(numSamples > 1)//
        {
            glTexImage2DMultisample(target, numSamples, internalFotmat, sizex, sizey, GL_TRUE);
        }
        else//
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

            //分配纹理内存
            if(OpenGL::SupportStorageTexture() && !gpFormat._IsCompressed)
            {
                glTexStorage2D(target, numMips,internalFotmat, sizex, sizey);
            }
            else
            {
                for(int mipIndex = 0; mipIndex < numMips; mipIndex ++)
                {
                    if(!gpFormat._IsCompressed)
                    {
                        glTexImage2D(
                                     target,
                                     mipIndex,
                                     internalFotmat,
                                     std::max<uint32>(1,sizex >> mipIndex),
                                     std::max<uint32>(1,sizey >> mipIndex),
                                     0,
                                     glFormat,
                                     glType,
                                     nullptr);
                    }
                    else
                    {
                        uint32 image_w = std::max<uint32>(1,sizex >> mipIndex);
                        uint32 image_h = std::max<uint32>(1,sizey >> mipIndex);
                        const int imageSize = (image_w/formatInfo._BlockSizeX) * (image_h/formatInfo._BlockSizeY) * formatInfo._ByteSize;
                        glCompressedTexImage2D(
                                               target,
                                               mipIndex,
                                               internalFotmat,
                                               image_w,
                                               image_h,
                                               0,
                                               imageSize,
                                               nullptr);
                    }
                }
            }
            //更新纹理数据到纹理对象
            if(data != nullptr)
            {
                const uint8* curData  = data;
                GLenum internalFotmat = gpFormat._GLInternalFormat[isSrgb];
                for(int mipIndex = 0; mipIndex < numMips; mipIndex ++)
                {
                    const int image_w = std::max<uint32>(1,sizex >> mipIndex);
                    const int image_h = std::max<uint32>(1,sizey >> mipIndex);
                    const int imageSize = (image_w/formatInfo._BlockSizeX) * (image_h/formatInfo._BlockSizeY) * formatInfo._ByteSize;
                    if(gpFormat._IsCompressed && OpenGL::SupportASTC())
                    {
                        glCompressedTexSubImage2D(target, mipIndex, 0, 0, image_w, image_h, glFormat, imageSize, curData);
                    }
                    else if(!gpFormat._IsCompressed)
                    {
                        glTexSubImage2D(target, mipIndex,0, 0, image_w, image_h, glFormat, glType, curData);
                    }
                    curData     += imageSize;
                }
            }
        }
        
        //TODO: depthstencil and resovle(MRT to normal rt)
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
        tex2D->_GpuHandle   = texId;
        tex2D->_Target      = target;
        tex2D->_Attachment  = attachment;
    }
    
    void GRIGLDrive::GRICreateTexture2DArray(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips, uint32 numSamples, TextureUsageType usageType,uint8* data,GRITexture2DArrayRef& handle)
    {
        
    }
    void GRIGLDrive::GRICreateTexture3D(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips,uint8* data,GRITexture3DRef& handle)
    {
        
    }
    void GRIGLDrive::GRICreateTextureCube(uint32 size, uint8 format, uint32 numMips, TextureUsageType usageType,uint8* data,GRITextureCubeRef& handle)
    {
        
    }

    void GRIGLDrive::GRIUpdateTexture2D(GRITexture2D* tex2D, uint32 mipLevel, Texture2DRegion region, uint32 pitch, const uint8* data)
    {
        GRIGLTexture2D* glTexture = dynamic_cast<GRIGLTexture2D*>(tex2D);
        
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

    void GRIGLDrive::GRIUpdateTexture3D(GRITexture3D* tex3D, uint32 mipLevel, Texture2DRegion region, uint32 rowPitch, uint8 depthPitch, const uint8* data)
    {
        
    }

    void GRIGLDrive::GRIUpdateTextureCube(GRITextureCube* texCube)
    {
        
    }

    //Texture Internal call function
    namespace OGLTexture
    {
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
