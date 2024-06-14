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
#include "GameObjectManager.h"
#include "GameObject.h"
#include "IComponent.h"

namespace SkySnow
{
    GameObjectManager::GameObjectManager()
    {
    }
    GameObjectManager::~GameObjectManager()
    {
    }
    GameObjectManager& GameObjectManager::Instance()
    {
        static GameObjectManager instance;
        return instance;
    }

    SPtr<GameObject> GameObjectManager::CreateGameObject()
    {
        _tempUuidIdx ++;
        SPtr<GameObject> go = CreateSPtr<GameObject>();
        go->SetUUID(_tempUuidIdx);
        _GOMaps[_tempUuidIdx] = go;
        return go;
    }
    SPtr<GameObject> GameObjectManager::GetGameObjectPtr(int64_t uuid)
    {
        auto iter = _GOMaps.find(uuid);
        if(iter != _GOMaps.end())
        {
            return iter->second;
        }
        return nullptr;
    }
    void GameObjectManager::UpdateGameObjectUUID(int64 oldUuid,int64 newUuid)
    {
        auto iter = _GOMaps.find(oldUuid);
        if(iter != _GOMaps.end())
        {
            SPtr<GameObject> go = iter->second;
            _GOMaps.erase(iter);
            _GOMaps[newUuid] = go;
        }
    }
    void GameObjectManager::RemoveGameObjectPtr(int64_t uuid)
    {
        auto iter = _GOMaps.find(uuid);
        if(iter != _GOMaps.end())
        {
            RemoveGameObjectComponents(iter->second->GetUUID());
            _GOMaps.erase(iter);
        }
    }
    std::map<int64,std::vector<SPtr<IComponent>>>& GameObjectManager::GetComponents()
    {
        return _ComMaps;
    }
    SPtr<IComponent> GameObjectManager::GetComponentPtr(int64 goUuid,const char* typeName)
    {
        auto iter = _ComMaps.find(goUuid);
        if(iter != _ComMaps.end())
        {
            for(auto com : iter->second)
            {
               if(com->GetTypeName() == typeName)
               {
                   return com;
               }
            }
        }
        return nullptr;
    }
    void GameObjectManager::RemoveComponentPtr(int64 goUuid,const char* typeName)
    {
        auto iter = _ComMaps.find(goUuid);
        if(iter != _ComMaps.end())
        {
            for(auto ci = iter->second.begin();ci != iter->second.end();)
            {
               if((*ci)->GetTypeName() == typeName)
               {
                   (*ci)->RemoveFromModule();
                   (*ci)->OnDestroyed();
                   ci = iter->second.erase(ci);
                   break;
               }else
               {
                   ci ++;
               }
            }
        }
    }
    void GameObjectManager::RemoveGameObjectComponents(int64 goUuid)
    {
        auto iter = _ComMaps.find(goUuid);
        if(iter != _ComMaps.end())
        {
            for (auto com : iter->second)
            {
                com->RemoveFromModule();
                com->OnDestroyed();
            }
            _ComMaps.erase(iter);
        }
    }

    void GameObjectManager::ClearGameObject()
    {
        for(auto go = _ComMaps.begin();go != _ComMaps.end(); go ++)
        {
            for(auto com : go->second)
            {
                com->RemoveFromModule();
                com->OnDestroyed();
            }
        }
        _ComMaps.clear();
        _GOMaps.clear();
    }
    GameObjectManager& GetGOManager()
    {
        return GameObjectManager::Instance();
    }
}
