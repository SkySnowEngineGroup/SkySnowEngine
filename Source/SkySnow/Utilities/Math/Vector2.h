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
#include <math.h>
namespace SkySnow
{
    template<typename T>
    class Vector2
    {
    public:
        union
        {
            struct { T x, y;};
            T       _Data[2];
        };
    public:
        Vector2()
            : x(0)
            , y(0)
        {
        }
        
        Vector2(T inX,T inY)
            : x(inX)
            , y(inY)
        {
        }
        
        template<typename R>
        Vector2(const Vector2<R>& inData)
        {
            x = static_cast<T>(inData.x);
            y = static_cast<T>(inData.y);
        }
        
        template<typename R>
        Vector2& operator= (const Vector2<R>& input)
        {
            x = static_cast<T>(input.x);
            y = static_cast<T>(input.y);
            return *this;
        }
        
        Vector2& operator= (const Vector2& input)
        {
            x = input.x;
            y = input.y;
            return *this;
        }
        
        //vector2
        Vector2& operator+= (const Vector2& input)
        {
            x += input.x;
            y += input.y;
            return *this;
        }
        
        Vector2& operator-= (const Vector2& input)
        {
            x -= input.x;
            y -= input.y;
            return *this;
        }
        Vector2& operator*= (const Vector2& input)
        {
            x *= input.x;
            y *= input.y;
            return *this;
        }
        Vector2& operator/= (const Vector2& input)
        {
            x /= input.x;
            y /= input.y;
            return *this;
        }
        Vector2 operator* (const Vector2& input) const
        {
            return Vector2<T>( x * input.x , y * input.y);
        }
        
        Vector2 operator+ (const Vector2& input) const
        {
            return Vector2<T>( x + input.x , y + input.y);
        }
        
        Vector2 operator- (const Vector2& input) const
        {
            return Vector2<T>( x - input.x , y - input.y);
        }
        
        Vector2 operator/ (const Vector2& input) const
        {
            return Vector2<T>( x / input.x , y / input.y);
        }
        
        Vector2 operator- () const
        {
            return Vector2(-x, -y);
        }
        
        Vector2 operator/ (T num) const
        {
            return Vector2(x / num, y / num);
        }
        
        friend Vector2<T> operator* (T num, const Vector2<T>& rhs)
        {
            return Vector2<T>(rhs.x*num, rhs.y*num);
        }
        
        friend Vector2<T> operator* (const Vector2<T>& rhs, T num)
        {
            return Vector2<T>(rhs.x * num, rhs.y * num);
        }
        
        Vector2 operator- (T num) const
        {
            return Vector2(x - num, y - num);
        }
        
        Vector2 operator+ (T num) const
        {
            return Vector2(x + num, y + num);
        }
        
        Vector2& operator*= (T num)
        {
            x *= num;
            y *= num;
            return *this;
        }
        
        Vector2& operator/= (T num)
        {
            x /= num;
            y /= num;
            return *this;
        }
        
        Vector2& operator+= (T num)
        {
            x += num;
            y += num;
            return *this;
        }
        
        Vector2& operator-= (T num)
        {
            x -= num;
            y -= num;
            return *this;
        }
        T Dot(const Vector2& rhs) const
        {
            return Vector2<T>(x * rhs.x + y * rhs.y);
        }
        Vector2& NormalizeSelf()
        {
            T len = x * x + y * y;
            if (fabs(len) < 1e-5)
            {
                len = (T)1.0f;
            }
            else
            {
                len = T(1)/std::sqrt(x * x + y * y);
            }
            x = x * len;
            y = y * len;
            return *this;
        }
        Vector2 Normalize()
        {
            Vector2 temp;
            T len = x * x + y * y;
            if (std::fabs(float(len)) < 1e-6)
            {
                len = (T)1.0f;
            }
            else
            {
                len = T(1)/std::sqrt(x * x + y * y);
            }
            temp.x = x * len;
            temp.y = y * len;
            return temp;
        }
        T Length() const
        {
            return std::sqrt(x * x + y * y);
        }
        T Pow() const
        {
            return x*x + y*y;
        }
        void Set(T inX, T inY)
        {
            x = inX;
            y = inY;
        }
        T& operator[] (int i)
        {
            return _Data[i];
        }
        const T& operator[] (int i) const
        {
            return _Data[i];
        }
        int Count()
        {
            return 2;
        }
        static int ByteSize()
        {
            return 2 * sizeof(T);
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
