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
#pragma once
#include "SkySnowProfiles.h"
#include "OSWindow.h"
#include "Viewport.h"
namespace SkySnow
{
    enum EngineWindowType
    {
        EGameWindow = 0,
        EEditorMainWindow = 1
    };
	class EngineWindow
	{
	public:
        EngineWindow(EngineWindowType windowType)
            : _EngineWindowType(windowType)
            , _OSWindow(nullptr)
            , _Viewport(nullptr)
        {}

        virtual ~EngineWindow();
	public:
        void CreateEngineWindow(uint32 width,uint32 height, std::string windowName = "",EngineWindow* shareWindow = nullptr);

        OSWindow* GetOSWindow() const { return _OSWindow; }

        Viewport* GetViewport() const { return _Viewport; }

        EngineWindowType GetEngineWindowType() const {return _EngineWindowType;}

        void ExitViewPort();

        void ShutDown();
    private:
        EngineWindowType    _EngineWindowType;
        OSWindow*           _OSWindow;
        Viewport*           _Viewport;
	};
    /*
     * WindowA
     *      Scene
     *          RenderSystem
     *              BeginRenderPassA_A
     *                  DrawCall(0-5)
     *              EndRenderPassA_A
     *              BeginRenderPassA_B
     *                  DrawCall(6-10)
     *              EndRenderPassA_B
     *          BeginViewport
     *              DrawCall(RTA_B)
     *          EndViewport
     * WindowB
     *      Scene
     *          RenderSystem
     *              BeginRenderPassB_A
     *                  DrawCall(0-5)
     *              EndRenderPassB_A
     *              BeginRenderPassB_B
     *                  DrawCall(6-10)
     *              EndRenderPassB_B
     *          BeginViewport
     *              DrawCall(RTB_B)
     *          EndViewport
     */
}
