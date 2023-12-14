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
#include "RenderModule.h"
#include "Context.h"
#include "RendererScene.h"
#include "GRIResourceCreateInfo.h"
#include "HashUtil.h"
#include "StbImageLoad.h"
#include "SkySnowEngine.h"
#include "TextureLoader.h"
#include "RendererScene.h"
namespace SkySnow
{
    RenderModule::RenderModule()
    {
        
    }

    RenderModule::~RenderModule()
    {
        SN_LOG("RenderModule DesConstruct.");
    }

    void RenderModule::StartUp()
    {

    }

    void RenderModule::Update()
    {
        RenderInternal();
    }
    void RenderModule::RenderInternal()
    {
        for(const auto& pair : _RendererScenes)
        {
            pair.second->RenderCore();
        }
        TempCode();//
    }
    //Call from SceneManager
    RendererScene* RenderModule::NotifyCreateRendererScene(SceneHandle sceneHandle)
    {
        _RendererScenes[sceneHandle] = new RendererScene();
        return _RendererScenes[sceneHandle];
    }
    //Call from SceneManager
    void RenderModule::NotifyRemoveRendererScene(SceneHandle sceneHandle)
    {
        auto iter = _RendererScenes.find(sceneHandle);
        if(iter != _RendererScenes.end())
        {
            delete iter->second;
            _RendererScenes.erase(iter);
        }
    }
    RendererScene* RenderModule::GetRendererScene(SceneHandle sceneHandle)
    {
        auto iter = _RendererScenes.find(sceneHandle);
        if(iter != _RendererScenes.end())
        {
            return _RendererScenes[sceneHandle];
        }
        SN_WARN("Not find this SceneHandle(%d) RendererScene.",sceneHandle);
        return nullptr;
    }
    void RenderModule::ShutDown()
    {
        for (auto& pair : _RendererScenes)
        {
            delete pair.second; // 删除指针指向的对象
        }
        _RendererScenes.clear();
        SN_LOG("RenderModule ShutDown.");
    }



//直接使用RHI代码，临时放到这里。后面作为一个RHI使用示范
void RenderModule::TempCode()
{
    if (!_CMBPool)
    {
        _CMBPool = new GRICommandBufferPool();
    }
    GRIRenderCommandBuffer* commandBuffer = (GRIRenderCommandBuffer*)_CMBPool->AllocCommandBuffer();
    SkySnowEngine* engine = Context::Instance().GetSkySnowEngine();
    GRIViewportStateRef viewport = engine->GetEngineWindow(EGameWindow)->GetViewport()->GetGRIViewport();
    if(!_TestInit)
    {
        string vsShaderPath = GetMaterialAllPath("Test/BaseVertex.sns");
        string fsShaderPath = GetMaterialAllPath("Test/BaseFragment.sns");
        _File = new File();
        _VsData = new Data();
        _FsData = new Data();
        //TODO Shader SourceData Manage
        _File->ReadData(vsShaderPath, _VsData);
        _File->ReadData(fsShaderPath, _FsData);
        //Create VS And PS
        ResourceData vsRD;
        vsRD.MakeCopy(_VsData->GetBytes(), (int32)_VsData->GetSize());
        _vsRef = CreateVertexShader(vsRD);
        ResourceData fsRD;
        fsRD.MakeCopy(_FsData->GetBytes(), (int32)_FsData->GetSize());
        _fsRef = CreateFragmentShader(fsRD);
        //Create ShaderPipeline
        _PipelineShaderRef = CreatePipelineShader(_vsRef, _fsRef);
        
        //Create Texture
        string imagePath = GetImageAllPath("panda.png");
        TextureLoader* tImp = new TextureLoader();
        TextureStream* texStream = tImp->Load<TextureStream>(imagePath);
        ResourceData texRD;
        texRD.MakeCopy(texStream->GetImageData(), texStream->GetImageSize());

        uint64 tut = (uint64)TextureUsageType::TUT_ShaderResource | (uint64)TextureUsageType::TUT_None;
        _Tex2D = CreateTexture2D(texStream->GetImageWidth(),
                                 texStream->GetImageHeight(),
                                 texStream->GetPixelFormat(),
                                 1, 1,
                                 (TextureUsageType)tut,
                                 texRD);
        Delete_Object(texStream);
        Delete_Object(tImp);
        //Create Sampler
        SamplerState samplerState;
        _Sampler = CreateSampler(samplerState);
        //Create UniformBuffer
        //TODO UniformBuffer SourceData Manage
        float uColor[]{0,1,0,0};
        float uColor2[]{1,0,0,0};
        UniformSlotList uSlot1;
        uSlot1.push_back(UniformSlot("uColor", uColor, 4 * sizeof(float)));
        uSlot1.push_back(UniformSlot("uColor2", uColor2, 4 * sizeof(float)));
        _UBO_Md = CreateUniformBuffer(uSlot1,"TestUniformBlock",UniformBufferUsageType::UBT_MultiFrame);
        
        //Create Uniform Array
        //TODO UniformBuffer SourceData Manage
        float test1[]{1,0,0,0};
        float test2[]{0,1,0,0};
        float test3[]{0,0,1,0};
        UniformSlotList uSlot2;
        uSlot2.push_back(UniformSlot("test1", test1, 4 * sizeof(float)));
        uSlot2.push_back(UniformSlot("test2", test2, 4 * sizeof(float)));
        uSlot2.push_back(UniformSlot("test3", test3, 4 * sizeof(float)));
        _UBO_Sd = CreateUniformBuffer(uSlot2,"UniformArray",UniformBufferUsageType::UBT_UV_SingleDraw);
        
        UniformBufferList ubSlot;
        ubSlot.push_back(UniformBufferSlot(0, "UniformArray",UniformBufferUsageType::UBT_UV_SingleDraw,_UBO_Sd));
        ubSlot.push_back(UniformBufferSlot(1, "TestUniformBlock",UniformBufferUsageType::UBT_MultiFrame,_UBO_Md));
        _UBODesc = CreateUniformDescriptor(ubSlot);
        
        //TODO UniformBuffer SourceData Manage
        float vertices[]{ -0.5f, -0.5f,0.0f,
                          0.5f,  0.5f, 0.0f,
                          -0.5f, 0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                          0.5f, -0.5f, 0.0f,
                          0.5f, 0.5f, 0.0f};
        ResourceData vexRD;
        vexRD.MakeCopy(vertices, 18 * sizeof(float));
        _VertexBufferRef = CreateBuffer(BufferUsageType::BUT_VertexBuffer,
                                        18 * sizeof(float),
                                        3,
                                        vexRD);
        //TODO UniformBuffer SourceData Manage
        float colors[]{ 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,
                        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,1.0f,
                        0.0f, 0.0f, 1.0f, 1.0f, 0.0f,1.0f,
                        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,
                        0.0f, 1.0f, 1.0f, 1.0f, 1.0f,0.0f,
                        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,1.0f};
        ResourceData colRD;
        colRD.MakeCopy(colors, 36 * sizeof(float));
        _ColorBufferRef = CreateBuffer(BufferUsageType::BUT_VertexBuffer,
                                       36 * sizeof(float),
                                       6,
                                       colRD);
        VertexElementList veList;
        //bufferindex attritubeindex stride offset
        veList.push_back(VertexElementSlot(0,0,3,0,VertexElementType::VET_Float3,_VertexBufferRef));
        veList.push_back(VertexElementSlot(1,1,6,0,VertexElementType::VET_Float4,_ColorBufferRef));
        veList.push_back(VertexElementSlot(1,2,6,16,VertexElementType::VET_Float2,_ColorBufferRef));
        _VertexDescriptor = CreateVertexDescriptor(veList);
        //Consider: Need?
//            _PipelineShaderRef = CreatePipelineShader(_vsRef, _fsRef,_VertexDeclaration);
        
        GRICreateGraphicsPipelineInfo psoCreateInfo;
        psoCreateInfo._PrimitiveType = PrimitiveType::PT_Trangles;
        psoCreateInfo._ShaderPipelineInfo._PipelineShader = _PipelineShaderRef;
        psoCreateInfo._ShaderPipelineInfo._VertexDescriptor = _VertexDescriptor;
        psoCreateInfo._ShaderPipelineInfo._UniformBufferDescriptor = _UBODesc;
        psoCreateInfo._ShaderPipelineInfo._Textures[0] = _Tex2D;
        psoCreateInfo._ShaderPipelineInfo._Samplers[0] = _Sampler;
        _PSORef = CreateGraphicsPipeline(psoCreateInfo);
        SN_LOG("_PipelineShaderRef Count:%d",_PipelineShaderRef.GetRefCount());
        _TestInit = true;
    }
    commandBuffer->CmdBeginViewport(viewport, _Tex2D);
//        SN_LOG("_PipelineShaderRef Start Count:%d",_PipelineShaderRef.GetRefCount());

    //commandBuffer->CmdSetShaderTexture(_PipelineShaderRef, _Tex2D, 0);
    //commandBuffer->CmdSetShaderSampler(_PipelineShaderRef, _Sampler, 0);
    commandBuffer->CmdSetGraphicsPipeline(_PSORef);
    
//        commandBuffer->CmdSetBuffer(0,_VertexBufferRef,0);
//        commandBuffer->CmdSetPipelineShader(_PipelineShaderRef);
    
    commandBuffer->CmdDrawPrimitive(2, 1);
    
//        SN_LOG("_PipelineShaderRef Count:%d",_PipelineShaderRef.GetRefCount());
//        SN_LOG("_PSORef Count:%d",_PSORef.GetRefCount());
    commandBuffer->CmdEndViewport(viewport,false,false);
    
    _GQueue->SubmitCommandBuffer(commandBuffer);
//        SN_LOG("_PipelineShaderRef End Count:%d",_PipelineShaderRef.GetRefCount());
//        SN_LOG("_PSORef Count:%d",_PSORef.GetRefCount());
}
}
