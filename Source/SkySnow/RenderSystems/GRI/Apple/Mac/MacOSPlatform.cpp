//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
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
#include "MacOSPlatform.h"
#include "GLTypeGRI.h"
namespace SkySnow
{
    MacOSPlatform::MacOSPlatform()
        : m_TypeGRI(nullptr)
        , m_RealTimeGRI(nullptr)
    {

    }

    MacOSPlatform::~MacOSPlatform()
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
    }

    RealTimeGRI* MacOSPlatform::OSPlatformCreateRealTimeGRI()
    {
        if (m_TypeGRI && m_RealTimeGRI)
        {
            return m_RealTimeGRI;
        }
        m_TypeGRI = new GLTypeGRI();
        //m_PlatformGRI = new VulkanPlatformGRI();//if config with json
        //m_PlatformGRI = new MetalPlatformGRI();
        //Windows platform can support OpenGL, Vulakn GRI
        if (m_TypeGRI->IsSupport())
        {
            m_RealTimeGRI = m_TypeGRI->CreateGRI();
        }
        return m_RealTimeGRI;
    }
}
