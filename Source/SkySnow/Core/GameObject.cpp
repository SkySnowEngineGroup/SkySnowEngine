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
namespace SkySnow
{
    GameObject::GameObject()
    {

    }
    GameObject::~GameObject()
    {

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
	void GameObject::AddComponent(IComponent* component)
    {
        component->AttachToGameObject(this);
        _ComponentList.push_back(component);
    }
}
