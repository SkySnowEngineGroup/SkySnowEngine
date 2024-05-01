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

    RenderModule* RenderSystem()
    {
        return SSContext().GetModule<RenderModule>();
    }
}
