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
#include "IModule.h"
#include <vector>
namespace SkySnow
{
    class SceneRenderer;
    class Context : public NonCopyable
    {
    public:
        static Context& Instance();
        //TODO Not Single Instance
        SceneRenderer* RegisterSceneRenderer();
        
        SceneRenderer* GetSceneRenderer();
        
        void RemoveSceneRenderer();

        SkySnowEngine* RegisterSkySnowEngine()
        {
            if(!_SkySnowEngine)
            {
                _SkySnowEngine = new SkySnowEngine();
            }
            return _SkySnowEngine;
        }
        void RemoveSkySnowEngine()
        {
            Delete_Object(_SkySnowEngine);
        }
        SkySnowEngine* GetSkySnowEngine() const
        {
            return _SkySnowEngine;
        }
        template<typename T> T* RegisterModule();

        template<typename T> T* GetModule();

        template<typename T> void RemoveModule();
    private:
        Context();
        ~Context();
    private:
        SceneRenderer*          _SceneRenderer;
        std::vector<IModule*>   _Modules;
        SkySnowEngine*          _SkySnowEngine;
    };

    template<typename T> inline T* Context::RegisterModule()
    {
        for(auto entry: _Modules)
        {
            if (T::GetTypeNameStatic() == entry->GetTypeName())
            {
                return dynamic_cast<T*>(entry);
            }
        }
        T* module = new T();
        _Modules.push_back(module);
        return dynamic_cast<T*>(module);
    }

    template<typename T> inline T* Context::GetModule()
    {
        for(auto entry: _Modules)
        {
            if (T::GetTypeNameStatic() == entry->GetTypeName())
            {
                return dynamic_cast<T*>(entry);
            }
        }
        return RegisterModule<T>();
    }

    template<typename T> inline void Context::RemoveModule()
    {
        for (auto iter = _Modules.begin(); iter != _Modules.end();iter++)
        {
            if ((*iter)->GetTypeName() == T::GetTypeNameStatic())
            {
                delete (*iter);
                _Modules.erase(iter);
                break;
            }
        }
    }
}
