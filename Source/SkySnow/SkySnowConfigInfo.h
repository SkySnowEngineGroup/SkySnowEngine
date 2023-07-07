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
#include <string>
#include "ResourcePathConfig.h"
namespace SkySnow
{
    //Globle config for engine
	static const std::string g_RelativeMaterialPath = std::string(Resource_Path) + "/Media/";
	static const int g_String_Buffer_MaxLength = 128;
	static char g_Null_Char = 0;
	static const int g_Min_Capacity = 8;//min cap is 8byte
	static const unsigned NPOS = 0xffffffff;
    static const uint64_t g_DefaultCullingMask = 1ULL << 63;
    typedef int SkySnowSceneHandle;
	//globle Function
	static std::string GetMaterialAllPath(const std::string mpath)
	{
		return g_RelativeMaterialPath + "Material/" + mpath;
	}
    static std::string GetImageAllPath(const std::string ipath)
    {
        return g_RelativeMaterialPath + "Texture/" + ipath;
    }
#define Delete_Object(object) \
		if(object) \
		{ \
			delete object; \
			object = nullptr; \
		}
}
