//
// Copyright(c) 2020 - 2022 the NuwaEngine project.
// Open source is written by wangcan(crygl)¡¢liuqian(SkySnow)¡¢zhangshuangxue(Calence)
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
#include "RealTimeGRI.h"
#include "PlatformProfiles.h"

//The rendering API allocates different API header imports depending on the platform
#if PLATFORM == PLATFORM_ANDROID
#	include "GLESAndroid.h"
#elif PLATFORM == PLATFORM_IOS
#	include "GLESIos.h"
#elif PLATFORM == PLATFORM_WINDOW
#	include "GLWindow.h"
#elif PLATFORM == PLATFORM_MAC
#	include "GLMac.h"
#endif

namespace Nuwa
{
	/*
		brief: Each real-time rendering API (GRI) unifies the base class of the external interface. 
			   Different rendering APIs inherit from this class and implement the functions of 
			   different APIs with the same capability
	*/
	class GLRealTimeGRI :public RealTimeGRI
	{
	public:
		GLRealTimeGRI();

		~GLRealTimeGRI() {}

		GRIFeature GetGRIFeatureType() override { return OpenGL::GetGRIFeatureType(); }

		void GRIClearColor(float red, float green, float blue, float alpha) final override;

		virtual GRIVertexShaderRef GRICreateVertexShader(const char* vsCode) final override;

		virtual GRIFragmentShaderRef GRTCreateFragmentShader(const char* fsCode) final override;
	};
}