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
#include "GRICommandBuffer.h"
#include "GLCommandBuffer.h"
namespace SkySnow
{
	GRICommandBufferBase::GRICommandBufferBase(CommandBufferSate cbState)
		: _CMState(cbState)

	{
	}


    GRICommandBufferBase* GRICommandBufferPool::CreateCMB()
    {
        GRICommandBufferBase* tempCmb = nullptr;
        GRIFeature version = GRI->GetGRIFeatureType();
        switch (version)
        {
        case SkySnow::ENone:
            break;
        case SkySnow::EVulkan:
            break;
        case SkySnow::EMetal:
            break;
        case SkySnow::EGLES:
        case SkySnow::EOpenGL:
            tempCmb = new GLCommandBuffer();
            break;
        default:
            break;
        }
        return tempCmb;
    }

	void GRICommandBufferQueue::Init()
	{
        GRIFeature version = GRI->GetGRIFeatureType();
        switch (version)
        {
        case SkySnow::ENone:
            break;
        case SkySnow::EGLES:
        case SkySnow::EOpenGL:
            _LowerComBuf = new GLCommandBuffer();
            break;
        case SkySnow::EDx9:
        case SkySnow::EDx10:
        case SkySnow::EDx11:
            break;
        default:
            break;
        }
	}
    bool GRICommandBufferQueue::IsLowerVerion()
    {
        GRIFeature version = GRI->GetGRIFeatureType();
        if (version == EVulkan ||
            version == EMetal ||
            version == EDX12)
        {
            return false;
        }
        return true;
    }
}
