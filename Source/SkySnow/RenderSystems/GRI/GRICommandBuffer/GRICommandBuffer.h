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
#include <vector>
namespace SkySnow
{
    class GRICommandBufferQueue;
    class GRICommandBufferPool;
    class GRICommandBufferBase;
    
    class GRICommandBufferBase
    {
    public:
        GRICommandBufferBase();

    protected:
        void AllocCommand()
        {

        }
        //reset this commandbuffer command to init
        void Reset()
        {

        }
    protected:
        GRICommandBase* _Head;
        GRICommandBase* _Curr{ _Head};
    private:
        MemStack*       _StackMem;
    };
	//function call back GRICommands and RealTimeGRL
	//type: RenderCommandBuffer ComputeCommandBuffer ext
	class GRICommandBuffer : public GRICommandBufferBase
	{
	public:
		GRICommandBuffer()
            : GRICommandBufferBase()
		{
		}

		GRIVertexShaderRef CMBCreateVertexShader(const char* vsCode)
		{
			GRIVertexShaderRef _VsHandle;
			_Curr->_Next = new GRICreateVertexShaderCMD(_VsHandle, vsCode);
			_Curr = _Curr->_Next;
			return _VsHandle;
		}
	};

    class GRICommandBufferPool
    {
    public:
        GRICommandBufferPool()
        {
        }
        
        ~GRICommandBufferPool()
        {
            ReleasePool();
        }
        
        GRICommandBuffer* AllocCommandBuffer()
        {
            GRICommandBuffer* newComBuf = new GRICommandBuffer();
            _CommandBufferList.emplace_back(newComBuf);
            return newComBuf;
        }
        
        void ReleasePool()
        {
            for (std::vector<GRICommandBuffer*>::const_iterator itr=_CommandBufferList.begin(); itr!=_CommandBufferList.end(); ++itr)
            {
              delete *itr;
            }
            _CommandBufferList.clear();
        }
    private:
        std::vector<GRICommandBuffer*> _CommandBufferList;
    };

    class GRICommandBufferQueue
    {
    public:
        
        void SubmitQueue(GRICommandBuffer* comBuf)
        {
           
        }

        void FlushResource()
        {

        }
        void PresentQueue()
        {
            
        }
        //call by renderthread at gl,other vulkan&metal also will create renderthread
        //curr frame has result
        void ImmediatelyExecuteCommandBuffer()
        {
            
        }
        //call by renderthread at gl,other vulkan&metal also will create renderthread
        //next frame has result
        void DeferredExecuteCommandBuffer()
        {
            
        }
    };

    GRICommandBufferQueue _GlobleComBufQueue;
}
