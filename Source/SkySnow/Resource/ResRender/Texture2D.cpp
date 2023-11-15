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
#include "Texture2D.h"
#include "GRI.h"
namespace SkySnow
{
    Texture2D::Texture2D()
        : IResRender(GRT_Texture2D)
    {
        
    }

    Texture2D::~Texture2D()
    {
        
    }

    void Texture2D::SetTextureStream(TextureStream* stream)
    {
        _TextureStream = stream;
        ResourceData texRD;
        texRD.MakeCopy(_TextureStream->GetImageData(), _TextureStream->GetImageSize());
        uint64 tut = (uint64)TextureUsageType::TUT_ShaderResource | (uint64)TextureUsageType::TUT_None;
        _GRITexture2D = CreateTexture2D(_TextureStream->GetImageWidth(),
                                         _TextureStream->GetImageHeight(),
                                         _TextureStream->GetPixelFormat(),
                                         1, 1,
                                         (TextureUsageType)tut,
                                         texRD);
    }
}
