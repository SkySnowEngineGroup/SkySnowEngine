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
#include "EditorWindow.h"
namespace Editor
{
    GLFWWindow::GLFWWindow()
        : IWindow()
        , _Window(nullptr)
        , _Width(0)
        , _Height(0)
    {
    }

    GLFWWindow::~GLFWWindow()
    {
    }

    void GLFWWindow::CreateEngineWindow(unsigned int width, unsigned int height)
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
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        _Window = glfwCreateWindow(width, height, SkySnow_Name, NULL, NULL);
        if (!_Window)
        {
            SN_ERR("glfwCreateWindow failed!");
            glfwTerminate();
        }
        //glfwSetWindow(_Window);
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
}
