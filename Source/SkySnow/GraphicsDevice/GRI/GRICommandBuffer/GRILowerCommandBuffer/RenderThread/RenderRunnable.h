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
#include "GRIDrive.h"
#include "GLPipelineResource.h"
#include "Runnable.h"
#include "ThreadSemaphore.h"
namespace SkySnow
{
    //禁止继承该类，该类为引擎核心部件
	class RenderRunnable final: public Runnable
	{
    public:
        RenderRunnable();
        
        ~RenderRunnable();
        
        void BeginFrame();
        
        void EndFrame();
        
        virtual void Run() override;

        virtual void Stop() override;

        virtual void Exit() override;

        void WaitForRenderThread();
    private:
        void OnRenderFrame();
    private:
        std::atomic<bool>   _ExitFlag;
        std::atomic<bool>   _FrameFinish;
        std::atomic<bool>   _RenderThreadEnd;
        ThreadSemaphore     _RenderSem;
        ThreadSemaphore     _MainSem;
	};
}
