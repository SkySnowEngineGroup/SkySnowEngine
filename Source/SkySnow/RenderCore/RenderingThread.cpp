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
#include "RenderingThread.h"
#include "OSPlatform.h"
namespace SkySnow
{
    RenderingThread::RenderingThread()
        : m_ExitRenderingThread(false)
        , m_SNWindow(nullptr)
    {
        
    }
    RenderingThread::~RenderingThread()
    {
        m_ExitRenderingThread = true;
    }
    //如果是GLFW，GLFWSwapBuffer必须在主线程进行调用，因为SwapBuffer是交换后台缓冲到前台缓冲显示。
    //如果想要单独起一个渲染线程，那么需要创建一个ShareContext给渲染线程，渲染到BackBuffer中，从BackBuffer
    //可以使用像素解包缓冲区到纹理，给GLFW所在线程显示,或者是使用windowsurface，渲染到挂载到fbo的纹理上给GLFW所在线程显示
    //从Main函数中调用而来
    void RenderingThread::RenderOneFrame()
    {
        m_SNWindow->MakeGLContext();
        m_SNWindow->LoadgladFun();
        glViewport(0,0,m_SNWindow->GetWindowWidth(),m_SNWindow->GetWindowHeight());
        while (!m_SNWindow->SNIsCloseWindow())
        {
            SN_LOG("SkySnowEngine Rendering Thread Update.");
            GRC->GRIClearColor(1.0,0.0,0.0,1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            m_SNWindow->GLFWSwapBuffer();
        }
        m_SNWindow->SNShutDown();
    }
}
