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
#include "ISystem.h"
#include "GRICommandBuffer.h"
#include "GRI.h"
#include "File.h"
namespace SkySnow
{
    class RenderSystem : public ISystem
    {
    public:
        RenderSystem();
        
        ~RenderSystem();
        
        virtual void PreUpdate() final override;
        
        virtual void Update() final override;
        
        virtual void PostUpdate()final override;
        
        virtual void ShutDown() final override;
    private:
        bool                        _TestInit = false;
        File*                       _File;
        Data*                       _VsData;
        Data*                       _FsData;
        GRIVertexShaderRef          _vsRef;
        GRIFragmentShaderRef        _fsRef;
        GRIBufferRef                _VertexBufferRef;
        GRIBufferRef                _ColorBufferRef;
        GRIVertexDescriptorRef      _VertexDescriptor;
        GRIPipelineShaderRef        _PipelineShaderRef;
        GRIGraphicsPipelineRef      _PSORef;
        GRICommandBufferPool*       _CMBPool;
    };
}