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
#include "GRIResourceCreateInfo.h"
#include "GRIDrive.h"
// render type interface for engine 
namespace SkySnow
{
    class GRIPipelineCache;
    //Globle var
    extern GRIDrive*                GRI;
    extern GRIPipelineCache*        _GPipelineCache;
    
    //GRI Init
    void GRIInit();
    //GRI Exit
    void GRIExit();
    //GRI Flush GPU Resource(GPU Handle Recycle)
    void FlushResource();
    //Viewport Create
    GRIViewportStateRef GRCCreateViewport(void* windowHandle,uint32 width,uint32 height,PixelFormat format,bool isFullScreen);
    //Create VS
    GRIVertexShaderRef GRCCreateVertexShader(ResourceData& rData);
    //Create Fs
    GRIFragmentShaderRef GRCCreateFragmentShader(ResourceData& rData);
    //Create PipelineShader
    GRIPipelineShaderRef GRCCreatePipelineShader(GRIVertexShader* vs, GRIFragmentShader* fs);
    //Create Buffer BufferType:IndexBuffer\VertexBuffer\SSBO
    GRIBufferRef GRCCreateBuffer(BufferUsageType usageType, int size, int stride,ResourceData& rData);
    //Create Vertex Declaration
    GRIVertexDescriptorRef GRCCreateVertexDescriptor(const VertexElementList& vdel);
    //Create Pipeline
    GRIGraphicsPipelineRef GRCCreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo);
    //Create UniformBuffer
    GRIUniformBufferRef GRCCreateUniformBuffer(const UniformSlotList& contents,const char* ubName,UniformBufferUsageType ubType);
    //Create UniformBufferList Desc
    GRIUniformBufferDescriptorRef GRCCreateUniformDescriptor(const UniformBufferList& ubl);
    //Create Texture2D
    GRITexture2DRef GRCCreateTexture2D(uint32 sizex, uint32 sizey, PixelFormat format, uint32 numMips, uint32 numSamples, TextureUsageType usageType,ResourceData& rData);
    //Texture2DArray
    GRITexture2DArrayRef GRCCreateTexture2DArray(uint32 sizex, uint32 sizey, uint32 sizez, PixelFormat format, uint32 numMips, uint32 numSamples, TextureUsageType usageType,ResourceData& rData);
    //Texture3D
    GRITexture3DRef GRCCreateTexture3D(uint32 sizex, uint32 sizey, uint32 sizez, PixelFormat format, uint32 numMips, TextureUsageType usageType, ResourceData& rData);
    //TextureCube
    GRITextureCubeRef GRCCreateTextureCube(uint32 size, PixelFormat format, uint32 numMips, TextureUsageType usageType,ResourceData& rData);
    //SamplerState
    GRISamplerStateRef GRCCreateSampler(const SamplerState& sState);
}
