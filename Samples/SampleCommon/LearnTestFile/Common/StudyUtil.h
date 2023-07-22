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
#include "LogAssert.h"
#include "RefCounted.h"
namespace SkySnowLearning
{
    struct SDNode
    {
        SDNode(int k = -1,int v = -1)
            : key(k)
            , value(v)
            , pre(nullptr)
            , next(nullptr)
        {
        }
        int     key;
        int     value;
        SDNode* pre;
        SDNode* next;
    };
    
    struct SSNode
    {
        SSNode(int v = -1,SSNode* n = nullptr)
            : value(v)
            , next(n)
        {
        }
        
        bool operator ==(SSNode& other) const
        {
            return other.value == this->value;
        }
        int     value;
        SSNode* next;
    };

    struct TreeNode
    {
        TreeNode()
            : m_Data(0)
            , m_Left(nullptr)
            , m_Right(nullptr)
        {
        }
        TreeNode(int val)
            : m_Data(val)
            , m_Left(nullptr)
            , m_Right(nullptr)
        {
        }
        TreeNode(int val,TreeNode* left,TreeNode* right)
            : m_Data(val)
            , m_Left(left)
            , m_Right(right)
        {
        }
        int m_Data;
        struct TreeNode* m_Left;
        struct TreeNode* m_Right;
    };
}
