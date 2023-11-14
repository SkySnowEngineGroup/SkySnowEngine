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
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace SkySnow
{
//    template<typename T>class Vector2;
//    template<typename T>class Vector3;
//    template<typename T>class Vector4;

    
    typedef Vector2<int>    Vector2i;
    typedef Vector2<float>  Vector2f;
    typedef Vector2<double> Vector2d;

    typedef Vector3<int>    Vector3i;
    typedef Vector3<float>  Vector3f;
    typedef Vector3<double> Vector3d;

    typedef Vector4<int>    Vector4i;
    typedef Vector4<float>  Vector4f;
    typedef Vector4<double> Vector4d;

    //Math Base Function
//    namespace Math
//    {
//        static inline bool IsZero(float value)
//        {
//            return fabs(value) < 1e-6;
//        }
//        static inline bool IsZero(double value)
//        {
//            return fabs(value) < 1e-15;
//        }
//    }
}
