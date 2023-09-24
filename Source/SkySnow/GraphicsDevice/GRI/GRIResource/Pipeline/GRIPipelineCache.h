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
#include "GRIResource.h"
#include "GRIResourceCreateInfo.h"
#include "DoubleMapCache.h"
namespace SkySnow
{
    class GRIPipelineCache
    {
    public:
        GRIPipelineCache();
        ~GRIPipelineCache();
        //刷新资源
        void FlushResourceRelease();
        //引擎退出
        void Shutdown();
        //获取缓存的GraphicsPipeline
        template<typename TypePipeline>
        bool GetGraphicsPipeline(const GRICreateGraphicsPipelineInfo& pipelineInfo, GRIGraphicsPipelineRef& handle);
        //获取缓存的ComputePipeline
        template<typename TypePipeline>
        bool GetComputePipeline(const GRICreateComputePipelineInfo& pipelineInfo, GRIComputePipelineRef& handle);
    private:
        DoubleMapCache<GRICreateGraphicsPipelineInfo, GRIGraphicsPipelineRef>  _GraphicsPipelineCache;
        DoubleMapCache<GRICreateComputePipelineInfo, GRIComputePipelineRef>   _ComputePipelineCache;
    };


    template<typename TypePipeline>
    inline bool GRIPipelineCache::GetGraphicsPipeline(const GRICreateGraphicsPipelineInfo& pipelineInfo, GRIGraphicsPipelineRef& handle)
    {
        GRIGraphicsPipelineRef outPipeline = nullptr;

        bool find = _GraphicsPipelineCache.Find(pipelineInfo, outPipeline);
        if (!find)
        {
            outPipeline = new TypePipeline(pipelineInfo);
            _GraphicsPipelineCache.Add(pipelineInfo, outPipeline);
        }

        handle = outPipeline;
        return find;
    }
    template<typename TypePipeline>
    inline bool GRIPipelineCache::GetComputePipeline(const GRICreateComputePipelineInfo& pipelineInfo, GRIComputePipelineRef& handle)
    {
        GRIComputePipeline* outPipeline = nullptr;


        handle = outPipeline;
        return true;
    }
}
