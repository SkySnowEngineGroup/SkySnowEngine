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
    
    VertexDescriptor VertexStream::GetVertexDesc()
    {
        return _VertexDesc;
    }

    void VertexStream::SetVertexCount(uint32 vlss, int count)
    {
        _ChunkStride    = 0;
        _VertexLayout   = vlss;
        _VertexCount    = count;
        if (vlss | VertexLayoutSlot::VLS_Position)
        {
            _ChunkStride += Vector3f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_Normal)
        {
            _ChunkStride += Vector3f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_Tangent)
        {
            _ChunkStride += Vector4f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_Color)
        {
            _ChunkStride += Vector4f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_TexCoord0)
        {
            _ChunkStride += Vector2f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_TexCoord1)
        {
            _ChunkStride += Vector2f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_TexCoord2)
        {
            _ChunkStride += Vector2f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_TexCoord3)
        {
            _ChunkStride += Vector2f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_TexCoord4)
        {
            _ChunkStride += Vector2f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_TexCoord5)
        {
            _ChunkStride += Vector2f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_TexCoord6)
        {
            _ChunkStride += Vector2f::ByteSize();
        }
        if (vlss | VertexLayoutSlot::VLS_TexCoord7)
        {
            _ChunkStride += Vector2f::ByteSize();
        }

        if (count)
        {
            int dataSize = _ChunkStride * _VertexCount;
            _Buffer.resize(dataSize);
        }
    }

    void VertexStream::PushVertex(VertexLayoutSlot slot, Vector2f inData)
    {

    }
    void VertexStream::PushVertex(VertexLayoutSlot slot, Vector3f inData)
    {

    }
    void VertexStream::PushVertex(VertexLayoutSlot slot, Vector4f inData)
    {

    }
}
