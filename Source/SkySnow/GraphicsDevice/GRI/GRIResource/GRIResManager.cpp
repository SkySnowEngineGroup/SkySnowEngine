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
#include "GRIResManager.h"
#include "GRIResource.h"
#include "RunnableThread.h"
namespace SkySnow
{
    GRIResManager& GRIResManager::Instance()
    {
        static GRIResManager instance;
        return instance;
    }

    void GRIResManager::RegisterResource(GRIResource* res)
    {
        _ResLock.Lock();
        auto iter = std::find(_GRIResList.begin(), _GRIResList.end(), res);
        if(iter == _GRIResList.end())
        {
            _GRIResList.emplace_back(res);
        }
        _ResLock.UnLock();
    }

    void GRIResManager::FlushResource()
    {
        _ResLock.Lock();
        if(IsInRenderThread())
        {
            for(int i = 0; i < _DeleteList.size(); i ++)
            {
                delete _DeleteList[i];
            }
            _DeleteList.clear();
        }
        _ResLock.Lock();
    }
    void GRIResManager::MoveToDelete(GRIResource* res)
    {
        _ResLock.Lock();
        auto iter = std::find(_GRIResList.begin(), _GRIResList.end(), res);
        if(iter != _GRIResList.end())
        {
            _GRIResList.erase(iter);
            _DeleteList.emplace_back(res);
        }
        _ResLock.UnLock();
    }
    void GRIResManager::ShutDown()
    {
        _ResLock.Lock();
        if(IsInRenderThread())
        {
            for(int i = 0; i < _DeleteList.size(); i ++)
            {
                delete _DeleteList[i];
            }
            _DeleteList.clear();
            for(int i = 0; i < _GRIResList.size(); i ++)
            {
                delete _GRIResList[i];
            }
            _GRIResList.clear();
        }
        _ResLock.UnLock();
    }
}
