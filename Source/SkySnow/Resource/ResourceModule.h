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
#include "IModule.h"
#include <vector>
#include <map>
#include <unordered_map>
#include "IRSEntity.h"

namespace SkySnow
{
class IResSource;
class IResRender;
    class ResourceModule : public IModule
    {
        SkySnow_Object(ResourceModule, IModule);
    public:
        ResourceModule();
        virtual ~ResourceModule();

        virtual void StartUp() final override;

        virtual void Update() final override;

        virtual void ShutDown() final override;
        
        void LoadAsync();
        void LoadSync();
        
        template<typename T> SPtr<T> CreateRSEntity();
        template<typename T> SPtr<T> GetRSEntity(int64 uuid);
        
        void RemoveRSEntity(int64 uuid);
    private:
        std::map<int64,SPtr<IRSEntity<IResSource,IResRender>>> _RSEnMaps;
    };

    template<typename T>
    SPtr<T> ResourceModule::CreateRSEntity()
    {
        SPtr<T> entity = CreateSPtr<T>();
        return entity;
    }

    ResourceModule* ResourceSystem();
}
