//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by sunguoqiang(SunGQ1987),wangcan(crygl),
//							 liuqian(SkySnow),zhangshuangxue(Calence)
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
#pragma once
#include "Type.h"
namespace SkySnow
{
//记录类型信息
#define SkySnow_Object(TypeName,BaseTypeName) \
		public: \
			using ClassName = TypeName; \
			using ParentClassName = BaseTypeName; \
			virtual const Type* GetType() const override \
			{ \
				return GetTypeStatic()->GetType(); \
			} \
			virtual const char* GetTypeName() const override \
			{ \
				return GetTypeStatic()->GetName(); \
			} \
			static const char* GetTypeNameStatic() \
			{ \
				return GetTypeStatic()->GetName(); \
			} \
			static const SkySnow::Type* GetTypeStatic() \
			{ \
				static const SkySnow::Type type(#TypeName,ParentClassName::GetTypeStatic()); \
				return &type; \
			}
}