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
	//Resource base class
	class GRIResource
	{
	public:
		GRIResource()
			: m_GRIResourceType(EGRIResourceType::GRT_None)
		{

		}
		GRIResource(EGRIResourceType grit)
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
		//RefCount add
		//-----------------------------------------------------------
		int Add()
		{
			int newCount = m_Atomic.Add(std::memory_order_acquire);
			return newCount;
		}
		//RefCount sub
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
	//Shader about
    //ShaderStart=====================================================================================
	class GRIShader : public GRIResource
	{
	public:
		GRIShader(EGRIResourceType grit, ShaderFrequency shaderFrequency)
			: GRIResource(grit)
			, _ShaderFrequency(shaderFrequency)
		{
		}

		virtual ~GRIShader()
		{
			SN_LOG("GRIShader DesConstruct.");
		}

		ShaderFrequency GetShaderFrequency() const
		{
			return _ShaderFrequency;
		}
	private:
		ShaderFrequency _ShaderFrequency;
	};
	//vertex\fragment\geometry
	class GRIGraphicsShader : public GRIShader
	{
	public:
		explicit GRIGraphicsShader(EGRIResourceType resourceType, ShaderFrequency shaderFrequency)
			: GRIShader(resourceType, shaderFrequency)
		{
		}
		virtual ~GRIGraphicsShader()
		{
			SN_LOG("GRIGraphicsShader DesConstruct.");
		}
	};
	class GRIVertexShader : public GRIGraphicsShader
	{
	public:
		GRIVertexShader()
			: GRIGraphicsShader(EGRIResourceType::GRT_VertexShader,ShaderFrequency::SF_Vertex)
		{
		}
		virtual ~GRIVertexShader()
		{
			SN_LOG("GRIVertexShader DesConstruct.");
		}
	};

	class GRIFragmentShader : public GRIGraphicsShader
	{
	public:
		GRIFragmentShader()
			: GRIGraphicsShader(EGRIResourceType::GRT_FragmentShader, ShaderFrequency::SF_Fragement)
		{
		}
		virtual ~GRIFragmentShader()
		{
			SN_LOG("GRIFragmentShader DesConstruct.");
		}
	};
    //ShaderEnd======================================================================================
	//Pipeline about
    //PipelineStateStart=============================================================================
	class GRIPipelineShader : public GRIResource
	{
	public:
		GRIPipelineShader()
			: GRIResource(EGRIResourceType::GRT_PipelineShaderState)
		{
		}
		virtual ~GRIPipelineShader()
		{
			SN_LOG("GRIPipelineShader Destruct.");
		}
	};
	//Graphics Pipeline state
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
    //Compute Pipeline State
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
    //PipelineStateEnd=============================================================================
    //Buffer about
    //BufferStart==================================================================================
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
    //顶点流描述
	class GRIVertexDescriptor : public GRIResource
	{
	public:
        GRIVertexDescriptor()
			: GRIResource(GRT_VertexDescriptor)
		{
		}
		virtual ~GRIVertexDescriptor()
		{
			SN_LOG("GRIVertexDescriptor Destruct.");
		}
	};
    //统一变量 Uniform Buffer
    class GRIUniformBuffer : public GRIResource
    {
    public:
        GRIUniformBuffer()
            : GRIResource(EGRIResourceType::GRT_UniformBuffer)
        {
        }
        virtual ~GRIUniformBuffer()
        {
            SN_LOG("GRIUniformBuffer Destruct.");
        }
    };
    //描述符 Uniform Buffer Declaration
    class GRIUniformBufferDescriptor : public GRIResource
    {
    public:
        GRIUniformBufferDescriptor()
            : GRIResource(GRT_UniformBufferDescriptor)
        {
        }
        virtual ~GRIUniformBufferDescriptor()
        {
            SN_LOG("GRIUniformBufferDescriptor Destruct.");
        }
    };
    //BufferEnd===================================================================================
    //State about
    //StateStart==================================================================================
    //图元装配状态
    class GRIAssemblyState : public GRIResource
    {
    public:
        GRIAssemblyState()
            : GRIResource(EGRIResourceType::GRT_AssemblyState)
        {
        }
        virtual ~GRIAssemblyState()
        {
            SN_LOG("GRIAssembly DesConstruct.");
        }
    };
    //光栅化状态
    class GRIRasterizerState : public GRIResource
    {
    public:
        GRIRasterizerState()
            : GRIResource(EGRIResourceType::GRT_RasterizerState)
        {
        }
        virtual ~GRIRasterizerState()
        {
            SN_LOG("GRIRasterizerState DesConstruct.");
        }
    };
    //深度模版状态
    class GRIDepthStencilState : public GRIResource
    {
    public:
        GRIDepthStencilState()
            : GRIResource(EGRIResourceType::GRT_DepthStencilState)
        {
        }
        virtual ~GRIDepthStencilState()
        {
            SN_LOG("GRIDepthStencilState DesConstruct.");
        }
    };
    //混合状态
    class GRIBlendState : public GRIResource
    {
    public:
        GRIBlendState()
            : GRIResource(EGRIResourceType::GRT_BlendState)
        {
        }
        virtual ~GRIBlendState()
        {
            SN_LOG("GRIBlendState DesConstruct.");
        }
    };
    //采样器状态
    class GRISamplerState : public GRIResource
    {
    public:
        GRISamplerState()
            : GRIResource(EGRIResourceType::GRT_SamplerState)
        {
        }
        virtual ~GRISamplerState()
        {
            SN_LOG("GRISamplerState DesConstruct.");
        }
    };
    //StateEnd===================================================================================
    //OnScreen and OffScreen
    class GRIViewportState : GRIResource
    {
    public:
        GRIViewportState()
            : GRIResource(EGRIResourceType::GRT_ViewportState)
        {
        }
        virtual ~GRIViewportState()
        {
            SN_LOG("GRIViewport DesConstruct.");
        }
    };
	//shader type vertex fragement compute
	typedef RefCountPtr<GRIVertexShader>			GRIVertexShaderRef;
	typedef RefCountPtr<GRIFragmentShader>			GRIFragmentShaderRef;
	typedef RefCountPtr<GRIPipelineShader>			GRIPipelineShaderRef;
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
	typedef RefCountPtr<GRIVertexDescriptor>		GRIVertexDescriptorRef;
    //UniformBuffer
    typedef RefCountPtr<GRIUniformBuffer>           GRIUniformBufferRef;
    typedef RefCountPtr<GRIUniformBufferDescriptor> GRIUniformBufferDescriptorRef;
    //rasterization assembly blend sampler DepthStencil
    typedef RefCountPtr<GRIAssemblyState>           GRIAssemblyStateRef;
    typedef RefCountPtr<GRIRasterizerState>         GRIRasterizerStateRef;
    typedef RefCountPtr<GRIDepthStencilState>       GRIDepthStencilStateRef;
    typedef RefCountPtr<GRIBlendState>              GRIBlendStateRef;
    //OnScreen and OffScreen
    typedef RefCountPtr<GRIViewportState>           GRIViewportStateRef;
}
