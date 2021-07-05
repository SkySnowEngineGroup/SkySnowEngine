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
#include "LogAssert.h"

namespace Nuwa
{
	static LogAssert* logInstance = nullptr;
	LogAssert::LogAssert()
	{
		logInstance = this;
#if PLATFORM == PLATFORM_WINDOW
		AllocConsole();
		m_WinHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif // PLATFORM == PLATFORM_WINDOW
	}

	LogAssert::~LogAssert()
	{
		logInstance = nullptr;
	}

	LogAssert* LogAssert::Instance()
	{
		static LogAssert instance;
		return &instance;
	}
	char* LogAssert::VspFun(const char* str, va_list args)
	{
		int index = sprintf(m_logBuffer, NUWA_LOG_TAG);
		vsnprintf(m_logBuffer + index, MAX_BUFFER_SIZE - index - 1, str, args);
		return m_logBuffer;
	}

	void LogAssert::LogProcessing(LogLevel level, const char* str, ...)
	{
		if (level < ELOG_TRACE || level >= ELOG_NONE)
			return;
		va_list args;
		va_start(args,str);
		char* buffer = VspFun(str, args);
		va_end(args);
		PrintLog(level,buffer);
		RecordLog(level, buffer);
	}
	void LogAssert::RecordLog(LogLevel level, char* str)
	{
		//Write the log to a file or upload it to the server
		//should be in the log thread
	}

	void LogAssert::PrintLog(LogLevel level, char* buffer)
	{
#if PLATFORM == PLATFORM_WINDOW
		switch (level)
		{
		case ELOG_INFO:
			SetConsoleTextAttribute(m_WinHandle, 2);
			break;
		case ELOG_WARNING:
			SetConsoleTextAttribute(m_WinHandle, 14);
			break;
		case ELOG_ERROR:
			SetConsoleTextAttribute(m_WinHandle, 12);
			break;
		default:
			SetConsoleTextAttribute(m_WinHandle, 7);
			break;
		}
		std::cout << buffer << std::endl;
#elif  PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_LINUX
		switch (level)
		{
		case ELOG_INFO:
			printf("Info:%s\n", buffer);
		case ELOG_WARNING:
			printf("Warning:%s\n", buffer);
		case ELOG_ERROR:
			printf("Error:%s\n", buffer);
			break;
		default:
			break;
		}
#elif PLATFORM == PLATFORM_ANDROID 
		switch (level)
		{
		case ELOG_INFO:
			__android_log_print(ANDROID_LOG_INFO, NUWA_LOG_TAG, "%s", buffer);
			break;
		case ELOG_WARNING:
			__android_log_print(ANDROID_LOG_WARN, NUWA_LOG_TAG, "%s", buffer);
			break;
		case ELOG_ERROR:
			__android_log_print(ANDROID_LOG_ERROR, NUWA_LOG_TAG, "%s", buffer);
			break;
		default:
			break;
		}
#endif // PLATFORM == PLATFORM_WINDOW
	}
}
