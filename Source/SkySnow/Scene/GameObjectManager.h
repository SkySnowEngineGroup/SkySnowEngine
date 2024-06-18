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
#include "NonCopyable.h"
#include "VarType.h"
#include "SPtr.h"
#include "UUID.h"
#include <map>
#include <vector>

namespace SkySnow
{
    class GameObject;
    class IComponent;
    class GameObjectManager : public NonCopyable
    {
    public:
        static GameObjectManager& Instance();
        
        SPtr<GameObject> CreateGameObject();
        SPtr<GameObject> GetGameObjectPtr(const UUID& uuid);
        void UpdateGameObjectUUID(const UUID& oldUuid,const UUID& newUuid);
        void RemoveGameObjectPtr(const UUID& uuid);
        
        std::map<UUID,std::vector<SPtr<IComponent>>>& GetComponents();
        SPtr<IComponent> GetComponentPtr(const UUID& goUuid,const char* typeName);
        void RemoveComponentPtr(const UUID& goUuid,const char* typeName);
        void RemoveGameObjectComponents(const UUID& goUuid);
        
        void ClearGameObject();
    private:
        GameObjectManager();
        ~GameObjectManager();
    private:
        std::map<UUID,SPtr<GameObject>>                 _GOMaps;
        std::map<UUID,std::vector<SPtr<IComponent>>>    _ComMaps;
    };
    GameObjectManager& GetGOManager();
}
