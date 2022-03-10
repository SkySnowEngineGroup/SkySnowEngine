//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
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
#include "RefCounted.h"
#include "GRICommons.h"
namespace SkySnow
{
	class GRIResource : public RefThreadSafeCounted
	{
	public:
		GRIResource(EGRIResourceType grit)
			: m_GRIResourceType(grit)
		{
		}
		inline EGRIResourceType GetType() const
		{
			return m_GRIResourceType;
		}
	private:
		const EGRIResourceType m_GRIResourceType;
	};

	class GRIShader : public GRIResource
	{
	public:
		GRIShader(EGRIResourceType grit)
			: GRIResource(grit)
		{
		}
	};

	class GRIVertexShader : public GRIShader
	{
	public:
		GRIVertexShader()
			: GRIShader(GRT_VertexShader)
		{
		}
	};

	class GRIFragmentShader : public GRIShader
	{
	public:
		GRIFragmentShader()
			: GRIShader(GRT_FragmentShader)
		{
		}
	};

	class GRIBuffer : public GRIResource
	{
	public:

	};
	// Thread safe ref ptr
	typedef RefCountPtr<GRIVertexShader> GRIVertexShaderRef;
	typedef RefCountPtr<GRIFragmentShader> GRIFragmentShaderRef;
}
