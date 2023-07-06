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
#include "NonCopyable.h"
#include "GRICommons.h"
#include "GRIResourceCreateInfo.h"
namespace SkySnow
{
    class TextureStream : public NonCopyable
    {
    public:
        TextureStream() = delete;
        TextureStream(PixelFormat inPixelFormat,uint32 inNumChannel,uint32 inWidth,uint32 inHeight);
        ~TextureStream();
        
        void CopyTargetData(void* targetData);
        
        void* GetImageData();
        
        uint32 GetImageSize();
        
        PixelFormat GetPixelFormat() const;
        
        uint32 GetImageChannels() const;
        
        uint32 GetImageWidth() const;
        
        uint32 GetImageHeight() const;
    private:
        PixelFormat _PixelFormat    = PF_None;
        char*       _ImageRawData   = nullptr;
        uint32      _NumChannel     = 0;
        uint32      _Width          = 1;
        uint32      _Height         = 1;
        uint32      _ImageSize      = 0;
    };
}
