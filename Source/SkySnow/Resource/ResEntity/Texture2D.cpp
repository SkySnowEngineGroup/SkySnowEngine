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
#include "TextureSource.h"

namespace SkySnow
{
    Texture2D::Texture2D()
    {
        CreateTextureMeta();
    }
    Texture2D::~Texture2D()
    {
    }

    void Texture2D::SetTextureStream(const SPtr<TextureStream>& stream)
    {
        Sou()->SetTextureStream(stream);
    }
    void Texture2D::SetTextureName(const std::string texName)
    {
        _Tex2DMetaData->SetTextureName(texName);
    }
    const std::string& Texture2D::GetTextureName() const
    {
        return _Tex2DMetaData->GetTextureName();
    }
    void Texture2D::CreateTextureMeta()
    {
        if(!_Tex2DMetaData)
        {
            _Tex2DMetaData = CreateSPtr<Texture2DMetaData>();
        }
    }
}
