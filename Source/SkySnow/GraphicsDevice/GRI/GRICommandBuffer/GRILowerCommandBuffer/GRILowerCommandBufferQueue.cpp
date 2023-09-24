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
#include "GRILowerCommandBufferQueue.h"
#include "GLCommandBuffer.h"
#include "RenderRunnable.h"
namespace SkySnow
{
    GRILowerCommandBufferQueue::GRILowerCommandBufferQueue()
        : _MainCreatCB(nullptr)
        , _RenderCreateCB(nullptr)
        , _RenderRunnable(nullptr)
        , _RenderThread(nullptr)
    {
    }

    GRILowerCommandBufferQueue::~GRILowerCommandBufferQueue()
    {
        Delete_Object(_MainCreatCB);
        Delete_Object(_RenderCreateCB);
        //Delete_Object(_RenderThread);
        //Delete_Object(_RenderRunnable);
        _MainCBList.clear();
        _RenderCBList.clear();
    }

    void GRILowerCommandBufferQueue::Init()
    {
        _MainCreatCB = new GLCreateCommandBuffer();
        _RenderCreateCB = new GLCreateCommandBuffer();
        _RenderRunnable = new RenderRunnable();
        _RenderThread = RunnableThread::Create(_RenderRunnable);
    }
    void GRILowerCommandBufferQueue::SubmitCommandBuffer(GRICommandBufferBase* comBuf)
    {
        _SubmitLock.Lock();
        _MainCBList.emplace_back(comBuf);
        _SubmitLock.UnLock();
    }

    void GRILowerCommandBufferQueue::BeginFrame()
    {
        if(_RenderRunnable)
        {
            _RenderRunnable->BeginFrame();
        }
    }

    void GRILowerCommandBufferQueue::EndFrame()
    {
        if(_RenderRunnable)
        {
            _RenderRunnable->EndFrame();
            
            //Swap Create CommandBuffer
            GLCreateCommandBuffer* temp = _MainCreatCB;
            _MainCreatCB = _RenderCreateCB;
            _RenderCreateCB = temp;
            //Swap MainCBList with RenderCBList
            for(int i = 0; i < _MainCBList.size(); i++)
            {
                _RenderCBList.emplace_back(_MainCBList[i]);
            }
            _MainCBList.clear();
        }
    }
    
    GRICreateCommandBuffer* GRILowerCommandBufferQueue::GetLowerCommandBuffer()
    {
        return _MainCreatCB;
    }

    void GRILowerCommandBufferQueue::WaitforRenderThreadExit()
    {
        if(_RenderRunnable)
        {
            _RenderRunnable->WaitForRenderThread();
        }
    }

    void GRILowerCommandBufferQueue::PresentQueue()
    {
        //TestCode Single MainThread Render Capacity
        //TestCode == Resource Create At Lower Api Version
        _RenderCreateCB->ResourceCreateExecutor();
        //TestCode == Resource Set At Lower Api Version,At Height Api Version Use Self CommandBuffer
        for (int i = 0; i < _RenderCBList.size(); i ++)
        {
            GRICommandBufferBase* cmb = _RenderCBList[i];
            cmb->CmdResourceSetExecutor();
        }
        _RenderCBList.clear();
    }
}
