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
#include "VertexStream.h"
#include <iostream>
#include <vector>
#include <algorithm>
namespace SkySnow
{
	VertexStream::VertexStream()
        : _VertexCount(0)
        , _StridSize(0)
        , _IsDirty(false)
        , _Strid(0)
        , _StreamIndex(0)
	{
	}
    
	VertexStream::~VertexStream()
	{
	}

    void VertexStream::ReserveBuffer(uint32 count)
    {
        if(_VertexCount != count)
        {
            _VertexCount = count;
            _IsDirty = true;
        }
    }

    void VertexStream::AddVertexElementSlot(VertexLayoutSlot eSlot, VertexElementType veType)
    {
        int vtSize      = 0;
        int veCount     = 0;
        switch(veType)
        {
            case VertexElementType::VET_Float1:
                veCount = 1;
                vtSize = sizeof(float);
                break;
            case VertexElementType::VET_Float2:
                veCount = 2;
                vtSize = sizeof(float);
                break;
            case VertexElementType::VET_Float3:
                veCount = 3;
                vtSize = sizeof(float);
                break;
            case VertexElementType::VET_Float4:
                veCount = 4;
                vtSize = sizeof(float);
                break;
            default:
                SN_LOG("Not support VertexElementType(%d).",veType);
                break;
        }

        VertexElementSlot veSlot;
        veSlot._AttributeIndex = ComBinaryBitIndex(eSlot);
        veSlot._Strid          = veCount;
        veSlot._VESize         = vtSize;
        veSlot._Offset         = 0;
        veSlot._VET_Type       = veType;
        _VertexElementList.push_back(veSlot);

        _StridSize += vtSize * veCount;
        _Strid += veCount;

        //Sort with attritube index
        auto compare = [](const VertexElementSlot& x, const VertexElementSlot& y)
        {
            return x._AttributeIndex < y._AttributeIndex;
        };
        std::sort(_VertexElementList.begin(), _VertexElementList.end(), compare);
        //Re Calcute vertexElement offset
        int tOffset = 0;
        for (auto& entry : _VertexElementList)
        {
            entry._Offset = tOffset;
            tOffset += entry._Strid * entry._VESize;
        }
    }

    void VertexStream::PushVertex(VertexLayoutSlot slot, const Vector2f& inData)
    {
        ResizeBuffer();
        _Buffer.insert(_Buffer.end(), inData.Data(),inData.Data() + inData.ByteSize());
    }
    void VertexStream::PushVertex(VertexLayoutSlot slot, const Vector3f& inData)
    {
        ResizeBuffer();
        _Buffer.insert(_Buffer.end(), inData.Data(),inData.Data() + inData.ByteSize());
    }
    void VertexStream::PushVertex(VertexLayoutSlot slot, const Vector4f& inData)
    {
        ResizeBuffer();
        _Buffer.insert(_Buffer.end(), inData.Data(),inData.Data() + inData.ByteSize());
    }
    const void* VertexStream::GetBufferData() const
    {
        return &_Buffer[0];
    }

    const VertexElementList& VertexStream::GetVertexElementList()
    {
        return _VertexElementList;
    }

    void VertexStream::ResizeBuffer()
    {
        if(_IsDirty)
        {
            _Buffer.reserve(_StridSize * _VertexCount);
            _IsDirty = false;
        }
    }
}
