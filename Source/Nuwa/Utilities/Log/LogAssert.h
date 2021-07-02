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
#include "NonCopyable.h"
#include "PlatformProfiles.h"
namespace Nuwa
{
	enum LogLevel
	{
		LOG_TRACE = 0,
		LOG_DEBUG,
		LOG_INFO,
		LOG_WARNING,
		LOG_ERROR,
		LOG_NONE
	};
	class LogAssert:public NonCopyable
	{
	private:
		LogAssert();
		~LogAssert();
	public:
		static LogAssert* Instance();
		void LogProcessing(LogLevel level,const char* str, ...);
	private:
		static LogAssert* logInstance;
#if PLATFORM == PLATFORM_WINDOW
		HANDLE			m_WinHandle;
#endif
	};

#define NUWALOG(x, ...)		if(Nuwa::LogAssert::Instance())Nuwa::logAssert::Instance->LogProcessing(Nuwa::LOG_INFO,x, ##__VA_ARGS__)
#define NUWAWARNING(x, ...) if(Nuwa::LogAssert::Instance())Nuwa::logAssert::Instance->LogProcessing(Nuwa::LOG_WARNING,x, ##__VA_ARGS__)
#define NUWAERROR(x, ...)	if(Nuwa::LogAssert::Instance())Nuwa::logAssert::Instance->LogProcessing(Nuwa::LOG_ERROR,x, ##__VA_ARGS__)
}
