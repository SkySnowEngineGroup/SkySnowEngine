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
        typedef std::unordered_map<uint32, VertexElementSlot> VertexLayouts;
    public:
        VertexStream();
        ~VertexStream();

        
        void ReserveBuffer(uint32 count);
        
        void AddVertexElementSlot(VertexLayoutSlot eSlot, VertexElementType veType);
        
        template<typename T>
        void PushVertex(VertexLayoutSlot slot, const T& inData);
        const void* GetBufferData() const;
        int GetBufferSize(){return _StridSize * _VertexCount;}
        int GetVertexStrid(){return _Strid;}
        const VertexElementList& GetVertexElementList();

        const int GetStreamIndex() { return _StreamIndex; }
    private:
        inline int ComBinaryBitIndex(VertexLayoutSlot slot);
        void ReserveBuffer();
        void DoPushVertex(const char* data);
    private:
        std::vector<char>   _BufferPusher;
        int                 _PusherSize;
        VertexLayouts       _PusherIndexMap;
    private:
        int                 _StreamIndex;
        std::vector<char>   _Buffer;
        int                 _VertexCount;
        int                 _Strid;
        int                 _StridSize;
        VertexElementList   _VertexElementList;
        bool                _IsDirty;
    };

    template<typename T>
    inline void VertexStream::PushVertex(VertexLayoutSlot slot, const T& inData)
    {
        ReserveBuffer();
        _PusherSize += T::ByteSize();
        if(_PusherIndexMap.find(slot) == _PusherIndexMap.end())
        {
            SN_WARN("VertexStream not have VertexLayoutSlot(%d).",slot);
        }
        auto& layout = _PusherIndexMap[slot];
        std::memcpy(&_BufferPusher[layout._Offset],inData.Data(),T::ByteSize());
        if (_PusherSize >= _StridSize)
        {
            DoPushVertex(_BufferPusher.data());
            _PusherSize = 0;
            _BufferPusher.clear();
        }
    }
    inline void VertexStream::DoPushVertex(const char* data)
    {
        _Buffer.insert(_Buffer.end(), data, data + _StridSize);
    }
    inline void VertexStream::ReserveBuffer()
    {
        if (_IsDirty)
        {
            _VertexElementList.clear();
            _BufferPusher.resize(_StridSize);
            _Buffer.reserve(_StridSize * _VertexCount);
            
            int offset = 0;
            for(int i = 0; i < VLS_Count; i ++)
            {
                auto iter = _PusherIndexMap.find(1 << i);
                if(iter != _PusherIndexMap.end())
                {
                    iter->second._Offset = offset;
                    offset += iter->second._VESize * iter->second._Strid;
                    _VertexElementList.push_back(iter->second);
                }
            }
            _IsDirty = false;
        }
    }
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
