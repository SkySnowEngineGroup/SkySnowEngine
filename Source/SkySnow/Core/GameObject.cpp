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

#include "GameObject.h"
#include "LogAssert.h"
#include "TransformComponent.h"
namespace SkySnow
{
    GameObject::GameObject()
        : _Enable(true)
        , _Layer(0)
        , _Tag(0)
        , _Parent(nullptr)
    {
        _ComponentList.clear();
        _ChildList.clear();
    }
    
    GameObject::~GameObject()
    {
        for (auto entry:_ComponentList)
        {
            delete entry;
        }
        _ComponentList.clear();
        for(auto entry:_ChildList)
        {
            delete entry;
        }
        _ChildList.clear();
    }

    void GameObject::SetEnable(bool enable)
    {
        _Enable = enable;
        for(auto entry : _ComponentList)
        {
            entry->SetEnabled(enable);
        }
        for(auto entry:_ChildList)
        {
            entry->SetEnable(enable);
        }
    }

    bool GameObject::IsEnable() const
    {
        return _Enable;
    }
    //value between [0 32),so layer max is 32
    void GameObject::SetLayer(int32_t layer)
    {
        if(layer >= 0 && layer < 32)
        {
            _Layer = layer;
        }
        else
        {
            SN_WARN("GameObject::SetLayer parameter layer set error,The interval should be between [0 32].this setup layer value:%d",layer);
        }
    }

    int32_t GameObject::GetLayer() const
    {
        return _Layer;
    }
    //Gets the tag of the GameObject's level
    int32_t GameObject::GetLayerMask() const
    {
        return 1 << _Layer;
    }
    
    void GameObject::SetTag(int16_t tag)
    {
        _Tag = tag;
    }

    int16_t GameObject::GetTag() const
    {
        return _Tag;
    }

    GameObject* GameObject::AddChild()
    {
        GameObject* cgo = new GameObject();
        _ChildList.push_back(cgo);
        int32_t layer = _Layer + 1;
        cgo->SetLayer(layer);
        return cgo;
    }

    void GameObject::RemoveChild(GameObject* childGO)
    {
        for(auto entry:_ChildList)
        {
            if(entry == childGO)
            {
                delete entry;
                break;
            }
        }
    }

    void GameObject::SetParent(GameObject* parentGO)
    {
        _Parent = parentGO;
    }
}
