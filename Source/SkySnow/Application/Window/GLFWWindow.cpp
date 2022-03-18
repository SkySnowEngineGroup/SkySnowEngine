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

#include "GLFWWindow.h"
namespace SkySnow
{
	SN_GLFWWindow::SN_GLFWWindow()
		: m_Window(nullptr)
		, m_Width(0)
		, m_Height(0)
	{
	}

	SN_GLFWWindow::~SN_GLFWWindow()
	{
	}

	void SN_GLFWWindow::SNCreateWindow(unsigned int width, unsigned int height)
	{
		m_Width  = width;
		m_Height = height;
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_Window = glfwCreateWindow(width,height,SkySnow_Name,NULL,NULL);
	}

	bool SN_GLFWWindow::SNCloseWindow()
	{
		int close = false;
		if (m_Window)
		{
			if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(m_Window, true);
			}
			close = glfwWindowShouldClose(m_Window);
		}
		return close;
	}

	void SN_GLFWWindow::SNShutDown()
	{
		if (m_Window)
		{
			glfwTerminate();
		}
	}
}