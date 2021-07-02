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

	void LogAssert::LogProcessing(LogLevel level, const char* str, ...)
	{
		if (level < LOG_TRACE || level >= LOG_NONE)
			return;
#if PLATFORM == PLATFORM_WINDOW
		switch (level)
		{
		case LOG_INFO:
			SetConsoleTextAttribute(m_WinHandle, 2);
			break;
		case LOG_WARNING:
			SetConsoleTextAttribute(m_WinHandle, 14);
			break;
		case LOG_ERROR:
			SetConsoleTextAttribute(m_WinHandle, 12);
			break;
		default:
			SetConsoleTextAttribute(m_WinHandle, 7);
			break;
		}
		std::cout << str << std::endl;
#elif  PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_IOS

#endif // PLATFORM == PLATFORM_WINDOW

	}
}