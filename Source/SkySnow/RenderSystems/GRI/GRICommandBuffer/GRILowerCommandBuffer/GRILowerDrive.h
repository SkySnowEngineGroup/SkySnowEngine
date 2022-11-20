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
#include "GRICommons.h"
#include "GRIResource.h"
#include "GRIResourceCreateInfo.h"
namespace SkySnow
{
	//这是不支持并行提交命令的低版本API的桥接版本，低版本API必须继承此类，高版本不需要
	//低版本的API需要继承实现，而metal&vulkan&dx12则不需要
	class GRILowerDrive
	{
		//GRISet==========================================================================================================================
		virtual void GRISetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset) = 0;
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) = 0;
		virtual void GRISetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState) = 0;
		virtual void GRISetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState) = 0;
		//GRISet==========================================================================================================================
	};
}