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
	//��Ⱦ��Դ����
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
		//��������ط���
		//-----------------------------------------------------------
		int Add()
		{
			int newCount = m_Atomic.Add(std::memory_order_acquire);
			return newCount;
		}
		//�ô���ʹ�÷���ָ������ڴ����
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
	//Shader��Ⱦ��Դ����
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
	//��ȾPipelineShader��Դ����
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
	//��ȾPipeline��Դ����
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
	// Shader�����Դ������ָ��
	typedef RefCountPtr<GRIVertexShader>			GRIVertexShaderRef;
	typedef RefCountPtr<GRIFragmentShader>			GRIFragmentShaderRef;
	typedef RefCountPtr<GRIPipelineShaderState>		GRIPipelineShaderStateRef;
	//��Draw֮ǰ����GPU�������GPU������������Դ���û��
	typedef RefCountPtr<GRIGraphicsPipelineState>	GRIGraphicsPipelineStateRef;
	//Buffer��ص�����ָ��
	typedef class GRIBuffer							GRIIndexBuffer;
	typedef class GRIBuffer							GRIVertexBuffer;
	typedef RefCountPtr<GRIVertexBuffer>			GRIVertexBufferRef;
	typedef RefCountPtr<GRIIndexBuffer>				GRIIndexBufferRef;
	typedef RefCountPtr<GRIBuffer>					GRIBufferRef;

}
