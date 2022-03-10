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
#include "GRICommons.h"
#include "GRIResource.h"
namespace SkySnow
{
	//根据不同平台创建不同的渲染API
	class RealTimeGRI
	{
	public:
		virtual ~RealTimeGRI() {}

		virtual GRIFeature GetGRIFeatureType() = 0;
		// Test:clear quad color
		virtual void GRIClearColor(float red, float green, float blue, float alpha) = 0;
		//Create Vertex Shader
		//virtual GRIVertexShaderRef GRICreateVertexShader(const char* vsCode) = 0;
		//Create Fragment Shader
		//virtual GRIFragmentShaderRef GRTCreateFragmentShader(const char* fsCode) = 0;
	};
};
