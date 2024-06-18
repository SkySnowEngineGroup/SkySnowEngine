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
#include "Object.h"
#include "SPtr.h"

namespace SkySnow
{
    class IRSBase : public Object
    {
        SkySnow_Object(IRSBase, Object);
    public:
        IRSBase(){};
        virtual ~IRSBase(){}
    public:
        virtual void CreateResource() = 0;
        virtual void CreateSource() = 0;
    };
    template<typename Source, typename Resource>
    class IRSEntity : public IRSBase
    {
        SkySnow_Object(IRSEntity, Object);
    public:
        IRSEntity() {}
        virtual ~IRSEntity() {}

        SPtr<Resource>  Res() { return _Res; }
        SPtr<Source>    Sou() { return _Sou; }
        
        virtual void CreateResource() final override { OnCreateRes();}
        virtual void CreateSource() final override { OnCreateSou(); }
        
    private:
        inline void OnCreateRes();
        inline void OnCreateSou();
    private:
        SPtr<Resource>  _Res;
        SPtr<Source>    _Sou;
    };
    template<typename Source,typename Resource>
    inline void IRSEntity<Source,Resource>::OnCreateRes()
    {
        _Res = CreateSPtr<Resource>();
    }
    template<typename Source,typename Resource>
    inline void IRSEntity<Source,Resource>::OnCreateSou()
    {
        _Sou = CreateSPtr<Source>();
    }
}
