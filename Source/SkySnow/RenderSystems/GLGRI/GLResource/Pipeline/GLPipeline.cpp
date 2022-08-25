//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by sunguoqiang(SunGQ1987),wangcan(crygl),
//							 liuqian(SkySnow),zhangshuangxue(Calence)
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
#include "GLPipeline.h"
#include "GRIGLDrive.h"
#include "GLPipelineResource.h"
namespace SkySnow
{
	//后期在抽象Encoder的时，会将此Interface接口归属与RenderEncoder编码器处理
	//RenderEncoder从EncoderPool申请，单独处理该接口，如果加载数据压力较大的情况
	//下可以异步处理，即可以在一根线程单独持有pipeline的处理，而进行事件或者内存屏障进行同步
	GRIGraphicsPipelineStateRef GRIGLDrive::GRICreateGraphicsPipelineState(const GRICreateGraphicsPipelineStateInfo& createInfo)
	{
		return new GLGraphicPipelineState(createInfo);
	}
}