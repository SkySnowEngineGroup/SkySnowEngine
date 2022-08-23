//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by sunguoqiang(SunGQ1987),wangcan(crygl),
//							 liuqian(SkySnow),zhangshuangxue(Calence)
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
namespace SkySnow
{
	//声明全局变量，并用extern标记，即声明又定义，保证定义
	//只在该处进行定义初始化，别的地方定义初始化会报错
	//extern const std::string g_MediaPath = "D:/StudyEnginer/";//Home Path
	extern const std::string g_MediaPath = "D:/"; //Company Path
	extern const std::string g_RelativeMaterialPath = "SkySnowEngine/Script/Media/Material/";
	extern const int g_String_Buffer_MaxLength = 128;
	extern char g_Null_Char = 0;
	extern int g_Min_Capacity = 8;//最小8byte
	//globle Function
	std::string GetMaterialAllPath(const std::string mpath)
	{
		return g_MediaPath + g_RelativeMaterialPath + mpath;
	}

#define Delete_Object(object) \
		if(object) \
		{ \
			delete object; \
			object = nullptr; \
		}
}