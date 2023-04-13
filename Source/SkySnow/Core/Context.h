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
#include "ISystem.h"
#include <vector>
namespace SkySnow
{
    class SceneRenderer;

    class Context : public NonCopyable
    {
    public:
        static Context& Instance();
        
        void RegisterSceneRenderer(SceneRenderer* sceneRenderer);
        
        SceneRenderer* GetSceneRenderer();
        
        void RemoveSceneRenderer();

        template<typename T> void RegisterSystem();

        template<typename T> T* GetSystem();

        template<typename T> void RemoveSystem();
    private:
        Context();
        ~Context();
    private:
        SceneRenderer*  _SceneRenderer;
        std::vector<ISystem*> _Systems;
    };

    template<typename T> inline void Context::RegisterSystem()
    {
        bool isFind = false;
        for each (auto entry in _Systems)
        {
            if (T::GetTypeNameStatic() == entry->GetTypeName())
            {
                isFind = true;
            }
        }
        if (!isFind)
        {
            T* system = new T();
            _Systems.push_back(system);
        }
    }

    template<typename T> inline T* Context::GetSystem()
    {
        for each (auto entry in _Systems)
        {
            if (T::GetTypeNameStatic() == entry->GetTypeName())
            {
                return dynamic_cast<T*>(entry);
            }
        }
        return nullptr;
    }

    template<typename T> inline void Context::RemoveSystem()
    {
        for (auto iter = _Systems.begin(); iter != _Systems.end(); )
        {
            if (*iter != nullptr && (*iter)->GetTypeName() == T::GetTypeNameStatic())
            {
                delete (*iter);
                iter = _Systems.erase(iter);
            }
            else 
            {
                iter++;
            }
        }
    }
}
