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
//
#pragma once
#include "RefCounted.h"
#include "GRICommons.h"
#include "LogAssert.h"
#include "GRIResourceFree.h"
#include "SNAtomicVar.h"
namespace SkySnow
{
	//渲染资源基类
	class GRIResource //: public RefThreadSafeCounted
	{
	public:
		GRIResource()
			//: RefThreadSafeCounted()
			: m_GRIResourceType(GRT_None)
		{

		}
		GRIResource(EGRIResourceType grit)
			//: RefThreadSafeCounted()
			: m_GRIResourceType(grit)
		{
		}
		virtual ~GRIResource()
		{
			SN_LOG("GRIResource DesConstruct.");
		}
		inline EGRIResourceType GetType() const
		{
			return m_GRIResourceType;
		}
		//计数器相关方法
		//-----------------------------------------------------------
		int Add()
		{
			int newCount = m_Atomic.Add(std::memory_order_acquire);
			return newCount;
		}
		//该处将使用风险指针进行内存管理
		int Release()
		{
			int newCount = m_Atomic.Release(std::memory_order_release);
			if (newCount == 0)
			{
				ReclaimResource();
			}
			return newCount;
		}
		int GetRefCount()
		{
			return m_Atomic.GetCountRef(std::memory_order_relaxed);
		}
		bool IsValid()
		{
			return m_Atomic.IsValid(std::memory_order_relaxed);
		}
		//-----------------------------------------------------------
	public:
		static void FlushResourceRelease();
	private:
		void ReclaimResource()
		{
			delete this;
		}
	private:
		const EGRIResourceType	m_GRIResourceType;
		mutable AtomicCount		m_Atomic;
	};
	//Shader渲染资源基类
	class GRIShader : public GRIResource
	{
	public:
		GRIShader(EGRIResourceType grit)
			: GRIResource(grit)
		{
		}

		virtual ~GRIShader()
		{
			SN_LOG("GRIShader DesConstruct.");
		}
	};

	class GRIVertexShader : public GRIShader
	{
	public:
		GRIVertexShader()
			: GRIShader(GRT_VertexShader)
		{
		}
		virtual ~GRIVertexShader()
		{
			SN_LOG("GRIVertexShader DesConstruct.");
		}
	};

	class GRIFragmentShader : public GRIShader
	{
	public:
		GRIFragmentShader()
			: GRIShader(GRT_FragmentShader)
		{
		}
		virtual ~GRIFragmentShader()
		{
			SN_LOG("GRIFragmentShader DesConstruct.");
		}
	};

	class GRIAssembly : public GRIResource
	{
	public:
		GRIAssembly()
			: GRIResource(GRI_Assembly)
		{
		}
		virtual ~GRIAssembly()
		{
			SN_LOG("GRIAssembly DesConstruct.");
		}
	};
	//渲染PipelineShader资源基类
	class GRIPipelineShaderState : public GRIResource
	{
	public:
		GRIPipelineShaderState()
			: GRIResource(GRT_PipelineShaderState)
		{
		}
		virtual ~GRIPipelineShaderState()
		{
			SN_LOG("GRIPipelineShaderState Destruct.");
		}
	};
	//渲染Pipeline资源基类
	class GRIGraphicsPipelineState : public GRIResource
	{
	public:
		GRIGraphicsPipelineState()
			: GRIResource(GRT_GraphicsPipelineState)
		{
		}
		virtual ~GRIGraphicsPipelineState()
		{
			SN_LOG("GRIGraphicsPipelineState Destruct.");
		}

		int		_PrimitiveType;
	};

	class GRIBuffer : public GRIResource
	{
	public:
		GRIBuffer()
			: GRIResource(GRT_Buffer)
		{
		}
		GRIBuffer(BufferUsageType usage, int size, int stride)
			: GRIResource(GRT_Buffer)
			, m_UsageType(usage)
			, m_Size(size)
			, m_Stride(stride)
			, m_BufferName("")
		{
		}
		virtual ~GRIBuffer()
		{
			SN_LOG("GRIBuffer Destruct.");
		}

		BufferUsageType GetBufferUsageType()
		{
			return m_UsageType;
		}

		int GetStride()
		{
			return m_Stride;
		}

		int GetSize()
		{
			return m_Size;
		}

		void SetBufferName(const std::string bufferName)
		{
			m_BufferName = bufferName;
		}

		bool IsDynamic() const
		{
			return (m_UsageType & BUT_DynamicBuffer) != 0;
		}

		std::string GetBufferName()
		{
			return m_BufferName;
		}

	protected:
		BufferUsageType m_UsageType;
		int				m_Size;
		int				m_Stride;
		std::string		m_BufferName;
	};
	// Shader相关资源的智能指针
	typedef RefCountPtr<GRIVertexShader>			GRIVertexShaderRef;
	typedef RefCountPtr<GRIFragmentShader>			GRIFragmentShaderRef;
	typedef RefCountPtr<GRIPipelineShaderState>		GRIPipelineShaderStateRef;
	//在Draw之前，无GPU句柄及带GPU句柄的需进行资源设置或绑定
	typedef RefCountPtr<GRIGraphicsPipelineState>	GRIGraphicsPipelineStateRef;
	//Buffer相关的智能指针
	typedef class GRIBuffer							GRIIndexBuffer;
	typedef class GRIBuffer							GRIVertexBuffer;
	typedef RefCountPtr<GRIVertexBuffer>			GRIVertexBufferRef;
	typedef RefCountPtr<GRIIndexBuffer>				GRIIndexBufferRef;
	typedef RefCountPtr<GRIBuffer>					GRIBufferRef;

}
