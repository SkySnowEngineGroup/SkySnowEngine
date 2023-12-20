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

namespace SkySnow
{
    template<typename T>
    class Vector3
    {
    public:
        union
        {
            struct { T	x, y, z;};
            T		_Data[3];
        };
    public:
        Vector3()
            : x(T(0))
            , y(T(0))
            , z(T(0))
        {
        }
        Vector3(T inX, T inY, T inZ)
            : x(inX)
            , y(inY)
            , z(inZ)
        {
        }


        T& operator[] (int i)
        {
            return _Data[i];
        }

        const T& operator[] (int i) const
        {
            return _Data[i];
        }

        static int Count()
        {
            return 3;
        }

        static int ByteSize()
        {
            return 3 * sizeof(T);
        }

        const byte* Data() const
        {
            return (byte*)_Data;
        }

        bool CpyData(const byte* buff) const
        {
            memcpy(_Data, buff, ByteSize());
            return true;
        }
    };
}
