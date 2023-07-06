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
#include "StbImageLoad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "LogAssert.h"
namespace SkySnow
{
    TextureStream* StbImageLoad::StbLoadPNG(const std::string& filePath)
    {
        int width, height, channels;
        unsigned char* image_data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
        if(image_data == nullptr)
        {
            SN_WARN("Load Image(ImagePath:%s) fail.\n",filePath.c_str());
            return nullptr;
        }
        PixelFormat pixelFormat = PF_None;
        switch (channels)
        {
            case STBI_rgb_alpha:
                pixelFormat = PF_R8G8B8A8;
                break;
            case STBI_rgb:
                pixelFormat = PF_R8G8B8;
                break;
            case STBI_grey_alpha:
                pixelFormat = PF_R8G8;
                break;
            case STBI_grey:
                pixelFormat = PF_R8;
                break;
            default:
                break;
        }
        
        TextureStream* stream = new TextureStream(pixelFormat,channels,width,height);
        stream->CopyTargetData(image_data);
        stbi_image_free(image_data);
    }
}
