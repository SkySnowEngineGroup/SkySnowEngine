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
    //Texture2D/Texture2DArray
    //Texture3D
    //TextureCube
    //UnPackBuffer
    //Sampler:2D/2DArray/3D/Cube
    //Texture Stage(引擎只支持不可变纹理)
    namespace OGLTexture
    {
        GRITexture* CreateGLTextureInternal();
		void InitTextureFormat()
		{
            // Initial texture format
			for (int32 PF = 0; PF < PF_MAX; ++PF)
			{
				SetupTextureFormat(PixelFormat(PF), GLTextureFormat());
			}
			SetupTextureFormat(PF_None, GLTextureFormat());
			//GLTexture Format: InternalFormat InternalFormatSRGB Format Type bCompressed bBGRA
			SetupTextureFormat(PF_R8,			GLTextureFormat(GL_R8,					GL_R8,				GL_RED,				GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PF_R8_UINT,		GLTextureFormat(GL_R8UI,				GL_R8UI,			GL_RED_INTEGER,		GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PR_R8_SINT,		GLTextureFormat(GL_R8I,					GL_R8I,				GL_RED_INTEGER,		GL_BYTE,			false, false));
			SetupTextureFormat(PF_R16F,			GLTextureFormat(GL_R16F,				GL_R16F,			GL_RED,				GL_HALF_FLOAT,		false, false));
			SetupTextureFormat(PF_R16F_FILTER,	GLTextureFormat(GL_R16F,				GL_R16F,			GL_RED,				GL_HALF_FLOAT,		false, false));
			SetupTextureFormat(PF_R16_UINT,		GLTextureFormat(GL_R16UI,				GL_R16UI,			GL_RED_INTEGER,		GL_UNSIGNED_SHORT,	false, false));
			SetupTextureFormat(PF_R16_SINT,		GLTextureFormat(GL_R16I,				GL_R16I,			GL_RED_INTEGER,		GL_SHORT,			false, false));
			SetupTextureFormat(PF_R32F,			GLTextureFormat(GL_R32F,				GL_R32F,			GL_RED,				GL_FLOAT,			false, false));
			SetupTextureFormat(PF_R32_UINT,		GLTextureFormat(GL_R32UI,				GL_R32UI,			GL_RED_INTEGER,		GL_UNSIGNED_INT,	false, false));
			SetupTextureFormat(PF_R32_SINT,		GLTextureFormat(GL_R32I,				GL_R32I,			GL_RED_INTEGER,		GL_INT,				false, false));
			//SetupTextureFormat(PF_R64_UINT,		GLTextureFormat());
			SetupTextureFormat(PF_G8,			GLTextureFormat(GL_R8,					GL_R8,				GL_RED,				GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PF_G16,			GLTextureFormat(GL_R16,					GL_R16,				GL_RED,				GL_UNSIGNED_SHORT,	false, false));
			SetupTextureFormat(PF_A8,			GLTextureFormat(GL_R8,					GL_R8,				GL_RED,				GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PF_R8G8,			GLTextureFormat(GL_RG8,					GL_RG8,				GL_RG,				GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PF_R8G8_UINT,	GLTextureFormat(GL_RG8UI,				GL_RG8UI,			GL_RG_INTEGER,		GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PF_R16G16_UINT,	GLTextureFormat(GL_RG16UI,				GL_RG16UI,			GL_RG_INTEGER,		GL_UNSIGNED_SHORT,	false, false));
			SetupTextureFormat(PF_R32G32_UINT,	GLTextureFormat(GL_RG32UI,				GL_RG32UI,			GL_RG_INTEGER,		GL_UNSIGNED_INT,	false, false));
			SetupTextureFormat(PF_G16R16,		GLTextureFormat(GL_RG16,				GL_RG16,			GL_RG,				GL_UNSIGNED_SHORT,	false, false));
			SetupTextureFormat(PF_G16R16F,		GLTextureFormat(GL_RG16F,				GL_RG16F,			GL_RG,				GL_HALF_FLOAT,		false, false));
			SetupTextureFormat(PF_G16R16F_FILTER,GLTextureFormat(GL_RG16F,				GL_RG16F,			GL_RG,				GL_HALF_FLOAT,		false, false));
			SetupTextureFormat(PF_G16R16_SNORM, GLTextureFormat(GL_RG16_SNORM,			GL_RG16_SNORM,		GL_RG,				GL_SHORT,			false, false));
			SetupTextureFormat(PF_G32R32F,		GLTextureFormat(GL_RG32F,				GL_RG32F,			GL_RG,				GL_FLOAT,			false, false));
			SetupTextureFormat(PF_R5G6B5_UNORM, GLTextureFormat(GL_RGB565,				GL_RGB565,			GL_RGB,				GL_UNSIGNED_SHORT_5_6_5, false, false));
			SetupTextureFormat(PF_R8G8B8A8,		GLTextureFormat(GL_RGBA8,				GL_SRGB8_ALPHA8,	GL_RGBA,			GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PF_RGB_Float,	GLTextureFormat(GL_R11F_G11F_B10F,		GL_R11F_G11F_B10F,	GL_RGB,				GL_UNSIGNED_INT_10F_11F_11F_REV, false, false));
			SetupTextureFormat(PF_R11G11B10_Float,GLTextureFormat(GL_R11F_G11F_B10F,	GL_R11F_G11F_B10F,	GL_RGB,				GL_UNSIGNED_INT_10F_11F_11F_REV, false, false));
			SetupTextureFormat(PF_R32G32B32_UINT,GLTextureFormat(GL_RGB32UI,			GL_RGB32UI,			GL_RGB_INTEGER,		GL_UNSIGNED_INT,	false, false));
			SetupTextureFormat(PF_R32G32B32_SINT,GLTextureFormat(GL_RGB32I,				GL_RGB32I,			GL_RGB_INTEGER,		GL_INT,				false, false));
			SetupTextureFormat(PF_R32G32B32F,	GLTextureFormat(GL_RGB32F,				GL_RGB32F,			GL_RGB,				GL_FLOAT,			false, false));
			SetupTextureFormat(PF_R8G8B8A8_UINT,GLTextureFormat(GL_RGBA8UI,				GL_RGBA8UI,			GL_RGBA_INTEGER,	GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PF_R8G8B8A8_SNORM,GLTextureFormat(GL_RGBA8,				GL_RGBA8,			GL_RGBA,			GL_UNSIGNED_BYTE,	false, false));
			SetupTextureFormat(PF_R16G16B16A16_UINT,GLTextureFormat(GL_RGBA16UI,		GL_RGBA16UI,		GL_RGBA_INTEGER,	GL_UNSIGNED_SHORT,	false, false));
			SetupTextureFormat(PF_R16G16B16A16_SINT,GLTextureFormat(GL_RGBA16I,			GL_RGBA16I,			GL_RGBA_INTEGER,	GL_SHORT,			false, false));
			SetupTextureFormat(PF_RGBA_Float,	GLTextureFormat(GL_RGBA16F,				GL_RGBA16F,			GL_RGBA,			GL_HALF_FLOAT,		false, false));
			//bool bNeedsToSwizzleRedBlue = GL5551Format != GL_UNSIGNED_SHORT_5_5_5_1;
			SetupTextureFormat(PF_B5G5R5A1_UNORM,GLTextureFormat(GL_RGB5_A1,			GL_RGB5_A1,			GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, false, false));
			//SetupTextureFormat(PF_A8R8G8B8,		GLTextureFormat());
			SetupTextureFormat(PF_A16B16G16R16, GLTextureFormat(GL_RGBA16F,				GL_RGBA16F,			GL_RGBA, GL_HALF_FLOAT, false, false));
			SetupTextureFormat(PF_A2B10G10R10,	GLTextureFormat(GL_RGB10_A2,			GL_RGB10_A2,		GL_RGBA, GL_UNSIGNED_INT_2_10_10_10_REV, false, false));
			SetupTextureFormat(PF_A32B32G32R32F,GLTextureFormat(GL_RGBA32F,				GL_RGBA32F,			GL_RGBA, GL_FLOAT, false, false));
			SetupTextureFormat(PF_ASTC_4x4,		GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_4x4_KHR,	GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR,	GL_RGBA,			GL_UNSIGNED_BYTE, true, false));
			SetupTextureFormat(PF_ASTC_6x6,		GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_6x6_KHR,	GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR,	GL_RGBA,			GL_UNSIGNED_BYTE, true, false));
			SetupTextureFormat(PF_ASTC_8x8,		GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_8x8_KHR,	GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR,	GL_RGBA,			GL_UNSIGNED_BYTE, true, false));
			SetupTextureFormat(PF_ASTC_10x10,	GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_10x10_KHR,	GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR,	GL_RGBA,			GL_UNSIGNED_BYTE, true, false));
			SetupTextureFormat(PF_ASTC_12x12,	GLTextureFormat(GL_COMPRESSED_RGBA_ASTC_12x12_KHR,	GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR,	GL_RGBA,			GL_UNSIGNED_BYTE, true, false));
			//SetupTextureFormat(PF_ETC1,			GLTextureFormat());
			SetupTextureFormat(PF_ETC2_RGB,		GLTextureFormat(GL_COMPRESSED_RGB8_ETC2,			GL_COMPRESSED_SRGB8_ETC2,					GL_RGBA,			GL_UNSIGNED_BYTE, true, false));
			SetupTextureFormat(PF_ETC2_RGBA,	GLTextureFormat(GL_COMPRESSED_RGBA8_ETC2_EAC,		GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,		GL_RGBA,			GL_UNSIGNED_BYTE, true, false));
			SetupTextureFormat(PF_ETC2_R11_EAC, GLTextureFormat(GL_COMPRESSED_R11_EAC,				GL_COMPRESSED_R11_EAC,						GL_RED,				GL_UNSIGNED_BYTE, true, false));
			SetupTextureFormat(PF_ETC2_RG11_EAC,GLTextureFormat(GL_COMPRESSED_RG11_EAC,				GL_COMPRESSED_RG11_EAC,						GL_RG,				GL_UNSIGNED_BYTE, true, false));
			SetupTextureFormat(PF_D24,			GLTextureFormat(GL_DEPTH_COMPONENT16,				GL_DEPTH_COMPONENT16,						GL_DEPTH_COMPONENT, GL_UNSIGNED_INT,  false, false));//todo
			SetupTextureFormat(PF_DepthStencil, GLTextureFormat(GL_DEPTH24_STENCIL8,				GL_NONE,									GL_DEPTH_STENCIL,	GL_UNSIGNED_INT_24_8, false, false));
			SetupTextureFormat(PF_ShadowDepth,	GLTextureFormat(GL_DEPTH_COMPONENT16,				GL_DEPTH_COMPONENT16,						GL_DEPTH_COMPONENT, GL_UNSIGNED_INT,  false, false));//todo
		}

        inline void SetupTextureFormat(PixelFormat pFormat,const GLTextureFormat& glFormat)
        {
            GOpenGLTextureFormats[pFormat] = glFormat;
        }
    }


}
