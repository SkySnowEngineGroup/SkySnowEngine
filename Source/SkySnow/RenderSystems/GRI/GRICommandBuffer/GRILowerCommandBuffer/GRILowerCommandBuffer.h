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
#include "ThreadMutex.h"
namespace SkySnow
{
    //The CommandBuffer is a wrapper for Opengl and Dx instructions that 
    //do not support parallel commit.The lower version of the CommandBuffer 
    //also supports concurrent commit, but encapsulates a layer of processing 
    //associated with the renderthread in the CommandBuffer interface with the driver
    //If there are many resources that need to be uploaded to the gpu, for example, 
    //you can start several RenderThread sand use the shared context to handle the 
    //time - consuming problem of uploading resources to the gpu
    class GRILowerCommandBuffer
    {
    public:
        GRILowerCommandBuffer();
        virtual ~GRILowerCommandBuffer();

    protected:
        // Command分配将不能采用此种模式，这种模式分配不是线程安全的
        // 多个线程可以<创建渲染资源指令>，并可全局使用，单个渲染线程消费<渲染资源创建指令>
        // MPSC无锁队列很合适:但是MPSC又会涉及到内存安全问题，比较复杂 TODO
        inline void* AllocCommandSet(int64_t cmdSize, int32_t cmdAlign)
        {
            GRICommandBase* cmd = (GRICommandBase*)_StackMem.Alloc(cmdSize, cmdAlign);
            _NumCommands++;
            _Curr = cmd;
            _Curr = cmd->_Next;
            return cmd;
        }

        template<typename T,typename... Args>
        void AllocCommandCreate(Args&&... args)
        {
            _Lock.Lock();
            GRICommandBase* mem = (GRICommandBase*)_StackMem.Alloc(sizeof(T), alignof(T));
            T* cmd = new(mem) T(std::forward<Args>(args)...);
            _NumCommands++;
            _Curr = cmd;
            _Curr = cmd->_Next;
            _Lock.UnLock();
        }
    public:
        virtual GRIVertexShaderRef CreateVertexShader(const char* vsCode) = 0;

        virtual GRIFragmentShaderRef CreateFragmentShader(const char* fsCode) = 0;

        virtual GRIPipelineShaderStateRef CreatePipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs) = 0;

        virtual GRIBufferRef CreateBuffer(BufferUsageType usageType, int size, int stride, void* data) = 0;

        virtual GRIGraphicsPipelineStateRef CreateGraphicsPipelineState(const GRICreateGraphicsPipelineStateInfo& createInfo) = 0;


        virtual void ResourceCreateExecutor();
    protected:
        int                         _NumCommands;
        GRICommandBase*             _Head;
        GRICommandBase*             _Curr{ _Head };
        MemStack                    _StackMem;
        //MpscQueue<GRICommandBase>   _MpscQueue;
        ThreadMutex                 _Lock;
    };
//GPUResourceSet use this on OpenGL & GLES & DX9 & DX11
#define Alloc_CommandSet(...) new(AllocCommandSet(sizeof(__VA_ARGS__), alignof(__VA_ARGS__))) __VA_ARGS__
//GPUResourceCreate use this on OpenGL & GLES & DX9 & DX11
#define Alloc_CommandCreate(type,...) AllocCommandCreate<type>(__VA_ARGS__)
}
