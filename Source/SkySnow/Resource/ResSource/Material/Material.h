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
#include "StandardMesh.h"
#include "IResSource.h"
#include "Texture2D.h"
#include "PropertyName.h"
#include "GRIHeaders.h"
#include "File.h"
namespace SkySnow
{
    class Material : public IResSource
    {
        SkySnow_Object(Material, IResSource);
    public:
        Material();
        ~Material();
        
        void SetTexture(std::string name,Texture2D* texture);

        Texture2D* GetTexture(std::string name);
        
        //temp code
        void CreateShader(std::string vsName,std::string fsName);
        GRIPipelineShaderRef GetPShader()
        {
            if(!_PipelineShaderRef.GetReference())
            {
                //Create VS And PS
                ResourceData vsRD;
                vsRD.MakeCopy(_VsData->GetBytes(), (int32)_VsData->GetSize());
                _vsRef = GRCCreateVertexShader(vsRD);
                ResourceData fsRD;
                fsRD.MakeCopy(_FsData->GetBytes(), (int32)_FsData->GetSize());
                _fsRef = GRCCreateFragmentShader(fsRD);
                //Create ShaderPipeline
                _PipelineShaderRef = GRCCreatePipelineShader(_vsRef, _fsRef);
            }
            return _PipelineShaderRef;
        }

    private:
        std::unordered_map<std::string, Texture2D*>    _Textures;
        File*                       _File;
        Data*                       _VsData;
        Data*                       _FsData;
        GRIVertexShaderRef          _vsRef;
        GRIFragmentShaderRef        _fsRef;
        GRIPipelineShaderRef        _PipelineShaderRef;
    };
}
