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
#include "Hash.h"
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
            
            
            //Create UniformBuffer
            float uColor[] = {0,1,0,0};
            float uColor2[] = {1.0,0,0,0};
            UniformBufferSlot ubSlot1("TestUniformBlock",UniformBufferUsageType::UBT_MultiFrame);
            ubSlot1.AddUniformSlot("uColor", uColor, 4 * sizeof(float));
            ubSlot1.AddUniformSlot("uColor2", uColor2, 4 * sizeof(float));
            _UBO_Md = CreateUniformBuffer(ubSlot1);
            
            //Create Uniform Array
            float test1[] = {0.5,0,0,0};
            float test2[] = {0,0.5,0,0};
            float test3[] = {0,0,0.5,0};
            UniformBufferSlot ubSlot2("UniformArray",UniformBufferUsageType::UBT_UV_SingleDraw);
            ubSlot2.AddUniformSlot("test1", test1, 4 * sizeof(float));
            ubSlot2.AddUniformSlot("test2", test2, 4 * sizeof(float));
            ubSlot2.AddUniformSlot("test3", test3, 4 * sizeof(float));
            _UBO_Sd = CreateUniformBuffer(ubSlot2);
            
            GRICreateUniformBufferDescriptorInfo descInfo;
            descInfo.AddUniformBuffer(0, "UniformArray", UniformBufferUsageType::UBT_UV_SingleDraw,_UBO_Sd);
            descInfo.AddUniformBuffer(1, "TestUniformBlock", UniformBufferUsageType::UBT_MultiFrame,_UBO_Md);
            _UBODesc = CreateUniformDescriptor(descInfo);
            
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
            VertexDescriptorElementList elementList;
            //bufferindex attritubeindex stride offset
            elementList.push_back(GRIVertexElement(0,0,3,0,VertexElementType::VET_Float3,_VertexBufferRef));
            elementList.push_back(GRIVertexElement(1,1,4,0,VertexElementType::VET_Float4,_ColorBufferRef));
            _VertexDescriptor = CreateVertexDescriptor(elementList);
            
//            _PipelineShaderRef = CreatePipelineShader(_vsRef, _fsRef,_VertexDeclaration);
            
            GRICreateGraphicsPipelineInfo psoCreateInfo;
            psoCreateInfo._PrimitiveType = PrimitiveType::PT_Trangles;
            psoCreateInfo._ShaderPipelineInfo._PipelineShader = _PipelineShaderRef;
            psoCreateInfo._ShaderPipelineInfo._VertexDescriptor = _VertexDescriptor;
            psoCreateInfo._ShaderPipelineInfo._UniformBufferDescriptor = _UBODesc;
            _PSORef = CreateGraphicsPipeline(psoCreateInfo);
            _TestInit = true;
            
            /*std::string test = "UniformBuffer_0";
            size_t hash = String2Hash(test);
            std::string test2 = "UniformBuffer_0";
            size_t hash2 = String2Hash(test2);
            SN_LOG("hash:%zu  hash2:%ld",hash,hash2);*/
            std::string ubn = "TestUniformBlock";
            SN_LOG("TestUniformBlock HashKey:%ld", String2Hash(ubn));
            //UniformBufferSlot ubSlot;
            
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
