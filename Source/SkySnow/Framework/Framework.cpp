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
#include "Framework.h"
#include "Context.h"
#include "GLFWWindow.h"
#include <string>

namespace SkySnow
{
    Framework::Framework()
        : _RenderSystem(nullptr)
    {

    }
    Framework::~Framework()
    {
        Context::Instance().RemoveSystem<RenderSystem>();
    }

    void Framework::Init(FrameworkInfo& frameInfo)
    {
        //init gri
        GRIInit(frameInfo._OSPlatformInfo);
        
        _CMBPool = new GRICommandBufferPool();
        Context::Instance().RegisterSystem<RenderSystem>();
        _RenderSystem = Context::Instance().GetSystem<RenderSystem>();
    }
    void Framework::MainUpdate()
    {
        _GQueue->BeginFrame();
        SN_LOG("MainUpdate----------------");
        _RenderSystem->PreUpdate();
        _RenderSystem->Update();
        _RenderSystem->PostUpdate();
        
        //------testcode start
        if(!_TestInit)
        {
            string vsShaderPath = GetMaterialAllPath("Test/BaseVertex.sns");
            string fsShaderPath = GetMaterialAllPath("Test/BaseFragment.sns");
            _File = new File();
            _VsData = new Data();
            _FsData = new Data();
            _File->ReadData(vsShaderPath, _VsData);
            _File->ReadData(fsShaderPath, _FsData);

            _vsRef = CreateVertexShader((char*)_VsData->GetBytes());
            _fsRef = CreateFragmentShader((char*)_FsData->GetBytes());
            _PipelineShaderStateRef = CreatePipelineShaderState(_vsRef, _fsRef);
            static float vertices[] = { -0.5f, -0.5f, 0.0f,
                                 0.5f,  -0.5f, 0.0f,
                                 0.0f,  0.5f,  0.0f};
            SN_LOG("Vertex Size:%d",sizeof(vertices));
            _VertexBufferRef = CreateBuffer(BufferUsageType::BUT_VertexBuffer,
                                                    sizeof(vertices),
                                                    3,
                                                    vertices);

            GRICreateGraphicsPipelineStateInfo psoCreateInfo;
            psoCreateInfo._PrimitiveType = PrimitiveType::PT_Trangles;
            _PSORef = CreateGraphicsPipelineState(psoCreateInfo);
            _TestInit = true;
        }
        
        GRIRenderCommandBuffer* commandBuffer = (GRIRenderCommandBuffer*)_CMBPool->AllocCommandBuffer();
        
        commandBuffer->CmdBeginViewport();
        
        commandBuffer->CmdSetBuffer(0,_VertexBufferRef,0);
        commandBuffer->CmdSetPipelineShaderState(_PipelineShaderStateRef);
        commandBuffer->CmdSetGraphicsPipelineState(_PSORef);
        commandBuffer->CmdDrawPrimitive(1,1);
        
        commandBuffer->CmdEndViewport();
        
        _GQueue->SubmitQueue(commandBuffer);
        //------testcode end
        _GQueue->EndFrame();
    }

    void Framework::Stop()
    {
        GRIExit();
    }

    void Framework::Exit()
    {

    }
}
