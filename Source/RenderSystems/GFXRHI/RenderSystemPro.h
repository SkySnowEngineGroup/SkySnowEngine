//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
// Open source is written by wangcan(crygl)¡¢liuqian(SkySnow)¡¢zhangshuangxue(Calence)
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
namespace Nuwa
{
#define PLATFORM_UNKNOW 0
#define PLATFORM_ANDROID 1
#define PLATFORM_IOS 2
#define PLATFORM_WINDOW 3
#define PLATFORM_MAC 4
#define PLATFORM_LINUX 5

#define PLATFORM PLATFORM_UNKNOW
//Æ½Ì¨ÅÐ¶Ï
#if defined(__ANDROID__) || defined(ANDROID)
#	undef  PLATFORM
#	define PLATFORM PLATFORM_ANDROID
#elif defined(__APPLE__)
#	undef  PLATFORM
#	if defined(__arm__) || (TARGET_IPHONE_SIMULATOR)
#		define PLATFORM PLATFORM_IOS
#	else 
#		define PLATFORM PLATFORM_MAC
#	endif
#elif defined(LINUX) || defined(__LINUX) || defined(__LINUX__) || defined(linux) || defined(__unix__)
#	undef  PLATFORM
#	define PLATFORM PLATFORM_LINUX
#elif defined(_WIN32)||defined(__WIN32__)
#	undef  PLATFORM
#	define PLATFORM PLATFORM_WINDOW
#endif

}