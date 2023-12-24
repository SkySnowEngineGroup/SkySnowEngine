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
#include "RendererScene.h"
#include "LogAssert.h"
#include "Renderable.h"
#include "RenderRenderable.h"
#include "RenderableProxy.h"
#include "SPtr.h"
#include "StaticMesh.h"
#include "Context.h"
namespace SkySnow
{
    RendererScene::RendererScene()
    {
        
    }

    RendererScene::~RendererScene()
    {
        
    }

    void RendererScene::NotifyRenderableAdded(RenderableProxy* renderable)
    {
        auto renderElement = CreateSPtr<RenderRenderable>(renderable);
        _RSceneInfo._RenderRenderables.push_back(renderElement);
    }
    void RendererScene::NotifyRenderableUpdate(RenderableProxy* renderable)
    {
        
    }
    void RendererScene::NotifyRenderableRemoved(RenderableProxy* renderable)
    {
        for(auto iter = _RSceneInfo._RenderRenderables.begin();iter != _RSceneInfo._RenderRenderables.end();)
        {
            if((*iter)->IsEqual(renderable))
            {
                iter = _RSceneInfo._RenderRenderables.erase(iter);
            }
            else
            {
                iter ++;
            }
        }
    }
    void RendererScene::NotifyCameraAdded(CameraProxy* camera)
    {
        if(!_RSceneInfo._RenderViewFamily)
        {
            _RSceneInfo._RenderViewFamily = CreateSPtr<RenderViewFamily>();
        }
        _RSceneInfo._RenderViewFamily->AddRenderView(camera);
    }
    void RendererScene::NotifyCameraUpdate(CameraProxy* camera)
    {
        
    }
    void RendererScene::NotifyCameraRemoved(CameraProxy* camera)
    {
        _RSceneInfo._RenderViewFamily->RemoveRenderView(camera);
    }

    void RendererScene::RenderCore()
    {
        //temp code
        if (!_CMBPool)
        {
            _CMBPool = new GRICommandBufferPool();
        }
        GRIRenderCommandBuffer* commandBuffer = (GRIRenderCommandBuffer*)_CMBPool->AllocCommandBuffer();
        SkySnowEngine* engine = SSContext().GetSkySnowEngine();
        GRIViewportStateRef viewport = engine->GetEngineWindow(EGameWindow)->GetViewport()->GetGRIViewport();
        
        GRITexture2DRef tex2DGRI;
        commandBuffer->CmdBeginViewport(viewport,tex2DGRI);
        
        for(int i = 0; i < _RSceneInfo._RenderRenderables.size(); i ++)
        {
            SPtr<RenderRenderable> render = _RSceneInfo._RenderRenderables[i];
            auto renderable = render->_RenderableProxy->GetRenderable();
            
            auto mesh = std::static_pointer_cast<StaticMesh>(renderable->GetShareMesh());
            auto matList = renderable->GetMaterials();

            for (int i = 0; i < matList.size(); i ++)
            {
                auto mat = matList[i];
                if (!_PSORef)
                {
                    SamplerState samplerState;
                    _Sampler = GRCCreateSampler(samplerState);
                    mesh->CreateMeshBuffer();
                    
                    GRICreateGraphicsPipelineInfo psoCreateInfo;
                    psoCreateInfo._PrimitiveType = PrimitiveType::PT_Trangles;
                    psoCreateInfo._ShaderPipelineInfo._PipelineShader = mat->GetPShader();
                    psoCreateInfo._ShaderPipelineInfo._VertexDescriptor = mesh->GetMeshBuffer()->GetVertexDesc();
                    psoCreateInfo._ShaderPipelineInfo._Textures[0] = mat->GetTexture("panda.png")->GetTexture();
                    psoCreateInfo._ShaderPipelineInfo._Samplers[0] = _Sampler;
                    _PSORef = GRCCreateGraphicsPipeline(psoCreateInfo);
                }
            }
            commandBuffer->CmdSetGraphicsPipeline(_PSORef);
            
            commandBuffer->CmdDrawPrimitive(2, 1);
        }
        
        commandBuffer->CmdEndViewport(viewport,false,false);

        _GQueue->SubmitCommandBuffer(commandBuffer);
    }
}
