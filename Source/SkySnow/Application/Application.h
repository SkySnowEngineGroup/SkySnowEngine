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
#pragma once
#include "GRIProfiles.h"
#include <stdlib.h>
#include <iostream>
namespace SkySnow
{
	namespace Engine
	{
#if defined(PLATFORM_WINDOW) || defined(PLATFORM_MAC)
#define NUWA_DEFINE_APPLICATION_MAIN(application, ...)		\
		int main(int argc, char** argv)			\
		{											\
				application app(__VA_ARGS__);				\
				return RunApplication(&app,argc,argv);	\
		}
#endif
		class Application
		{
		public:
			Application(const char* name,const char* description);
			virtual ~Application() = 0;
			virtual void Init(int32_t argc, const char* const* _argv, uint32_t width,uint32_t height) = 0;
			virtual int ShutDown() = 0;
			virtual bool Update() = 0;
		private:
			const char* m_Name;
			const char* m_Description;
		};
		int RunApplication(Application* app, int argc, const char* const* argv);
	}
}

