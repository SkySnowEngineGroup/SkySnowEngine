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
#include <vector>
namespace SkySnow
{
    class GRICommandBufferQueue;
    class GRICommandBufferPool;
    class GRICommandBuffer;
    
    class GRICommandBuffer
    {
    public:
        GRICommandBuffer(CBExecuteType exeType = Render);
        virtual ~GRICommandBuffer()
        {
            _StackMem.Flush();
        }

        inline void* AllocCommand(int64_t cmdSize,int32_t cmdAlign)
        {
            GRICommandBase* cmd = (GRICommandBase*)_StackMem.Alloc(cmdSize,cmdAlign);
            _NumCommands ++;
            _Curr = cmd;
            _Curr = cmd->_Next;
            return cmd;
        }

        template<typename CMD>
        inline void* AllocCommand()
        {
            return AllocCommand(sizeof(CMD),alignof(CMD));
        }
        //reset this commandbuffer command to init
        void Reset()
        {
        }
    protected:

    protected:
        GRICommandBase* _Head;
        GRICommandBase* _Curr{ _Head};
        CBExecuteType   _ExecuteType;
    private:
        int             _NumCommands;
        MemStack        _StackMem;
    };
#define Alloc_Command(...) new(AllocCommand(sizeof(__VA_ARGS__), alignof(__VA_ARGS__))) __VA_ARGS__
	//function call back GRICommands and RealTimeGRL
	//type: RenderCommandBuffer ComputeCommandBuffer ext
	class GRIRenderCommandBuffer : public GRICommandBuffer
	{
	public:
        GRIRenderCommandBuffer()
            : GRICommandBuffer(Render)
		{
		}

		GRIVertexShaderRef CMBCreateVertexShader(const char* vsCode)
		{
			GRIVertexShaderRef _VsHandle;
            Alloc_Command(GRICreateVertexShaderCMD)(_VsHandle, vsCode);
			return _VsHandle;
		}
	};


}
