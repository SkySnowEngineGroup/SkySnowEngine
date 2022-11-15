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
#include "GRICommands.h"
#include "StackAllocator.h"
#include "CommandBufferMacro.h"
#include "GRILowerCommandBuffer.h"
#include <vector>
namespace SkySnow
{
    class GRICommandBufferQueue;
    class GRICommandBufferPool;
    class GRICommandBufferBase
    {
    public:
        GRICommandBufferBase(CommandBufferSate cbState = Initial);
        virtual ~GRICommandBufferBase() 
        {
            _CMState = Invalid;
        }

        virtual void Reset() = 0;
        virtual void BeginCommandBuffer() = 0;
        virtual void EndCommandBuffer() = 0;

        virtual void BeginRenderPass() = 0;
        virtual void EndRenderPass() = 0;

    protected:
        CommandBufferSate   _CMState;
    };

    class GRICommandBufferPool
    {
    public:
        GRICommandBufferPool()
        {
        }

        ~GRICommandBufferPool()
        {

        }

        GRICommandBufferBase* AllocCommandBuffer()
        {
            return CreateCMB();
        }
        void ReleasePool()
        {

        }
    private:
        GRICommandBufferBase* CreateCMB();
    };
    class GRICommandBufferQueue
    {
    public:
        void Init();
        void SubmitQueue(GRICommandBuffer* comBuf)
        {

        }

        void BeginFrame();

        void EndFrame();

        void FlushResource()
        {

        }
        void PresentQueue()
        {

        }
        GRILowerCommandBuffer* GetLowerCommandBuffer()
        {
            return _LowerComBuf;
        }

        bool IsLowerVerion();
    private:
        GRILowerCommandBuffer* _LowerComBuf;
    };


    inline GRIVertexShaderRef CreateVertexShader(const char* vsCode)
    {
        if (!_GQueue.IsLowerVerion())
        {
            return GRI->GRICreateVertexShader(vsCode);
        }
        return _GQueue.GetLowerCommandBuffer()->CreateVertexShader(vsCode);
    }
    //全局唯一的一个Queue
    GRICommandBufferQueue _GQueue;
}
