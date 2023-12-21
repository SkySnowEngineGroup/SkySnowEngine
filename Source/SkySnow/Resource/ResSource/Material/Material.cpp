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
#include "Material.h"
namespace SkySnow
{
    Material::Material()
        : IResSource(RS_MaterialSource)
    {

    }

    Material::~Material()
    {

    }

    void Material::SetTexture(std::string name, Texture2D* texture)
    {
        _Textures[name] = texture;
    }

    Texture2D* Material::GetTexture(std::string name)
    {
        auto find = _Textures.find(name);
        if (find != _Textures.end())
        {
            return find->second;
        }
        return nullptr;
    }

    void Material::CreateShader(std::string vsName,std::string fsName)
    {
        string vsShaderPath = GetMaterialAllPath("Test/" + vsName);
        string fsShaderPath = GetMaterialAllPath("Test/" + fsName);
        _File = new File();
        _VsData = new Data();
        _FsData = new Data();
        //TODO Shader SourceData Manage
        _File->ReadData(vsShaderPath, _VsData);
        _File->ReadData(fsShaderPath, _FsData);
    }
}
