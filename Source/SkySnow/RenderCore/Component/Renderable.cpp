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
#include "Renderable.h"

namespace SkySnow
{
    Renderable::Renderable()
    {
        
    }
    Renderable::~Renderable()
    {
        
    }
    
    void Renderable::SetMaterialCount(int matCount)
    {
        const size_t oldSize = _Materials.size();
        if (matCount != (int)oldSize)
        {
            _Materials.clear();
            _Materials.resize(matCount);
        }
    }

    void Renderable::SetMaterial(SPtr<Material> material, int index)
    {
        if (index > _Materials.size())
        {
            SN_ERR("The index is larger than the material array size.");
        }
        _Materials[index] = material;
    }

    std::vector<SPtr<Material>> Renderable::GetMaterials()
    {
        return _Materials;
    }

    void Renderable::SetMesh(SPtr<Mesh> mesh)
    {
        _Mesh = mesh;
    }
}
