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
#include "OSPlatform.h"
#include "GRIResourceCreateInfo.h"
// render type interface for engine 
namespace SkySnow
{
    class GRIPipelineCache;
    //Globle var
    extern OSPlatform*              _GOSPlatform;
    extern GRIDrive*                GRI;
    extern GRIPipelineCache*        _GPipelineCache;
    
    //RHI Init
    void GRIInit(const OSPlatformInfo& osPlatformInfo);
    //RHI Exit
    void GRIExit();
 
    //Create VS
    GRIVertexShaderRef CreateVertexShader(const char* vsCode);
    //Create Fs
    GRIFragmentShaderRef CreateFragmentShader(const char* fsCode);
    //Create PipelineShader
    GRIPipelineShaderRef CreatePipelineShader(GRIVertexShader* vs, GRIFragmentShader* fs);
    //Create Buffer BufferType:IndexBuffer\VertexBuffer\SSBO
    GRIBufferRef CreateBuffer(BufferUsageType usageType, int size, int stride, void* data);
    //Create Vertex Declaration
    GRIVertexDescriptorRef CreateVertexDescriptor(const VertexElementList& vdel);
    //Create Pipeline
    GRIGraphicsPipelineRef CreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo);
    //Create UniformBuffer
    GRIUniformBufferRef CreateUniformBuffer(const UniformSlotList& contents,const char* ubName,UniformBufferUsageType ubType);
    //Create UniformBufferList Desc
    GRIUniformBufferDescriptorRef CreateUniformDescriptor(const UniformBufferList& ubl);
}
