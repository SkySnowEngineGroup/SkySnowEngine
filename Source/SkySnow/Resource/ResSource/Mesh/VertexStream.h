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
#include "GRIResourceCreateInfo.h"
#include "IStream.h"
#include "MathCommon.h"
#include <vector>
namespace SkySnow
{
    class VertexStream : public IStream
    {
        SkySnow_Object(VertexStream, IStream);
        friend class VertexData;
    public:
        VertexStream();
        ~VertexStream();

        
        void ReserveBuffer(uint32 count);
        
        void AddVertexElementSlot(VertexLayoutSlot eSlot, VertexElementType veType);

        void PushVertex(VertexLayoutSlot slot, const Vector2f& inData);
        void PushVertex(VertexLayoutSlot slot, const Vector3f& inData);
        void PushVertex(VertexLayoutSlot slot, const Vector4f& inData);
        const void* GetBufferData() const;
        int GetBufferSize(){return _StridSize * _VertexCount;}
        int GetVertexStrid(){return _Strid;}
        const VertexElementList& GetVertexElementList();

        const int GetStreamIndex() { return _StreamIndex; }
    private:
        inline int ComBinaryBitIndex(VertexLayoutSlot slot);
        void ResizeBuffer();
    private:
        int                 _StreamIndex;
        std::vector<char>   _Buffer;
        int                 _VertexCount;
        int                 _Strid;
        int                 _StridSize;
        VertexElementList   _VertexElementList;
        bool                _IsDirty;
    };

    inline int VertexStream::ComBinaryBitIndex(VertexLayoutSlot slot)
    {
        int bitIndex = 0;
        int value = slot;
        while(value > 0)
        {
            if(value & 1)
            {
                break;
            }
            value >>= 1;
            bitIndex++;
        }
        return bitIndex;
    }
}
