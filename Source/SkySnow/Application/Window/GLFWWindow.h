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
#include "GRIProfiles.h"
namespace SkySnow
{
	//can be use mac and window os
	class SN_GLFWWindow: public IWindow
	{
	public:
		SN_GLFWWindow();
			
		~SN_GLFWWindow();

		virtual void SNCreateWindow(unsigned int width,unsigned int height) override;

		virtual bool SNIsCloseWindow() override;

		virtual void SNShutDown() override;

		void MakeGLContext();

		void LoadgladFun();

		void GLFWSwapBuffer();

        GLFWwindow* GetWindow()
        {
            return m_Window;
        }
		int GetWindowWidth()
		{
			return m_Width;
		}

		int GetWindowHeight()
		{
			return m_Height;
		}

	private:
		unsigned int		m_Width;
		unsigned int		m_Height;
		GLFWwindow*			m_Window;
	};
}
