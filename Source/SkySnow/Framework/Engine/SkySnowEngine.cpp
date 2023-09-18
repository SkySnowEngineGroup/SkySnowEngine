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
#include "SkySnowEngine.h"
#include "SkySnowProfiles.h"
namespace SkySnow
{
    SkySnowEngine::SkySnowEngine()
        : _GameWindow(nullptr)
        , _EditorWindow(nullptr)
    {
        
    }

    SkySnowEngine::~SkySnowEngine()
    {
        Delete_Object(_GameWindow);
        Delete_Object(_EditorWindow);
    }
    
    void SkySnowEngine::Init()
    {
        GRIInit();
    }

    void SkySnowEngine::ShutDown()
    {
        if (_GameWindow)
        {
            _GameWindow->ExitViewPort();
        }
        if (_EditorWindow)
        {
            _EditorWindow->ExitViewPort();
        }
        GRIExit();
        if (_GameWindow)
        {
            _GameWindow->ShutDown();
        }
        if (_EditorWindow)
        {
            _EditorWindow->ShutDown();
        }
    }
    EngineWindow* SkySnowEngine::CreateGameWindow(uint32 width, uint32 height)
    {
        _GameWindow = new EngineWindow(EGameWindow);
        _GameWindow->CreateEngineWindow(width, height);
        return _GameWindow;
    }

    EngineWindow* SkySnowEngine::CreateEditorWindow(uint32 width, uint32 height)
    {
        _EditorWindow = new EngineWindow(EEditorMainWindow);
        _EditorWindow->CreateEngineWindow(width, height, _GameWindow ? _GameWindow : nullptr);
        return _EditorWindow;
    }

    bool SkySnowEngine::IsEngineWindowClose()
    {
        return _EditorWindow ? _EditorWindow->GetOSWindow()->IsCloseWindow() : _GameWindow->GetOSWindow()->IsCloseWindow();
    }
}
