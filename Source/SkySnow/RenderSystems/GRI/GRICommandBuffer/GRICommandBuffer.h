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
        virtual void CmdResourceSetExecutor() = 0;
        virtual void CmdReset() = 0;
        virtual void CmdBeginCommandBuffer() = 0;
        virtual void CmdEndCommandBuffer() = 0;
        virtual void CmdBeginRenderPass() = 0;
        virtual void CmdEndRenderPass() = 0;
        bool CommandBufferValid(CommandBufferType cmbType)
        {
            if(_CMState == Invalid && cmbType == _CMType)
            {
                return true;
            }
            return false;
        }
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

        virtual void CmdSetBuffer(int BufferInfoId, GRIBuffer* buffer, int offset) = 0;
        virtual void CmdDrawPrimitive(int numPrimitive, int numInstance) = 0;
        virtual void CmdSetPipelineShaderState(GRIPipelineShaderState* pipelineShaderState) = 0;
        virtual void CmdSetGraphicsPipelineState(GRIGraphicsPipelineState* pipelineState) = 0;
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
        void Init();
        void SubmitQueue(GRICommandBufferBase* comBuf)
        {
            _ComBufList.push_back(comBuf);
        }

        void BeginFrame()
        {
        }

        void EndFrame()
        {
            
        }

        void FlushResource()
        {

        }
        void PresentQueue()
        {
            //TestCode Single MainThread Render Capacity
            //TestCode == Resource Create At Lower Api Version
            _LowerComBuf->ResourceCreateExecutor();
            //TestCode == Resource Set At Lower Api Version,At Height Api Version Use Self CommandBuffer
            for (int i = 0; i < _ComBufList.size(); i ++)
            {
                GRICommandBufferBase* cmb = _ComBufList[i];
                cmb->CmdResourceSetExecutor();
            }
            _ComBufList.clear();
        }
        GRILowerCommandBuffer* GetLowerCommandBuffer()
        {
            return _LowerComBuf;
        }

        bool IsLowerVerion();
    private:
        GRILowerCommandBuffer*              _LowerComBuf;
        std::vector<GRICommandBufferBase*>  _ComBufList;
    };
    extern GRICommandBufferQueue*   _GQueue;
}
