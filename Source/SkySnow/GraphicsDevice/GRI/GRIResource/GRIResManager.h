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
#include <vector>
#include "ThreadMutex.h"
#include "NonCopyable.h"
#include "RefCounted.h"
namespace SkySnow
{
    class GRIResource;
    class GRIResManager : public NonCopyable
    {
    public:
        static GRIResManager& Instance();
        //GRI resources are registered with the administrator at the time of creation
        void RegisterResource(GRIResource* res);
        //
        void MoveToDelete(GRIResource* res);
        //At the beginning of each frame, the GRI resources that are not in use are cleared
        void FlushResource();
        //All GRI resources are reclaimed when GRI stops
        //If OpenGL&ES is called in the RenderThread thread, Meta/Vulkan/Dx12 can be called in the main thread
        void ShutDown();
    private:
        GRIResManager(){}
        ~GRIResManager(){}
    private:
        ThreadMutex                 _ResLock;
        std::vector<GRIResource*>   _GRIResList;
        std::vector<GRIResource*>   _DeleteList;
    };
}
