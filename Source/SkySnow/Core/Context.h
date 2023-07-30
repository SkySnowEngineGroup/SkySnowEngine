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
#pragma once
#include "NonCopyable.h"
#include "SkySnowEngine.h"
#include "ISystem.h"
#include <vector>
namespace SkySnow
{
    class SceneRenderer;
    class Context : public NonCopyable
    {
    public:
        static Context& Instance();
        
        SceneRenderer* RegisterSceneRenderer();
        
        SceneRenderer* GetSceneRenderer();
        
        void RemoveSceneRenderer();

        void RegisterSkySnowEngine(SkySnowEngine* engine)
        {
            _SkySnowEngine = engine;
        }
        SkySnowEngine* GetSkySnowEngine() const
        {
            return _SkySnowEngine;
        }
        template<typename T> T* RegisterSystem();

        template<typename T> T* GetSystem();

        template<typename T> void RemoveSystem();
    private:
        Context();
        ~Context();
    private:
        SceneRenderer*          _SceneRenderer;
        std::vector<ISystem*>   _Systems;
        SkySnowEngine*          _SkySnowEngine;
    };

    template<typename T> inline T* Context::RegisterSystem()
    {
        for(auto entry:_Systems)
        {
            if (T::GetTypeNameStatic() == entry->GetTypeName())
            {
                return dynamic_cast<T*>(entry);
            }
        }
        T* system = new T();
        _Systems.push_back(system);
        return dynamic_cast<T*>(system);
    }

    template<typename T> inline T* Context::GetSystem()
    {
        for(auto entry:_Systems)
        {
            if (T::GetTypeNameStatic() == entry->GetTypeName())
            {
                return dynamic_cast<T*>(entry);
            }
        }
        return RegisterSystem<T>();
    }

    template<typename T> inline void Context::RemoveSystem()
    {
        for (auto iter = _Systems.begin(); iter != _Systems.end();iter++)
        {
            if ((*iter)->GetTypeName() == T::GetTypeNameStatic())
            {
                delete (*iter);
                _Systems.erase(iter);
                break;
            }
        }
    }
}
