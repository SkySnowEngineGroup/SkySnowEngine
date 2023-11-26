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
#include "Context.h"
#include "SceneRenderer.h"
namespace SkySnow
{
    Context::Context()
        : _SceneRenderer(nullptr)
    {
        _Modules.clear();
    }
    Context::~Context()
    {
        RemoveSceneRenderer();
        for (auto entry : _Modules)
        {
            delete entry;
        }
        _Modules.clear();
    }
    Context& Context::Instance()
    {
        static Context instance;
        return instance;
    }
    
    SceneRenderer* Context::RegisterSceneRenderer()
    {
        if(_SceneRenderer == nullptr)
        {
            _SceneRenderer = new SceneRenderer();
        }
        return _SceneRenderer;
    }

    SceneRenderer* Context::GetSceneRenderer()
    {
        if(_SceneRenderer == nullptr)
        {
            RegisterSceneRenderer();
        }
        return _SceneRenderer;
    }
    
    void Context::RemoveSceneRenderer()
    {
        if(_SceneRenderer)
        {
            delete _SceneRenderer;
            _SceneRenderer = nullptr;
        }
    }
}
