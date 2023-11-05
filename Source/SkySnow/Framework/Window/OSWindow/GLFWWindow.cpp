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
	void GLFWWindow::CreateOSWindow(uint32 width, uint32 height, OSWindow* shareWindow)
	{
		_Width = width;
		_Height = height;
		if (width == 0 || height == 0)
		{
			SN_ERR("The window height or width parameter set iszero.");
		}
		bool initFlag = glfwInit();
		if (!initFlag)
		{
			SN_ERR("glfwInit() failed!");
		}
		//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		GLFWwindow* tShareWindow = shareWindow ? (GLFWwindow*)shareWindow->GetClientWindow() : nullptr;
		_Window = glfwCreateWindow(width, height, SkySnow_Name, NULL, tShareWindow);
		if (!_Window)
		{
			const char* description;
			int error = glfwGetError(&description);
			SN_ERR("glfwCreateWindow failed:%s", description);
			glfwTerminate();
		}
	}
	void* GLFWWindow::GetClientWindow()
	{
		return _Window;
	}
	void* GLFWWindow::GetNativeWindow()
	{
#if PLATFORM == PLATFORM_WINDOW
		return glfwGetWin32Window(_Window);
#elif PLATFORM == PLATFORM_MAC
		return glfwGetCocoaWindow(_Window);
#endif
	}

	bool GLFWWindow::IsCloseWindow()
	{
		int close = false;
		if (_Window)
		{
			if (glfwGetKey(_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(_Window, true);
			}
			//该函数返回0为未退出，返回非零为退出
			close = glfwWindowShouldClose(_Window);
		}
		return close;
	}

	void GLFWWindow::ShutDown()
	{
		if (_Window)
		{
			glfwTerminate();
		}
	}

	uint32 GLFWWindow::GetWindowWidth() const
	{
		return _Width;
	}

	uint32 GLFWWindow::GetWindowHeight() const
	{
		return _Height;
	}
}
