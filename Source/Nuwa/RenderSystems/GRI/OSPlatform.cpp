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

#include "OSPlatform.h"
#include "PlatformProfiles.h"
#include "WindowOSPlatform.h"
#include "AndroidOSPlatform.h"
#include "IOSOSPlatform.h"
#include "MacOSPlatform.h"
#include "LinuxOSPlatform.h"

namespace Nuwa
{
	static GRTCreate* griCreateInstance = nullptr;
	GRTCreate::GRTCreate()
		: m_GRI(nullptr)
		, m_OSPlatform(nullptr)
	{
		griCreateInstance = this;
	}

	GRTCreate::~GRTCreate()
	{
		if (nullptr != m_OSPlatform)
		{
			delete m_OSPlatform;
			m_OSPlatform = nullptr;
		}
		griCreateInstance = nullptr;
	}

	GRTCreate* GRTCreate::Instance()
	{
		static GRTCreate instance;
		return &instance;
	}

	RealTimeGRI* GRTCreate::GetRealTimeGRI()
	{
		if (nullptr != m_GRI)
		{
			return m_GRI;
		}
#if PLATFORM == PLATFORM_WINDOW
		m_OSPlatform = new WindowOSPlatform();
		m_GRI = m_OSPlatform->OSPlatformCreateRealTimeGRI();
#elif PLATFORM == PLATFORM_IOS
		m_OSPlatform = new IOSOSPlatform();
		m_GRI = m_OSPlatform->OSPlatformCreateRealTimeGRI();
#elif PLATFORM == PLATFORM_MAC
		m_OSPlatform = new MacOSPlatform();
		m_GRI = m_OSPlatform->OSPlatformCreateRealTimeGRI();
#elif PLATFORM == PLATFORM_ANDROID
		m_OSPlatform = new AndroidOSPlatform();
		m_GRI = m_OSPlatform->OSPlatformCreateRealTimeGRI();
#elif  PLATFORM == PLATFORM_LINUX
		m_OSPlatform = new LinuxOSPlatform();
		m_GRI = m_OSPlatform->OSPlatformCreateRealTimeGRI();
#endif
		return m_GRI;
	}
}