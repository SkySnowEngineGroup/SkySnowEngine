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
#include "GRICommandBuffer.h"
#include "SkySnowProfiles.h"
#include "GLCommandBuffer.h"
#include "GRIGLDrive.h"
#include "GRIModule.h"

namespace SkySnow
{
    //整体思考一个问题，面相对象编程的几个规范
    /*
     面向对象的几个原则
        1. 单一职责原则(Single Responsibility Principle)
           每一个类应该专注于做一件事情。 即：高内聚，低耦合
        2. 开闭原则（Open Close Principle）
           一个对象对扩展开放，对修改关闭。即：对类的改动是通过增加代码进行的，而不是修改现有代码
        3. 里氏替换原则（Liskov Substitution Principle）
           在任何父类出现的地方都可以用它的子类来替代
        4. 依赖倒置原则（Dependence Inversion Principle）
           要依赖于抽象，不要依赖于具体实现
        5. 接口隔离原则（Interface Segregation Principle）
           应当为客户端提供尽可能小的单独的接口，而不是提供大的总的接口
        6. 迪米特原则（Law Of Demeter）
           一个对象应当尽量少地与其他对象之间发生相互作用，使得系统功能模块相对独立
        7. 组合/聚合复用原则（Composite/Aggregate Reuse Principle）
           尽量使用组合/聚合的方式，而不是使用继承
     */
    //GRICommandBufferBase
    //================================================================================================
	GRICommandBufferBase::GRICommandBufferBase(CommandBufferSate cbState)
		: _CMState(cbState)

	{
	}
    GRICommandBufferBase::~GRICommandBufferBase()
    {
        _CMState = Invalid;
    }
    void GRICommandBufferBase::SetupState(CommandBufferSate cmbType)
    {
        _CMState = cmbType;
    }
    bool GRICommandBufferBase::CommandBufferValid(CommandBufferType cmbType)
    {
        if (_CMState == Invalid && cmbType == _CMType)
        {
            return true;
        }
        return false;
    }
    //GRICommandBufferPool
    //================================================================================================
    GRICommandBufferBase* GRICommandBufferPool::CreateCommandBuffer(CommandBufferType cbType)
    {
        _Lock.Lock();
        GRICommandBufferBase* tempCmb = nullptr;
        GRIFeature version = Drive()->GetGRIFeatureType();
        switch (version)
        {
        case SkySnow::ENone:
            break;
        case SkySnow::EVulkan:
            break;
        case SkySnow::EMetal:
            break;
        case SkySnow::EGLES:
        case SkySnow::EOpenGL:
            if(_CommandBufferList.size() != 0)
            {
                for(int i = 0; i < _CommandBufferList.size(); i ++)
                {
                    GRICommandBufferBase* commandBuffer = _CommandBufferList[i];
                    if(commandBuffer->CommandBufferValid(cbType))
                    {
                        tempCmb = commandBuffer;
                        tempCmb->SetupState(Recording);
                        break;
                    }
                }
            }
            if(tempCmb == nullptr)
            {
                if(cbType == Render)
                {
                    tempCmb = new GLRenderCommandBuffer();
                }
                else if(cbType == Compute)
                {
                    int a = 10;
                }
                _CommandBufferList.push_back(tempCmb);
            }
            break;
        default:
            break;
        }
        _Lock.UnLock();
        return tempCmb;
    }
    //GRICommandBufferQueue
    //================================================================================================
    bool GRICommandBufferQueue::IsLowerVerion()
    {
        GRIFeature version = Drive()->GetGRIFeatureType();
        if (version == EVulkan ||
            version == EMetal  ||
            version == EDX12)
        {
            return false;
        }
        return true;
    }

    //GRI Globle Create Resource Interface
    //================================================================================================
    void FlushResource()
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRIResManager::Instance().FlushResource();
            return;
        }
        CBQueue()->GetLowerCommandBuffer()->FlushResourceRelease();
    }
    //Create Viewport and Attach a Context or device
    GRIViewportStateRef GRCCreateViewport(void* windowHandle,uint32 width,uint32 height,PixelFormat format,bool isFullScreen)
    {
        return Drive()->GRICreateViewport(windowHandle, width, height, format, isFullScreen);
    }
    GRIVertexShaderRef GRCCreateVertexShader(ResourceData& rData)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRIVertexShaderRef handle;
            Drive()->GRICreateVertexShader(rData, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateVertexShader(rData);
    }

    GRIFragmentShaderRef GRCCreateFragmentShader(ResourceData& rData)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRIFragmentShaderRef handle;
            Drive()->GRICreateFragmentShader(rData, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateFragmentShader(rData);
    }

    GRIPipelineShaderRef GRCCreatePipelineShader(GRIVertexShader* vs, GRIFragmentShader* fs)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRIPipelineShaderRef handle;
            Drive()->GRICreatePipelineShader(handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreatePipelineShader(vs,fs);
    }

    GRIBufferRef GRCCreateBuffer(BufferUsageType usageType, int size, int stride,ResourceData& rData)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRIBufferRef handle;
            Drive()->GRICreateBuffer(usageType,size,stride,rData, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateBuffer(usageType, size, stride, rData);
    }
    
    GRIVertexDescriptorRef GRCCreateVertexDescriptor(const VertexElementList& vdel)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRIVertexDescriptorRef handle;
            Drive()->GRICreateVertexDescriptor(vdel, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateVertexDescriptor(vdel);
    }
    GRIGraphicsPipelineRef GRCCreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRIGraphicsPipelineRef handle;
            Drive()->GRICreateGraphicsPipeline(createInfo, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateGraphicsPipeline(createInfo);
    }

    GRIUniformBufferRef GRCCreateUniformBuffer(const UniformSlotList& contents,const char* ubName,UniformBufferUsageType ubType)
    {
        if(!CBQueue()->IsLowerVerion())
        {
            GRIUniformBufferRef handle;
            Drive()->GRICreateUniformBuffer(contents,ubName,ubType, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateUniformBuffer(contents,ubName,ubType);
    }
    
    GRIUniformBufferDescriptorRef GRCCreateUniformDescriptor(const UniformBufferList& ubl)
    {
        if(!CBQueue()->IsLowerVerion())
        {
            GRIUniformBufferDescriptorRef handle;
            Drive()->GRICreateUniformDescriptor(ubl, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateUniformDescriptor(ubl);
    }
    //Create Texture2D
    GRITexture2DRef GRCCreateTexture2D(uint32 sizex, uint32 sizey, PixelFormat format, uint32 numMips, uint32 numSamples, TextureUsageType usageType,ResourceData& rData)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRITexture2DRef handle;
            Drive()->GRICreateTexture2D(sizex, sizey, format, numMips, numSamples, usageType, rData, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateTexture2D(sizex, sizey, format, numMips, numSamples, usageType, rData);
    }
    //Texture2DArray
    GRITexture2DArrayRef GRCCreateTexture2DArray(uint32 sizex, uint32 sizey, uint32 sizez, PixelFormat format, uint32 numMips, uint32 numSamples, TextureUsageType usageType,ResourceData& rData)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRITexture2DArrayRef handle;
            Drive()->GRICreateTexture2DArray(sizex, sizey, sizez, format, numMips, numSamples, usageType, rData, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateTexture2DArray(sizex, sizey, sizez, format, numMips, numSamples, usageType, rData);
    }
    //Texture3D
    GRITexture3DRef GRCCreateTexture3D(uint32 sizex, uint32 sizey, uint32 sizez, PixelFormat format, uint32 numMips, TextureUsageType usageType, ResourceData& rData)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRITexture3DRef handle;
            Drive()->GRICreateTexture3D(sizex, sizey, sizez, format, numMips, usageType, rData, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateTexture3D(sizex, sizey, sizez, format, numMips, usageType, rData);
    }
    //TextureCube
    GRITextureCubeRef GRCCreateTextureCube(uint32 size, PixelFormat format, uint32 numMips, TextureUsageType usageType,ResourceData& rData)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRITextureCubeRef handle;
            Drive()->GRICreateTextureCube(size, format, numMips, usageType, rData, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateTextureCube(size, format, numMips, usageType, rData);
    }
    //SamplerState
    GRISamplerStateRef GRCCreateSampler(const SamplerState& sState)
    {
        if (!CBQueue()->IsLowerVerion())
        {
            GRISamplerStateRef handle;
            Drive()->GRICreateSampler(sState, handle);
            return handle;
        }
        return CBQueue()->GetLowerCommandBuffer()->CreateSampler(sState);
    }
}
