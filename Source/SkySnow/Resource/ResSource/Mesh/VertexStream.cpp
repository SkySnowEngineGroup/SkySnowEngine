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
namespace SkySnow
{
	VertexStream::VertexStream()
        : _VertexCount(0)
        , _ChunkStride(0)
        , _VertexLayout(0)
	{
	}
    
	VertexStream::~VertexStream()
	{
	}

    void VertexStream::SetVertexCount(int count)
    {
        _ChunkStride    = 0;
        _VertexLayout   = vlss;
        _VertexCount    = count;
        _ChunkStride = CalcuChunkStride(vlss);
        if (count)
        {
            int dataSize = _ChunkStride * _VertexCount;
            _Buffer.reserve(dataSize);
        }
    }

    void VertexStream::PushVertex(VertexLayoutSlot slot, const Vector2f& inData)
    {
        _Buffer.insert(_Buffer.end(), inData.Data(),inData.Data() + inData.ByteSize());
    }
    void VertexStream::PushVertex(VertexLayoutSlot slot, const Vector3f& inData)
    {
        _Buffer.insert(_Buffer.end(), inData.Data(),inData.Data() + inData.ByteSize());
    }
    void VertexStream::PushVertex(VertexLayoutSlot slot, const Vector4f& inData)
    {
        _Buffer.insert(_Buffer.end(), inData.Data(),inData.Data() + inData.ByteSize());
    }
    const void* VertexStream::GetBufferData() const
    {
        return &_Buffer[0];
    }

    int VertexStream::CalcuChunkStride(uint32 vlss)
    {
        int chunkStride = 0;
        if (vlss & VertexLayoutSlot::VLS_Position)
        {
            chunkStride += Vector3f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_Normal)
        {
            chunkStride += Vector3f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_Tangent)
        {
            chunkStride += Vector4f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_Color)
        {
            chunkStride += Vector4f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_TexCoord0)
        {
            chunkStride += Vector2f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_TexCoord1)
        {
            chunkStride += Vector2f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_TexCoord2)
        {
            chunkStride += Vector2f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_TexCoord3)
        {
            chunkStride += Vector2f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_TexCoord4)
        {
            chunkStride += Vector2f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_TexCoord5)
        {
            chunkStride += Vector2f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_TexCoord6)
        {
            chunkStride += Vector2f::ByteSize();
        }
        if (vlss & VertexLayoutSlot::VLS_TexCoord7)
        {
            chunkStride += Vector2f::ByteSize();
        }
        return chunkStride;
    }
}
