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
        
        SPtr<GameObject> CreateGo();
        SPtr<GameObject> GetGoPtr(int64_t uuid);
        void UpdateGOUUID(int64 oldUuid,int64 newUuid);
        void RemoveGoPtr(int64_t uuid);
        
        std::map<int64,std::vector<SPtr<IComponent>>>& GetComs();
        SPtr<IComponent> GetComPtr(int64 goUuid,const char* typeName);
        void RemoveComPtr(int64 goUuid,const char* typeName);
    private:
        int64                            _tempUuidIdx = -1;
        std::map<int64,SPtr<GameObject>> _GOMaps;
        std::map<int64,std::vector<SPtr<IComponent>>> _ComMaps;
    };
    GameObjectManager& GetGOManager();
}
