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
#include "GRICommandBuffer.h"
#include "GRILowerCommandBuffer.h"
#include "GLCreateCommandBuffer.h"
#include "RunnableThread.h"

namespace SkySnow
{
    class GRILowerCommandBufferQueue : public GRICommandBufferQueue
    {
    public:
        GRILowerCommandBufferQueue();
        
        ~GRILowerCommandBufferQueue();
        
        virtual void Init() final override;
        virtual void SubmitCommandBuffer(GRICommandBufferBase* comBuf) final override;
        
        virtual void BeginFrame() final override;
        
        virtual void EndFrame() final override;
        //LC is Lower Create CommandBuffer for GL\GLES\DX9
        virtual GRICreateCommandBuffer* GetLowerCommandBuffer() final override;
        
        virtual void WaitforRenderThreadExit() final override;
        
        virtual void PresentQueue() final override;
        
    private:
        //Double List or RingBuffer
        GLCreateCommandBuffer*              _MainCreatCB;
        GLCreateCommandBuffer*              _RenderCreateCB;
        std::vector<GRICommandBufferBase*>  _MainCBList;
        std::vector<GRICommandBufferBase*>  _RenderCBList;
        
        //RenderThread
        RunnableThread*                     _RenderThread;
        RenderRunnable*                     _RenderRunnable;
        //Submit Lock
        ThreadMutex                         _SubmitLock;
    };
}
