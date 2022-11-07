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
namespace SkySnow
{
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
        template<typename CMBType>
        CMBType* AllocCommandBuffer()
        {
            CMBType* newComBuf = new CMBType();
            _CommandBufferList.emplace_back(newComBuf);
            return newComBuf;
        }

        void ReleasePool()
        {
            for (std::vector<GRICommandBuffer*>::const_iterator itr = _CommandBufferList.begin(); itr != _CommandBufferList.end(); ++itr)
            {
                delete* itr;
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
