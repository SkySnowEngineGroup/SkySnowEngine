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
#pragma once
#include "IWindow.h"
#include "LogAssert.h"
namespace Editor
{
    class GLFWWindow final : public SkySnow::IWindow
    {
    public:
        GLFWWindow();

        ~GLFWWindow();

        virtual void CreateEngineWindow(unsigned int width, unsigned int height) override;

        virtual bool IsCloseWindow() override;

        virtual void ShutDown() override;

        void* GetNativeWindow()
        {
#if PLATFORM == PLATFORM_WINDOW
            return glfwGetWin32Window(_Window);
#elif PLATFORM == PLATFORM_MAC
            return glfwGetCocoaWindow(_Window);
#endif
        }

        int GetWindowWidth() const
        {
            return _Width;
        }

        int GetWindowHeight() const
        {
            return _Height;
        }
    private:
        unsigned int        _Width;
        unsigned int        _Height;
        GLFWwindow* _Window;
    };
}
