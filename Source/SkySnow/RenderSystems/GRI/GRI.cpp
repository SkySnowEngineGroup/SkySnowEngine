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
#include "GRI.h"
#include "GRICommandBuffer.h"
namespace SkySnow
{
    //Globle Member Variable
    GRICommandBufferQueue*  _GQueue = nullptr;
    OSPlatform*             _GOSPlatform = nullptr;
    OSPlatformInfo*         _GOSPlatformInfo = nullptr;
    GRIDrive*               GRI = nullptr;
    //Globle Member Function
    void GRIInit(const OSPlatformInfo& osPlatformInfo)
    {
        if(!_GOSPlatform)
        {
            _GOSPlatformInfo = new OSPlatformInfo();
            _GOSPlatformInfo->_NativeWindow = osPlatformInfo._NativeWindow;
            _GOSPlatformInfo->_DriveContext = osPlatformInfo._DriveContext;
            _GOSPlatform = CreateTargetOSPlatform();
            GRI = _GOSPlatform->OSPlatformCreateGRI();
            GRI->Init();
    //          _GQueue = new GRICommandBufferQueue();
    //          _GQueue->Init();
        }
        
    }
    void GRISwapTemp()
    {
        GRI->SwapTemp();
    }
    void GRIExit()
    {
        GRI->Exit();
    //      Delete_Object(_GQueue);
        Delete_Object(_GOSPlatform);
        Delete_Object(_GOSPlatformInfo);
    }
}
