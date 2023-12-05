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
#include "Framework.h"
#include "Context.h"
#include "GLFWWindow.h"
#include <string>
#include "ModuleHeaders.h"

namespace SkySnow
{
    Framework::Framework()
    {

    }
    Framework::~Framework()
    {
    }

    void Framework::Init()
    {
        SSContext().RegisterModule<TimeModule>();         //Register TimeModule
        SSContext().RegisterModule<BehaviourModule>();    //Register BehaviourModule
        SSContext().RegisterModule<ResourceModule>();     //Register ResourceModule
        SSContext().RegisterModule<RenderModule>();       //Register RenderModule
    }
    void Framework::MainUpdate()
    {
        //SN_LOG("MainUpdate----------------");
        //-----ResourceSystem   ---load asyn
        //-----CullingSystem    ---Cull Scene(Octree,BSP,LOD)
        //-----EventSystem      ---BoardCast Result Event(Input Output)
        SSContext().GetModule<ResourceModule>()->PreUpdate();
        
        SSContext().GetModule<RenderModule>()->PreUpdate();
        
        SSContext().GetModule<ResourceModule>()->Update();
        SSContext().GetModule<ResourceModule>()->PostUpdate();

        
        SSContext().GetModule<RenderModule>()->Update();
        SSContext().GetModule<RenderModule>()->PostUpdate();
    }

    void Framework::ShutDown()
    {
        SSContext().GetModule<TimeModule>()->ShutDown();
        SSContext().GetModule<BehaviourModule>()->ShutDown();
        SSContext().GetModule<RenderModule>()->ShutDown();
        SSContext().GetModule<ResourceModule>()->ShutDown();
        SSContext().RemoveModule<RenderModule>();
        SSContext().RemoveModule<ResourceModule>();
    }
}
