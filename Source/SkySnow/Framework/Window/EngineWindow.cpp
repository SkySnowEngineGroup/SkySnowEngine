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
#include "EngineWindow.h"
#include "GLFWWindow.h"
#include "SkySnowProfiles.h"
namespace SkySnow
{
	EngineWindow::~EngineWindow()
	{
        Delete_Object(_OSWindow);
        Delete_Object(_Viewport);
	}

    void EngineWindow::CreateEngineWindow(uint32 width, uint32 height, std::string windowName, EngineWindow* shareWindow)
    {
        _OSWindow = new GLFWWindow();
        _OSWindow->CreateOSWindow(width, height, shareWindow ? shareWindow->GetOSWindow() : nullptr, windowName);
        _Viewport = new Viewport();
        _Viewport->CreateEngineViewport(_OSWindow->GetNativeWindow(), width, height);
    }

    void EngineWindow::ExitViewPort()
    {
        Delete_Object(_Viewport);
    }

    void EngineWindow::ShutDown()
    {
        _OSWindow->ShutDown();
    }
}
