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
#include "SkySnowConfigInfo.h"
#include "GLCommandBuffer.h"
#include "WindowOSPlatform.h"
#include "AndroidOSPlatform.h"
#include "IOSOSPlatform.h"
#include "MacOSPlatform.h"
#include "LinuxOSPlatform.h"
#include "GRI.h"
#include "RenderRunnable.h"

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
        GRIFeature version = GRI->GetGRIFeatureType();
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
    GRICommandBufferQueue::GRICommandBufferQueue()
        : _LowerComBuf(nullptr)
        , _RenderRunnable(nullptr)
        , _RenderThread(nullptr)
    {
        _ComBufList.clear();
    }
    GRICommandBufferQueue::~GRICommandBufferQueue()
    {
        
    }
	void GRICommandBufferQueue::Init()
	{
        GRIFeature version = GRI->GetGRIFeatureType();
        switch (version)
        {
        case SkySnow::ENone:
            break;
        case SkySnow::EGLES:
        case SkySnow::EOpenGL:
            _LowerComBuf = new GLRenderCommandBuffer();
            _RenderRunnable = new RenderRunnable();
            _RenderThread = RunnableThread::Create(_RenderRunnable);
            break;
        default:
            break;
        }
	}
    
    void GRICommandBufferQueue::SubmitQueue(GRICommandBufferBase* comBuf)
    {
        _ComBufList.push_back(comBuf);
    }
    
    void GRICommandBufferQueue::BeginFrame()
    {
        if(_RenderRunnable)
        {
            _RenderRunnable->BeginFrame();
        }
    }

    void GRICommandBufferQueue::EndFrame()
    {
        if(_RenderRunnable)
        {
            _RenderRunnable->EndFrame();
        }
    }

    void GRICommandBufferQueue::FlushResource()
    {
        
    }
    void GRICommandBufferQueue::PresentQueue()
    {
        //TestCode Single MainThread Render Capacity
        //TestCode == Resource Create At Lower Api Version
        GRI->GRIBeginViewport();
        _LowerComBuf->ResourceCreateExecutor();
        //TestCode == Resource Set At Lower Api Version,At Height Api Version Use Self CommandBuffer
        for (int i = 0; i < _ComBufList.size(); i ++)
        {
            GRICommandBufferBase* cmb = _ComBufList[i];
            cmb->CmdResourceSetExecutor();
        }
        _ComBufList.clear();
    }
    bool GRICommandBufferQueue::IsLowerVerion()
    {
        GRIFeature version = GRI->GetGRIFeatureType();
        if (version == EVulkan ||
            version == EMetal  ||
            version == EDX12)
        {
            return false;
        }
        return true;
    }
    
    GRILowerCommandBuffer* GRICommandBufferQueue::GetLowerCommandBuffer()
    {
        return _LowerComBuf;
    }

    //GRI Globle Create Resource Interface
    //================================================================================================
    GRIVertexShaderRef CreateVertexShader(const char* vsCode)
    {
        if (!_GQueue->IsLowerVerion())
        {
            GRIVertexShaderRef handle;
            GRI->GRICreateVertexShader(vsCode, handle);
            return handle;
        }
        return _GQueue->GetLowerCommandBuffer()->CreateVertexShader(vsCode);
    }

    GRIFragmentShaderRef CreateFragmentShader(const char* fsCode)
    {
        if (!_GQueue->IsLowerVerion())
        {
            GRIFragmentShaderRef handle;
            GRI->GRICreateFragmentShader(fsCode, handle);
            return handle;
        }
        return _GQueue->GetLowerCommandBuffer()->CreateFragmentShader(fsCode);
    }

    GRIPipelineShaderRef CreatePipelineShader(GRIVertexShader* vs, GRIFragmentShader* fs)
    {
        if (!_GQueue->IsLowerVerion())
        {
            GRIPipelineShaderRef handle;
            GRI->GRICreatePipelineShader(handle);
            return handle;
        }
        return _GQueue->GetLowerCommandBuffer()->CreatePipelineShader(vs,fs);
    }

    GRIBufferRef CreateBuffer(BufferUsageType usageType, int size, int stride, void* data)
    {
        if (!_GQueue->IsLowerVerion())
        {
            GRIBufferRef handle;
            GRI->GRICreateBuffer(usageType,size,stride,data, handle);
            return handle;
        }
        return _GQueue->GetLowerCommandBuffer()->CreateBuffer(usageType, size, stride, data);
    }

    GRIGraphicsPipelineRef CreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo)
    {
        if (!_GQueue->IsLowerVerion())
        {
            GRIGraphicsPipelineRef handle;
            GRI->GRICreateGraphicsPipeline(createInfo, handle);
            return handle;
        }
        return _GQueue->GetLowerCommandBuffer()->CreateGraphicsPipeline(createInfo);
    }
}
