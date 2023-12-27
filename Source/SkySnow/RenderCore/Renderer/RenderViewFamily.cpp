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
#include "RenderViewFamily.h"

namespace SkySnow
{
	RenderViewFamily::RenderViewFamily()
	{

	}

	RenderViewFamily::~RenderViewFamily()
	{

	}

    void RenderViewFamily::AddRenderView(CameraProxy* cameraProxy)
    {
        auto renderView = CreateSPtr<RenderView>(cameraProxy);
        _RenderViews.push_back(renderView);
    }

    void RenderViewFamily::RemoveRenderView(CameraProxy* cameraProxy)
    {
        for(auto iter = _RenderViews.begin(); iter != _RenderViews.end();)
        {
            if((*iter)->IsEqual(cameraProxy))
            {
                iter = _RenderViews.erase(iter);
            }
            else
            {
                iter ++;
            }
        }
    }
}