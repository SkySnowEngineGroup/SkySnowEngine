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
#include "TextureStream.h"
#include "SkySnowConfigInfo.h"
namespace SkySnow
{
    TextureStream::TextureStream(PixelFormat inPixelFormat,uint32 inNumChannel,uint32 inWidth,uint32 inHeight)
        : _PixelFormat(inPixelFormat)
        , _NumChannel(inNumChannel)
        , _Width(inWidth)
        , _Height(inHeight)
    {
    }
    TextureStream::~TextureStream()
    {
        _PixelFormat = PF_None;
        _NumChannel = 0;
        _NumChannel = 0;
        _Width = 1;
        _Height = 1;
        if(_ImageRawData)
        {
            free(_ImageRawData);
        }
    }

    void TextureStream::WriteTargetData(void* targetData)
    {
        uint32 iSize = GetImageSize();
        _ImageRawData = (char*)malloc(iSize);
        if (_ImageRawData == nullptr)
        {
            SN_ERR("Malloc fail.");
        }
        memcpy(_ImageRawData, targetData, iSize);
    }

    void* TextureStream::GetImageData()
    {
        return _ImageRawData;
    }

    uint32 TextureStream::GetImageSize()
    {
        if(_ImageSize)
        {
            return _ImageSize;
        }
        PixelFormatInfo pfInfo = GPixelFormats[_PixelFormat];
        if (GPixelFormats[_PixelFormat]._IsCompressed)
        {
            _ImageSize = (_Width / pfInfo._BlockSizeX)* (_Height / pfInfo._BlockSizeY) * pfInfo._ByteSize;
        }
        else
        {
            _ImageSize = _Width * _Height * pfInfo._ByteSize;
        }
        return _ImageSize;
    }

    PixelFormat TextureStream::GetPixelFormat() const
    {
        return _PixelFormat;
    }

    uint32 TextureStream::GetImageChannels() const
    {
        return _NumChannel;
    }
    
    uint32 TextureStream::GetImageWidth() const
    {
        return _Width;
    }

    uint32 TextureStream::GetImageHeight() const
    {
        return _Height;
    }
}
