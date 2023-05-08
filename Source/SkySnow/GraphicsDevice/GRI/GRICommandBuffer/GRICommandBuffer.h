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
#include "RunnableThread.h"
namespace SkySnow
{
    //vulkan 中关于资源创建，资源命令设置以及同步等操作的渲染接口，一共约130个
    class GRICommandBufferQueue;
    class GRICommandBufferPool;
    class RenderRunnable;
    
    class GRICommandBufferBase
    {
        friend class GRICommandBufferPool;
    public:
        GRICommandBufferBase(CommandBufferSate cbState = Initial);
        virtual ~GRICommandBufferBase();
        
        virtual void CmdResourceSetExecutor() = 0;
        virtual void CmdReset() = 0;
        virtual void CmdBeginCommandBuffer() = 0;
        virtual void CmdEndCommandBuffer() = 0;
        virtual void CmdBeginRenderPass() = 0;
        virtual void CmdEndRenderPass() = 0;
    protected:
        void SetupState(CommandBufferSate cmbType);
        bool CommandBufferValid(CommandBufferType cmbType);
    protected:
        CommandBufferSate   _CMState;
        CommandBufferType   _CMType;
    };

    class GRIRenderCommandBuffer : public GRICommandBufferBase
    {
    public:
        virtual ~GRIRenderCommandBuffer() {}
        //this interface will move blitcommandbuffer
        virtual void CmdBeginViewport() = 0;
        virtual void CmdEndViewport() = 0;

        virtual void CmdSetBuffer(int bufferIndex, GRIBuffer* buffer, int offset) = 0;
        virtual void CmdDrawPrimitive(int numPrimitive, int numInstance) = 0;
        virtual void CmdSetPipelineShader(GRIPipelineShader* pipelineShaderState) = 0;
        virtual void CmdSetGraphicsPipeline(GRIGraphicsPipeline* pipelineState) = 0;
    protected:
    };
    //compute shader is a single pipeline
    class GRIComputeCommandBuffer : public GRICommandBufferBase
    {
    public:
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

        GRICommandBufferBase* AllocCommandBuffer(CommandBufferType cbType = Render)
        {
            return CreateCommandBuffer(cbType);
        }
        void ReleasePool()
        {

        }
    private:
        GRICommandBufferBase* CreateCommandBuffer(CommandBufferType cbType);
    private:
        ThreadMutex                 _Lock;
        std::vector<GRICommandBufferBase*>  _CommandBufferList;//testCode
    };
    class GRICommandBufferQueue
    {
    public:
        GRICommandBufferQueue();
        ~GRICommandBufferQueue();
        void Init();
        void SubmitQueue(GRICommandBufferBase* comBuf);

        void BeginFrame();

        void EndFrame();

        void FlushResource();
        
        void PresentQueue();

        GRICreateCommandBuffer* GetLowerCommandBuffer();

        bool IsLowerVerion();
    private:
        GRICreateCommandBuffer*             _LowerComBuf;
        std::vector<GRICommandBufferBase*>  _ComBufList;
        RenderRunnable*                     _RenderRunnable;
        RunnableThread*                     _RenderThread;
    };
    extern GRICommandBufferQueue*   _GQueue;
}
