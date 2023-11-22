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
#include "ResourcePathConfig.h"
#include <iostream>
#include <cfloat>
#include "VarType.h"

#define PLATFORM_UNKNOW 0
#define PLATFORM_ANDROID 1
#define PLATFORM_IOS 2
#define PLATFORM_WINDOW 3
#define PLATFORM_MAC 4
#define PLATFORM_LINUX 5

#define DEBUG 1
#define Log_Lock 1
//#define Use_Smart_Ptr 1 //Use custom smart Pointers

#define DEFAUT_WADTH 800
#define DEFAUT_HEIGHT 600
#define SkySnow_LOG_TAG "SkySnow:"
#define SkySnow_Name "SkySnowEngine"
#define MAX_BUFFER_SIZE 1024*4
#define PLATFORM PLATFORM_UNKNOW

//config various platforms
#if defined(__ANDROID__) || defined(ANDROID)
#	undef  PLATFORM
#	define PLATFORM PLATFORM_ANDROID
#	include <android/log.h>
#	include <trace_log.h>
#elif defined(__APPLE__)
#	undef  PLATFORM
#	if defined(__arm__) || (TARGET_IPHONE_SIMULATOR)
#		define PLATFORM PLATFORM_IOS
#	else 
#		define PLATFORM PLATFORM_MAC
#	endif
#	include <syslog.h>
#	include <sys/fcntl.h>
#	include <unistd.h>
#elif defined(LINUX) || defined(__LINUX) || defined(__LINUX__) || defined(linux) || defined(__unix__)
#	undef  PLATFORM
#	define PLATFORM PLATFORM_LINUX
#	include <syslog.h>
#	include <sys/fcntl.h>
#	include <unistd.h>
#elif defined(_WIN32)||defined(__WIN32__)
#	undef  PLATFORM
#	define PLATFORM PLATFORM_WINDOW
#	include <windows.h>
#	include <fcntl.h>
#	include <io.h>
#endif

//RenderDevice Config
#define GRI_UNKNOW 0
#define GRI_GL 1
#define GRI_VULKAN 2
#define GRI_METAL 3

//setup render device type: opengl or metal or vulkan
#define GRI_PLATFORM GRI_GL

#if GRI_PLATFORM == GRI_GL
#	include "GLProfiles.h"
#endif // GRI_PLATFORM == GRI_GL

//Shader是否debug的标记
#if DEBUG
#    undef Debug_Shader
#    define Debug_Shader 1
#endif // DEBUG

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
