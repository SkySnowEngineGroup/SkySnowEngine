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
#include "GRIGLDrive.h"
#include "GLTextureResource.h"
#include "GLTexture.h"
namespace SkySnow
{
    GLTextureFormat GOpenGLTextureFormats[PixelFormat::PF_End];
    void GRIGLDrive::GRICreateTexture2D(uint32 sizex, uint32 sizey, uint8 format, uint32 numMips, uint32 numSamples, TextureUsageType usageType, uint8* data,GRITexture2DRef& handle)
    {
        GRIGLTexture2D* tex2D = dynamic_cast<GRIGLTexture2D*>(handle.GetReference());
        PixelFormat pFormat = (PixelFormat)format;
        const GLTextureFormat& gpFormat = GOpenGLTextureFormats[pFormat];
        bool isSrgb = (uint64)usageType & (uint64)TextureUsageType::TUT_sRGB;
        GLenum target = GL_TEXTURE_2D;
        GLuint texId;
        glGenTextures(1, &texId);
        glBindTexture(target, texId);
        //不可变纹理
        glTexStorage2D(target, numMips,gpFormat._GLSizeInternalFormat[isSrgb], sizex, sizey);
        if (gpFormat._IsCompressed)
        {
            //TODO:Image Size
            //glCompressedTexSubImage2D(target,numMips, 0, 0, sizex, sizey, gpFormat._GLFormat, imageSize, data);
        }
        else
        {
            glTexSubImage2D(target, numMips, 0, 0, sizex, sizey, gpFormat._GLFormat, gpFormat._GLType, data);
        }
        
        glBindTexture(target, 0);
        
        tex2D->_GpuHandle = texId;
        tex2D->_Target    = target;
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
        
    }

    void GRIGLDrive::GRIUpdateTexture3D(GRITexture3D* tex3D, uint32 mipLevel, Texture2DRegion region, uint32 rowPitch, uint8 depthPitch, const uint8* data)
    {
        
    }

    void GRIGLDrive::GRIUpdateTextureCube(GRITextureCube* texCube)
    {
        
    }

    void GRIGLDrive::BindTextureForDraw(GLGraphicPipeline& contextState)
    {
        
    }
    //Texture Internal call function
    namespace OGLTexture
    {
        GRITexture* OGLTexture::CreateGLTextureInternal()
        {
            
        }

		void OGLTexture::SetupTextureFormat(PixelFormat pFormat, const GLTextureFormat& glFormat)
		{
			GOpenGLTextureFormats[pFormat] = glFormat;
		}
    }
}
