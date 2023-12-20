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
#include "StaticMesh.h"

namespace SkySnow
{
    StaticMesh::StaticMesh()
        : MeshBase(MT_StaticMesh)
    {
    }

    StaticMesh::~StaticMesh()
    {
        
    }

    void StaticMesh::CreateStandardMesh(StandardMeshType smType)
    {
        SMesh sMesh;
        switch(smType)
        {
            case SM_Quad: sMesh = MQuad(); break;
            case SM_Cube: sMesh = MCube(); break;
            case SM_Sphere: sMesh = MSphere(); break;
            case SM_Cone: sMesh = MCone(); break;
            default:
                SN_LOG("Not support this StandardMeshType:%d",smType);
                break;
        }
        if(!_VertexData)
        {
            _VertexData = CreateSPtr<StaticVertexData>();
        }
        _VertexData->PushVertexStream(sMesh._ArrayStream);
    }

    void StaticMesh::SetVertexData(const SPtr<StaticVertexData>& vertexData)
    {
        _VertexData = vertexData;
    }

    SPtr<StaticVertexData> StaticMesh::GetVertexData()
    {
        return _VertexData;
    }

    void StaticMesh::CreateMeshBuffer()
    {
        if (!_MeshBuffer)
        {
            _MeshBuffer = CreateSPtr<StaticMeshBuffer>();
            _MeshBuffer->CreateBuffer(_VertexData);
        }
    }

    SPtr<StaticMeshBuffer> StaticMesh::GetMeshBuffer()
    {
        return _MeshBuffer;
    }
    
}
