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
#include "AtomicVar.h"
namespace SkySnow
{
	//Resource base class
    //as RefCounted base class, not extend RefCounted
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
		inline int Add()
		{
			int newCount = m_Atomic.Add(std::memory_order_acquire);
			return newCount;
		}
		//RefCount sub
		inline int Release()
		{
			int newCount = m_Atomic.Release(std::memory_order_release);
			if (newCount == 0)
			{
				ReclaimResource();
			}
			return newCount;
		}
		inline int RefCount()
		{
			return m_Atomic.GetCountRef(std::memory_order_relaxed);
		}
		inline bool IsValid()
		{
			return m_Atomic.IsValid(std::memory_order_relaxed);
		}
		//-----------------------------------------------------------
	public:
		static void FlushResourceRelease()
        {
            ResourceReclaim::Instance().RemoveReclaimResource();
        }
	private:
		void ReclaimResource()
		{
            ResourceReclaim::Instance().AddReclaimResource(this);
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
    //Texture
    //2D/2DArray  3D/3DArray  Cube
	class GRITexture : public GRIResource
	{
	public:
		GRITexture(EGRIResourceType grt, uint32 inNumMips, uint32 inNumSample, PixelFormat inFormat, TextureUsageType inTUT)
			: GRIResource(grt)
			, _NumMips(inNumMips)
			, _NumSamples(inNumSample)
			, _Format(inFormat)
			, _TextureUseType(inTUT)
		{
		}
		virtual ~GRITexture()
		{
			SN_LOG("GRITexture Destruct.");
		}

		uint32 GetNumMaps() const
		{
			return _NumMips;
		}

		uint32 GetNumSamples() const
		{
			return _NumSamples;
		}

		bool IsMultiSample() const
		{
			return _NumSamples > 1;
		}

		PixelFormat GetFormat() const
		{
			return _Format;
		}

		TextureUsageType GetTextureUsageType() const
		{
			return _TextureUseType;
		}
    private:
		uint32				_NumMips;
		uint32				_NumSamples;
        PixelFormat			_Format;
		TextureUsageType	_TextureUseType;
        
    };
    class GRITexture2D : public GRITexture
    {
    public:
        GRITexture2D(uint32 inSizeX,uint32 inSizeY,uint32 inNumMips, uint32 inNumSample, PixelFormat inFormat, TextureUsageType inTUT,EGRIResourceType grt = GRT_None)
            : GRITexture(grt != GRT_None ? grt : GRT_Texture2D,inNumMips,inNumSample,inFormat,inTUT)
			, _SizeX(inSizeX)
			, _SizeY(inSizeY)
        {
        }
        virtual ~GRITexture2D()
        {
            SN_LOG("GRITexture2D Destruct.");
        }
		uint32 GetSizeX() const
		{
			return _SizeX;
		}
		uint32 GetSizeY() const
		{
			return _SizeY;
		}
	private:
		uint32 _SizeX;
		uint32 _SizeY;
    };
    class GRITexture2DArray : public GRITexture2D
    {
    public:
        GRITexture2DArray(uint32 inSizeX, uint32 inSizeY,uint32 inSizeZ,uint32 inNumMips, uint32 inNumSample, PixelFormat inFormat, TextureUsageType inTUT)
            : GRITexture2D(inSizeX, inSizeY,inNumMips,inNumSample, inFormat, inTUT,GRT_Texture2DArray)
			, _SizeZ(inSizeZ)
        {
        }
        virtual ~GRITexture2DArray()
        {
            SN_LOG("GRITexture2DArray Destruct.");
        }
		uint32 GetSizeZ() const
		{
			return _SizeZ;
		}
	private:
		uint32 _SizeZ;
    };
    class GRITexture3D : public GRITexture
    {
    public:
        GRITexture3D(uint32 inSizeX, uint32 inSizeY, uint32 inSizeZ, uint32 inNumMips, uint32 inNumSample, PixelFormat inFormat, TextureUsageType inTUT)
            : GRITexture(GRT_Texture3D, inNumMips, 1, inFormat, inTUT)
			, _SizeX(inSizeX)
			, _SizeY(inSizeY)
			, _SizeZ(inSizeZ)
        {
        }
        virtual ~GRITexture3D()
        {
            SN_LOG("GRITexture3D Destruct.");
        }

		uint32 GetSizeX() const
		{
			return _SizeX;
		}
		uint32 GetSizeY() const
		{
			return _SizeY;
		}
		uint32 GetSizeZ() const
		{
			return _SizeZ;
		}
	private:
		uint32 _SizeX;
		uint32 _SizeY;
		uint32 _SizeZ;
    };
    class GRITextureCube : public GRITexture
    {
    public:
        GRITextureCube(uint32 inSize,uint32 inNumMips, uint32 inNumSample, PixelFormat inFormat, TextureUsageType inTUT)
            : GRITexture(GRT_TextureCube,inNumMips,1,inFormat,inTUT)
			, _Size(inSize)
        {
        }
        virtual ~GRITextureCube()
        {
            SN_LOG("GRITextureCube Destruct.");
        }
		uint32 GetSize() const
		{
			return _Size;
		}
	private:
		uint32 _Size;
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
			, _Size(0)
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
    ////图元装配状态
    //class GRIAssemblyState : public GRIResource
    //{
    //public:
    //    GRIAssemblyState()
    //        : GRIResource(EGRIResourceType::GRT_AssemblyState)
    //    {
    //    }
    //    virtual ~GRIAssemblyState()
    //    {
    //        SN_LOG("GRIAssembly DesConstruct.");
    //    }
    //};
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
	//RenderTarget---GRI Internal Use
	class GRIRenderTarget : public GRIResource
	{
	public:
		GRIRenderTarget()
			: GRIResource(EGRIResourceType::GRT_RenderTarget)
		{
		}
		virtual ~GRIRenderTarget()
		{
			SN_LOG("GRIRenderTarget DesConstruct.");
		}
	};
    //StateEnd===================================================================================
    //Texture: Texture2D/Array Texture3D/Array TextureCube
    typedef RefCountPtr<GRITexture>                 GRITextureRef;//Base class use for PipelineState
    typedef RefCountPtr<GRITexture2D>               GRITexture2DRef;
    typedef RefCountPtr<GRITexture2DArray>          GRITexture2DArrayRef;
    typedef RefCountPtr<GRITexture3D>               GRITexture3DRef;
    typedef RefCountPtr<GRITextureCube>             GRITextureCubeRef;
    //Sampler
    typedef RefCountPtr<GRISamplerState>            GRISamplerStateRef;
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
    //typedef RefCountPtr<GRIAssemblyState>           GRIAssemblyStateRef;
    typedef RefCountPtr<GRIRasterizerState>         GRIRasterizerStateRef;
    typedef RefCountPtr<GRIDepthStencilState>       GRIDepthStencilStateRef;
    typedef RefCountPtr<GRIBlendState>              GRIBlendStateRef;

    //OnScreen and OffScreen and MultiWindow
    class GRIViewportState : public GRIResource
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

        virtual void* GetDriveContext() = 0;

        virtual void* GetWindowHandle() = 0;

        virtual GRITexture2DRef GetBackBuffer() = 0;

        virtual PixelFormat GetWindowPixelFormat() const { return PF_None;}

        virtual uint32 GetWindowWidth() const { return 0;}

        virtual uint32 GetWindowHeight() const { return 0;}

        virtual bool IsFullScreen() const { return true; }
    private:
    };
    //OnScreen and OffScreen
    typedef RefCountPtr<GRIViewportState>           GRIViewportStateRef;
}
