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
    class Context : public NonCopyable
    {
    public:
        static Context& Instance();

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
        std::unordered_map<std::string, IModule*>    _Modules;
        SkySnowEngine*                          _SkySnowEngine;
    };
    Context& SSContext();
    template<typename T> inline T* Context::RegisterModule()
    {
        if(_Modules.find(T::GetTypeNameStatic()) != _Modules.end())
        {
            return dynamic_cast<T*>(_Modules[T::GetTypeNameStatic()]);
        }
        
        T* tModule = new T();
        _Modules[tModule->GetTypeName()] = tModule;
        return dynamic_cast<T*>(tModule);
    }

    template<typename T> inline T* Context::GetModule()
    {
        if(_Modules.find(T::GetTypeNameStatic()) != _Modules.end())
        {
            return dynamic_cast<T*>(_Modules[T::GetTypeNameStatic()]);
        }
        return RegisterModule<T>();
    }

    template<typename T> inline void Context::RemoveModule()
    {
        auto iter = _Modules.find(T::GetTypeNameStatic());
        if(iter != _Modules.end())
        {
            delete iter->second; // 释放内存
            _Modules.erase(iter);
        }
        else
        {
            SN_LOG("Not find this module:%s",T::GetTypeNameStatic());
        }
    }
}
