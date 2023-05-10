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
#include "RenderSystem.h"
#include "Context.h"
#include "SceneRenderer.h"
#include "GRIResourceCreateInfo.h"
namespace SkySnow
{
    RenderSystem::RenderSystem()
    {
        
    }

    RenderSystem::~RenderSystem()
    {
        
    }

    void RenderSystem::PreUpdate()
    {
        
    }

    void RenderSystem::Update()
    {
        Context::Instance().GetSceneRenderer()->UpdateAllRenderers();
        
        if(!_TestInit)
        {
            _CMBPool = new GRICommandBufferPool();
            
            string vsShaderPath = GetMaterialAllPath("Test/BaseVertex.sns");
            string fsShaderPath = GetMaterialAllPath("Test/BaseFragment.sns");
            _File = new File();
            _VsData = new Data();
            _FsData = new Data();
            _File->ReadData(vsShaderPath, _VsData);
            _File->ReadData(fsShaderPath, _FsData);

            _vsRef = CreateVertexShader((char*)_VsData->GetBytes());
            _fsRef = CreateFragmentShader((char*)_FsData->GetBytes());
            _PipelineShaderRef = CreatePipelineShader(_vsRef, _fsRef);
            static float vertices[] = { -0.5f, -0.5f, 0.0f,
                                        0.5f,  -0.5f, 0.0f,
                                        0.0f,  0.5f,  0.0f};
            SN_LOG("Vertex Size:%d",sizeof(vertices));
            _VertexBufferRef = CreateBuffer(BufferUsageType::BUT_VertexBuffer,
                                                    sizeof(vertices),
                                                    3,
                                                    vertices);
            static float colors[] = { 1.0f, 0.0f, 0.0f, 1.0,
                                      0.0f, 1.0f, 0.0f, 1.0f,
                                      0.0f, 0.0f, 1.0f, 1.0f};
            _ColorBufferRef = CreateBuffer(BufferUsageType::BUT_VertexBuffer,
                                           sizeof(colors),
                                           4,
                                           colors);
            VertexDeclarationElementList elementList;
            elementList.push_back(GRIVertexElement(0,_VertexBufferRef,0,3,0,VertexElementType::VET_Float3));
            elementList.push_back(GRIVertexElement(1,_ColorBufferRef,1,4,0,VertexElementType::VET_Float4));
            _VertexDeclaration = CreateVertexDeclaration(elementList);
            
            GRICreateGraphicsPipelineInfo psoCreateInfo;
            psoCreateInfo._PrimitiveType = PrimitiveType::PT_Trangles;
            psoCreateInfo._ShaderPipelineInfo._PipelineShader = _PipelineShaderRef;
            psoCreateInfo._ShaderPipelineInfo._VertexDeclaration = _VertexDeclaration;
            _PSORef = CreateGraphicsPipeline(psoCreateInfo);
            _TestInit = true;
        }
        
        GRIRenderCommandBuffer* commandBuffer = (GRIRenderCommandBuffer*)_CMBPool->AllocCommandBuffer();
        
        commandBuffer->CmdBeginViewport();
        commandBuffer->CmdSetGraphicsPipeline(_PSORef);
        
//        commandBuffer->CmdSetBuffer(0,_VertexBufferRef,0);
//        commandBuffer->CmdSetPipelineShader(_PipelineShaderRef);
        
        commandBuffer->CmdDrawPrimitive(1,1);
        
        commandBuffer->CmdEndViewport();
        
        _GQueue->SubmitQueue(commandBuffer);
    }

    void RenderSystem::PostUpdate()
    {
        
    }
    
    void RenderSystem::ShutDown()
    {
        
    }
}
