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

#include "WindowOSPlatform.h"
#include "GLTypeGRI.h"
namespace SkySnow
{
	WindowOSPlatform::WindowOSPlatform()
		: m_TypeGRI(nullptr)
		, m_RealTimeGRI(nullptr)
		, m_Commands(nullptr)
	{

	}

	WindowOSPlatform::~WindowOSPlatform()
	{
		if (nullptr != m_TypeGRI)
		{
			delete m_TypeGRI;
			m_TypeGRI = nullptr;
		}
		if (m_RealTimeGRI)
		{
			delete m_RealTimeGRI;
			m_RealTimeGRI = nullptr;
		}
		if (m_Commands)
		{
			delete m_Commands;
			m_Commands = nullptr;
		}
	}

	RealTimeGRI* WindowOSPlatform::OSPlatformCreateRealTimeGRI()
	{ 
		if (m_TypeGRI && m_RealTimeGRI)
		{
			return m_RealTimeGRI;
		}
		//can create OpenGL Vulkan,Nuwa plan not support DX 
		m_TypeGRI = new GLTypeGRI();
		//Windows platform can support OpenGL, Vulakn GRI
		if (m_TypeGRI->IsSupport())
		{
			m_RealTimeGRI = m_TypeGRI->CreateGRI();
		}
		return m_RealTimeGRI;
	}

	GRICommands* WindowOSPlatform::OSPlatformCreateGRICommands()
	{
		if (m_TypeGRI && m_RealTimeGRI)
		{
			m_Commands = m_TypeGRI->CreateCommands();
			return m_Commands;
		}
		SN_ERR("Please Fast Call OSPlatformCreateRealTimeGRI Function.");
		return nullptr;
	}
}