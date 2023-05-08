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
    //Resource Set CommandBuffer Base Class For LowerVersion API
    class GRISetCommandBuffer
    {
    public:
        GRISetCommandBuffer();
        virtual ~GRISetCommandBuffer();
        inline void* AllocCommandSet(int64_t cmdSize, int32_t cmdAlign)
        {
            GRICommandBase* cmd = (GRICommandBase*)_StackMem.Alloc(cmdSize, cmdAlign);
            _NumCommands++;
            if (_Head == nullptr)
            {
                _Head = cmd;
                _Curr = cmd;
            }
            else
            {
                _Curr->_Next = cmd;
                _Curr = cmd;
            }
            return cmd;
        }
    protected:
        int                 _NumCommands;
        GRICommandBase*     _Curr;
        GRICommandBase*     _Head{ _Curr };
        MemStack            _StackMem;
    };
//GPUResourceSet use this on OpenGL & GLES & DX9 & DX11
#define Alloc_CommandSet(...) new(AllocCommandSet(sizeof(__VA_ARGS__), alignof(__VA_ARGS__))) __VA_ARGS__
    //============================================================================================================
    //Resource Create CommandBuffer Base Class For LowerVersion API
    class GRICreateCommandBuffer
    {
    public:
        GRICreateCommandBuffer();
        virtual ~GRICreateCommandBuffer();
        template<typename T, typename... Args>
        void AllocCommandCreate(Args&&... args)
        {
            _Lock.Lock();
            GRICommandBase* mem = (GRICommandBase*)_StackMem.Alloc(sizeof(T), alignof(T));
            T* cmd = new(mem) T(std::forward<Args>(args)...);
            _NumCommands++;
            if (_Head == nullptr)
            {
                _Head = cmd;
                _Curr = cmd;
            }
            else
            {
                _Curr->_Next = cmd;
                _Curr = cmd;
            }

            _Lock.UnLock();
        }
    public:
        virtual GRIVertexShaderRef CreateVertexShader(const char* vsCode) = 0;

        virtual GRIFragmentShaderRef CreateFragmentShader(const char* fsCode) = 0;

        virtual GRIPipelineShaderRef CreatePipelineShader(GRIVertexShader* vs, GRIFragmentShader* fs) = 0;

        virtual GRIBufferRef CreateBuffer(BufferUsageType usageType, int size, int stride, void* data) = 0;

        virtual GRIGraphicsPipelineRef CreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo) = 0;

        virtual GRIVertexDeclarationRef CreateVertexDeclaration(const VertexDeclarationElementList& vdel) = 0;

        virtual void ResourceCreateExecutor();
    private:
        void CommandBufferReset();
    protected:
        int                 _NumCommands;
        GRICommandBase*     _Curr;
        GRICommandBase*     _Head{ _Curr };
        MemStack            _StackMem;
        ThreadMutex         _Lock;
    };
//GPUResourceCreate use this on OpenGL & GLES & DX9 & DX11
#define Alloc_CommandCreate(type,...) AllocCommandCreate<type>(__VA_ARGS__)
}
