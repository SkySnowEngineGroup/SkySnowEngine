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
#include <vector>
using namespace std;
namespace SkySnowLearning
{
    template<typename T>
    class S_Stack
    {
    public:
        S_Stack()
        {
        }
        
        ~S_Stack()
        {
            _Data.clear();
        }
        
        void Push(T value)
        {
            _Data.push_back(value);
        }
        
        T Pop()
        {
            T value = _Data.back();
            _Data.pop_back();
            return value;
        }
        
        bool IsEmpty()
        {
            return _Data.empty();
        }
        
        T Top()
        {
            return _Data.back();
        }
        
        size_t Size() const
        {
            return _Data.size();
        }
        
        bool Valid_MathFun(std::string str)
        {
            char small_l = '(';
            char small_r = ')';
            
            char mid_l = '[';
            char mid_r = ']';
            
            char big_l = '{';
            char big_r = '}';
            
            for(int i = 0; i < str.size(); i ++)
            {
                char ts = str[i];
                if(ts == small_l || ts == mid_l || ts == big_l)
                {
                    Push(ts);
                }
                else if(ts == small_r || ts == mid_r || ts == big_r)
                {
                    if(IsEmpty())
                    {
                        return false;
                    }
                    char ps = Top();
                    if((ts == small_r && ps == small_l) ||
                       (ts == mid_r && ps == mid_l) ||
                       (ts == big_r && ps == big_l))
                    {
                        Pop();
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return IsEmpty();
        }
    private:
        std::vector<T> _Data;
    };

    static void Stack_Data()
    {
        S_Stack<int> stack;
        stack.Push(1);
        stack.Push(2);
        stack.Push(3);
        stack.Push(4);

        SN_LOG("StackValue_1:%d",stack.Pop());
        SN_LOG("StackValue_2:%d",stack.Pop());
        SN_LOG("StackValue_3:%d",stack.Pop());
        SN_LOG("StackValue_4:%d",stack.Pop());
        SN_LOG("StackSize:%d",stack.Size());
        
        std::string testStr = "(2 + 3) * 4 - [5 - 6]}";
        S_Stack<char> stack_ch;
        bool valid = stack_ch.Valid_MathFun(testStr);
        if(valid)
        {
            SN_LOG("Legal Math Function: %s is Valid.",testStr.c_str());
        }
        else
        {
            SN_LOG("Legal Math Function: %s is not Valid.",testStr.c_str());
        }
    }
}

