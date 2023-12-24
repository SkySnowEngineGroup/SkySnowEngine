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
#include "MeshBuffer.h"
#include "VertexData.h"

namespace SkySnow
{
    MeshBuffer::MeshBuffer()
    {
        
    }

    MeshBuffer::~MeshBuffer()
    {
        
    }

    void MeshBuffer::SMCreateBuffer(SPtr<VertexData> vertexData)
    {
        if(!_PositionBuffer)
        {
            _PositionBuffer = CreateSPtr<PositionBuffer>();
        }
        std::vector<SPtr<VertexStream>> stream = vertexData->GetVertexStreams();
        const void* data = stream[0]->GetBufferData();
        int dataSize = stream[0]->GetBufferSize();
        int vStrid = stream[0]->GetVertexStrid();
        
        ResourceData vexRD;
        vexRD.MakeCopy(stream[0]->GetBufferData(), dataSize);
        _PositionBuffer->_VertexBufferGRI = GRCCreateBuffer(BufferUsageType::BUT_VertexBuffer,
                                                         dataSize,
                                                         vStrid,
                                                         vexRD);
        VertexElementList veList = stream[0]->GetVertexElementList();
        for(auto& entry: veList)
        {
            entry._GRIBuffer = _PositionBuffer->_VertexBufferGRI;
            entry._BufferIndex = 0;
        }
        _VertexDesc = GRCCreateVertexDescriptor(veList);
    }

    GRIVertexDescriptorRef MeshBuffer::GetVertexDesc()
    {
        return _VertexDesc;
    }
}
