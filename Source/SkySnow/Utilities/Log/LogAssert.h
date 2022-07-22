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
#include "NonCopyable.h"
#include "PlatformProfiles.h"
namespace SkySnow
{
	enum LogLevel
	{
		ELOG_TRACE = 0,
		ELOG_DEBUG,
		ELOG_INFO,
		ELOG_WARNING,
		ELOG_ERROR,
		ELOG_NONE
	};

	class LogAssert:public NonCopyable
	{
	private:
		LogAssert();
		~LogAssert();
		
		char* VspFun(const char* str, va_list args);
		void PrintLog(LogLevel level,char* str);
		void RecordLog(LogLevel level, char* str);
	public:
		static LogAssert* Instance();
		void LogProcessing(LogLevel level,const char* str, ...);
	private:
		char m_logBuffer[MAX_BUFFER_SIZE];
#if PLATFORM == PLATFORM_WINDOW
		HANDLE			m_WinHandle;
#endif
	};
}
#define SN_LOG(x, ...)	if(SkySnow::LogAssert::Instance()&&DEBUG)SkySnow::LogAssert::Instance()->LogProcessing(SkySnow::ELOG_INFO,x, ##__VA_ARGS__)
#define SN_WARN(x, ...) if(SkySnow::LogAssert::Instance()&&DEBUG)SkySnow::LogAssert::Instance()->LogProcessing(SkySnow::ELOG_WARNING,x, ##__VA_ARGS__)
#define SN_ERR(x, ...)	if(SkySnow::LogAssert::Instance())SkySnow::LogAssert::Instance()->LogProcessing(SkySnow::ELOG_ERROR,x, ##__VA_ARGS__)
