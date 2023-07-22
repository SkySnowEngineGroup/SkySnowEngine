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
#include "OSWindow.h"
namespace SkySnow
{
	class GLFWWindow : public OSWindow
	{
	public:
		GLFWWindow()
			: OSWindow(GLFW)
			, _Width(0)
			, _Height(0)
			, _Window(nullptr)
		{}

		virtual ~GLFWWindow() {}
	public:
		virtual void CreateOSWindow(uint32 width, uint32 height, OSWindow* shareWindow = nullptr) override;

		virtual void* GetClientWindow() override;

		virtual void* GetNativeWindow() override;

		virtual bool IsCloseWindow() override;

		virtual void ShutDown() override;

		virtual uint32 GetWindowWidth() const override;

		virtual uint32 GetWindowHeight() const override;
	private:
		unsigned int    _Width;
		unsigned int    _Height;
		GLFWwindow*		_Window;
	};
}