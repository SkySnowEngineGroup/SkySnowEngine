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
			: m_GRIResourceType(EGRIResourceType::GRT_None)
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
			: GRIShader(EGRIResourceType::GRT_VertexShader)
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
			: GRIShader(EGRIResourceType::GRT_FragmentShader)
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
			: GRIResource(EGRIResourceType::GRT_Assembly)
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
			: GRIResource(EGRIResourceType::GRT_PipelineShaderState)
		{
		}
		virtual ~GRIPipelineShaderState()
		{
			SN_LOG("GRIPipelineShaderState Destruct.");
		}
	};
	//渲染Pipeline资源基类
	class GRIGraphicsPipeline : public GRIResource
	{
	public:
		GRIGraphicsPipeline()
			: GRIResource(EGRIResourceType::GRT_GraphicsPipeline)
		{
		}
		virtual ~GRIGraphicsPipeline()
		{
			SN_LOG("GRIGraphicsPipeline Destruct.");
		}
	};
    class GRIComputePipeline : public GRIResource
    {
    public:
        GRIComputePipeline()
            : GRIResource(EGRIResourceType::GRT_ComputePipeline)
        {
            
        }
        virtual ~GRIComputePipeline()
        {
            SN_LOG("GRIComputePipeline Destruct.");
        }
    };

	class GRIBuffer : public GRIResource
	{
	public:
		GRIBuffer()
			: GRIResource(EGRIResourceType::GRT_Buffer)
			, _UsageType(BufferUsageType::BUT_None)
			,_Size(0)
			, _Stride(0)
			, _BufferName("")
		{
		}
		GRIBuffer(BufferUsageType usage, int size, int stride)
			: GRIResource(EGRIResourceType::GRT_Buffer)
			, _UsageType(usage)
			, _Size(size)
			, _Stride(stride)
			, _BufferName("")
		{
		}
		virtual ~GRIBuffer()
		{
			SN_LOG("GRIBuffer Destruct.");
		}

		BufferUsageType GetBufferUsageType()
		{
			return _UsageType;
		}

		int GetStride()
		{
			return _Stride;
		}

		int GetSize()
		{
			return _Size;
		}

		void SetBufferName(const std::string bufferName)
		{
			_BufferName = bufferName;
		}

		bool IsDynamic() const
		{
			return (_UsageType & BufferUsageType::BUT_DynamicBuffer) != 0;
		}

		std::string GetBufferName()
		{
			return _BufferName;
		}

	protected:
		BufferUsageType _UsageType;
		int				_Size;
		int				_Stride;
		std::string		_BufferName;
	};

	class GRIVertexBindingDesc : public GRIResource
	{
	public:
		GRIVertexBindingDesc()
			: GRIResource(GRT_VertexBindingDesc)
		{
		}
		virtual ~GRIVertexBindingDesc()
		{
			SN_LOG("GRIVertexBindingDesc Destruct.");
		}
	};


	//shader type vertex fragement compute
	typedef RefCountPtr<GRIVertexShader>			GRIVertexShaderRef;
	typedef RefCountPtr<GRIFragmentShader>			GRIFragmentShaderRef;
	typedef RefCountPtr<GRIPipelineShaderState>		GRIPipelineShaderStateRef;
	//rendercomandbuffer
    typedef RefCountPtr<GRIGraphicsPipeline>        GRIGraphicsPipelineRef;
    //computecommandbuffer
	typedef RefCountPtr<GRIComputePipeline>	        GRIComputePipelineRef;
	//buffer type: vertex index texture  SSBO(Shader Storage Buffer Object)
	typedef class GRIBuffer							GRIIndexBuffer;
	typedef class GRIBuffer							GRIVertexBuffer;
	typedef RefCountPtr<GRIVertexBuffer>			GRIVertexBufferRef;
	typedef RefCountPtr<GRIIndexBuffer>				GRIIndexBufferRef;
	typedef RefCountPtr<GRIBuffer>					GRIBufferRef;
	typedef RefCountPtr<GRIVertexBindingDesc>		GRIVertexBindingDescRef;

}
