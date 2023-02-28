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
#include "StackAllocator.h"
#include "CommandBufferMacro.h"
#include "GRILowerCommandBuffer.h"
namespace SkySnow
{
    //vulkan 中关于资源创建，资源命令设置以及同步等操作的渲染接口，一共约130个
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

        virtual void CmdReset() = 0;
        virtual void CmdBeginCommandBuffer() = 0;
        virtual void CmdEndCommandBuffer() = 0;

        virtual void CmdBeginRenderPass() = 0;
        virtual void CmdEndRenderPass() = 0;

        virtual void CmdSetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset) = 0;
        virtual void CmdDrawPrimitive(int numPrimitive, int numInstance) = 0;
        virtual void CmdSetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState) = 0;
        virtual void CmdSetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState) = 0;
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
    extern GRICommandBufferQueue*   _GQueue;
}
