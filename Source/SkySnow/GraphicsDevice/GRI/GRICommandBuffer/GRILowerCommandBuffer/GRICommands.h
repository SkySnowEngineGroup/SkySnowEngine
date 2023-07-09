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
#include "GRIResource.h"
#include "GRIResourceCreateInfo.h"
namespace SkySnow
{
	/*
	 *These instructions are data structures encapsulated for OpenGL 
	 *and lower versions of dx. They are not required for metal&vulkan&dx12. 
	 *The unified interface encapsulated in CommandBuffer delivers rendering 
	 *instructions directly to the gpu
	*/
	class GRICommandBufferBase;
	struct GRICommandBase
	{
		virtual void ExecuteCommand(GRICommandBufferBase& cmdBuffer) = 0;
		GRICommandBase* _Next = nullptr;
	};

	template<typename T>
	struct GRICommand : public GRICommandBase
	{
	public:
		void ExecuteCommand(GRICommandBufferBase& cmdBuffer) override final
		{
			T* cmd = static_cast<T*>(this);
			cmd->Execute(cmdBuffer);
			cmd->~T();
		}
	};
    //RenderDrive Interface
	//======================================================================================================================
	struct GRINullCommand : public GRICommand<GRINullCommand>
	{
		void Execute(GRICommandBufferBase& cmdBuffer) {}
	};
	//======================================================================================================================
	// render pipeline control
	struct CmdBeginViewportCommand : public GRICommand<CmdBeginViewportCommand>
	{
		void Execute(GRICommandBufferBase& cmdBuffer);
	};
	struct CmdEndViewportCommand : public GRICommand<CmdEndViewportCommand>
	{
		void Execute(GRICommandBufferBase& cmdBuffer);
	};
	//======================================================================================================================
	// RenderResource Set 
	struct CmdSetBufferCommand : public GRICommand<CmdSetBufferCommand>
	{
		CmdSetBufferCommand(int BufferInfoId, GRIBufferRef& buffer, int offset)
			: _BufferInfoId(BufferInfoId)
			, _Offset(offset)
			, _Buffer(buffer)
		{

		}
		void Execute(GRICommandBufferBase& cmdBuffer);

		int _BufferInfoId;
		int _Offset;
		GRIBufferRef _Buffer;	
	};
	struct CmdDrawPrimitiveCommand : public GRICommand<CmdDrawPrimitiveCommand>
	{
		CmdDrawPrimitiveCommand(int numPrimitive, int numInstance)
			: _NumPrimitive(numPrimitive)
			, _NumInstance(numInstance)
		{
		}
		void Execute(GRICommandBufferBase& cmdBuffer);
		int _NumPrimitive;
		int _NumInstance;
	};
	struct CmdSetPipelineShaderCommand : public GRICommand<CmdSetPipelineShaderCommand>
	{
		CmdSetPipelineShaderCommand(GRIPipelineShaderRef& pipelineShaderState)
			: _PipelineShaderState(pipelineShaderState)
		{
		}
		void Execute(GRICommandBufferBase& cmdBuffer);
		GRIPipelineShaderRef _PipelineShaderState;
	};

	struct CmdSetGraphicsPipelineCommand : public GRICommand<CmdSetGraphicsPipelineCommand>
	{
		CmdSetGraphicsPipelineCommand(GRIGraphicsPipelineRef& pipelineState)
			: _PipelineState(pipelineState)
		{
		}
		void Execute(GRICommandBufferBase& cmdBuffer);
		GRIGraphicsPipelineRef _PipelineState;
	};

    struct CmdSetShaderParameterCommand : public GRICommand<CmdSetShaderParameterCommand>
    {
        CmdSetShaderParameterCommand(GRIPipelineShaderRef& graphicsShader, GRIUniformBufferRef& buffer,int32_t bufferIndex)
            : _PipelineShader(graphicsShader)
            , _UniformBuffer(buffer)
            , _UBIndex(bufferIndex)
        {
        }
        void Execute(GRICommandBufferBase& cmdBuffer);
        GRIPipelineShaderRef _PipelineShader;
        GRIUniformBufferRef _UniformBuffer;
        int32_t                 _UBIndex;
    };
    struct CmdUpdateUniformBufferCommand : public GRICommand<CmdUpdateUniformBufferCommand>
    {
        CmdUpdateUniformBufferCommand(GRIUniformBufferRef& buffer,const UniformSlotList& contents)
            : _UniformBuffer(buffer)
            , _UBData(contents)
        {
        }
        void Execute(GRICommandBufferBase& cmdBuffer);
        GRIUniformBufferRef _UniformBuffer;
        UniformSlotList   _UBData;
    };
    struct CmdSetUniformBufferDescriptorCommand : public GRICommand<CmdSetUniformBufferDescriptorCommand>
    {
        CmdSetUniformBufferDescriptorCommand(GRIUniformBufferDescriptorRef& descriptor)
            : _UBDescriptor(descriptor)
        {
        }
        void Execute(GRICommandBufferBase& cmdBuffer);
        GRIUniformBufferDescriptorRef _UBDescriptor;
    };
    struct CmdSetShaderTextureCommand : public GRICommand<CmdSetShaderTextureCommand>
    {
        CmdSetShaderTextureCommand(GRIPipelineShaderRef& graphicsShader,GRITextureRef& texture,uint32 textureIndex)
            : _ShaderPipeline(graphicsShader)
            , _Texture(texture)
            , _TextureIndex(textureIndex)
        {
        }
        void Execute(GRICommandBufferBase& cmdBuffer);
        GRIPipelineShaderRef _ShaderPipeline;
        GRITextureRef		 _Texture;
        uint32				 _TextureIndex;
    };

    struct CmdSetShaderSamplerCommand : public GRICommand<CmdSetShaderSamplerCommand>
    {
        CmdSetShaderSamplerCommand(GRIPipelineShaderRef& graphicsShader,GRISamplerStateRef& sampler,uint32 samplerIndex)
            : _ShaderPipeline(graphicsShader)
            , _Sampler(sampler)
            , _SamplerIndex(samplerIndex)
        {
        }
        void Execute(GRICommandBufferBase& cmdBuffer);
        GRIPipelineShaderRef _ShaderPipeline;
        GRISamplerStateRef	 _Sampler;
        uint32				 _SamplerIndex;
    };
	//======================================================================================================================
	// RenderResource Create
	// CreateVertexShader
	struct GRICreateVertexShaderCommand : public GRICommand<GRICreateVertexShaderCommand>
	{
        GRICreateVertexShaderCommand(GRIVertexShaderRef& handle,const char* vsCode)
			: _VsCode(vsCode)
			, _Handle(handle)
		{
		}
		void Execute(GRICommandBufferBase& cmdBuffer);

		const char*			_VsCode;
		GRIVertexShaderRef	_Handle;
	};

	struct GRICreateFragmentShaderCommand : public GRICommand<GRICreateFragmentShaderCommand>
	{
		GRICreateFragmentShaderCommand(GRIFragmentShaderRef& handle, const char* vsCode)
			: _FsCode(vsCode)
			, _Handle(handle)
		{
		}
		void Execute(GRICommandBufferBase& cmdBuffer);

		const char*				_FsCode;
		GRIFragmentShaderRef	_Handle;
	};

	struct GRICreatePipelineShaderCommand : public GRICommand<GRICreatePipelineShaderCommand>
	{
		GRICreatePipelineShaderCommand(GRIPipelineShaderRef& handle)
			: _Handle(handle)
		{
		}
		void Execute(GRICommandBufferBase& cmdBuffer);
		GRIPipelineShaderRef _Handle;
	};

	struct GRICreateBufferCommand : public GRICommand<GRICreateBufferCommand>
	{
		GRICreateBufferCommand(GRIBufferRef& handle,BufferUsageType usageType, int size, int stride, void* data)
			: _Handle(handle)
			, _UsageType(usageType)
			, _Size(size)
			, _Stride(stride)
			, _Data(data)
		{
		}

		void Execute(GRICommandBufferBase& cmdBuffer);
		BufferUsageType _UsageType;
		int				_Size;
		int				_Stride;
		void*			_Data;
		GRIBufferRef	_Handle;
	};

	struct GRICreateGraphicsPipelineCommand : public GRICommand<GRICreateGraphicsPipelineCommand>
	{
        GRICreateGraphicsPipelineCommand(const GRICreateGraphicsPipelineInfo& createInfo, GRIGraphicsPipelineRef& handle)
			: _PsoInfo(createInfo)
			, _Handle(handle)
		{

		}
		void Execute(GRICommandBufferBase& cmdBuffer);

        GRICreateGraphicsPipelineInfo   _PsoInfo;
		GRIGraphicsPipelineRef          _Handle;
	};
    //Create VertexDesc
    struct GRICreateVertexDescriptorCommand : public GRICommand<GRICreateVertexDescriptorCommand>
    {
        //const VertexDeclarationElementList& vdel
        GRICreateVertexDescriptorCommand(const VertexElementList& vdel,GRIVertexDescriptorRef& handle)
            : _VertexElementList(vdel)
            , _Handle(handle)
        {
        }
        void Execute(GRICommandBufferBase& cmdBuffer);
        GRIVertexDescriptorRef         _Handle;
        VertexElementList              _VertexElementList;
    };

    struct GRICreateUniformBufferCommand : public GRICommand<GRICreateUniformBufferCommand>
    {
        GRICreateUniformBufferCommand(const UniformSlotList& contents,const char* ubName,UniformBufferUsageType ubType,GRIUniformBufferRef& handle)
            : _USlotList(contents)
            , _UBName(const_cast<char*>(ubName))
            , _UBType(ubType)
            , _Handle(handle)
        {
        }
        void Execute(GRICommandBufferBase& cmdBuffer);
        char*                   _UBName;
        UniformBufferUsageType  _UBType;
        UniformSlotList         _USlotList;
        GRIUniformBufferRef     _Handle;
    };

    struct GRICreateUniformDescriptorCommand : public GRICommand<GRICreateUniformDescriptorCommand>
    {
        GRICreateUniformDescriptorCommand(const UniformBufferList& ubl,GRIUniformBufferDescriptorRef& handle)
            : _UBSlotList(ubl)
            , _Handle(handle)
        {
        }
        void Execute(GRICommandBufferBase& cmdBuffer);
        
        UniformBufferList               _UBSlotList;
        GRIUniformBufferDescriptorRef   _Handle;
    };

	struct GRICreateTexture2DCommand : public GRICommand<GRICreateTexture2DCommand>
	{
		GRICreateTexture2DCommand(uint32 sizex, uint32 sizey, uint8 format, uint32 numMips, uint32 numSamples, TextureUsageType usageType, uint8* data, GRITexture2DRef& handle)
			: _Sizex(sizex)
			, _Sizey(sizey)
			, _Format(format)
			, _NumMips(numMips)
			, _NumSamples(numSamples)
			, _UsageType(usageType)
			, _Data(data)
			, _Handle(handle)
		{
		}

		void Execute(GRICommandBufferBase& cmdBuffer);

		uint32				_Sizex;
		uint32				_Sizey; 
		uint8				_Format; 
		uint32				_NumMips;
		uint32				_NumSamples; 
		TextureUsageType	_UsageType; 
		uint8*				_Data;
		GRITexture2DRef		_Handle;
	};

	struct GRICreateTexture2DArrayCommand : public GRICommand<GRICreateTexture2DArrayCommand>
	{
		GRICreateTexture2DArrayCommand(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips, uint32 numSamples, TextureUsageType usageType, uint8* data, GRITexture2DArrayRef& handle)
			: _Sizex(sizex)
			, _Sizey(sizey)
			, _Sizez(sizez)
			, _Format(format)
			, _NumMips(numMips)
			, _NumSamples(numSamples)
			, _UsageType(usageType)
			, _Data(data)
			, _Handle(handle)
		{
		}

		void Execute(GRICommandBufferBase& cmdBuffer);

		uint32					_Sizex; 
		uint32					_Sizey; 
		uint32					_Sizez; 
		uint8					_Format; 
		uint32					_NumMips; 
		uint32					_NumSamples; 
		TextureUsageType		_UsageType; 
		uint8*					_Data; 
		GRITexture2DArrayRef	_Handle;
	};
	struct GRICreateTexture3DCommand : GRICommand<GRICreateTexture3DCommand>
	{
		GRICreateTexture3DCommand(uint32 sizex, uint32 sizey, uint32 sizez, uint8 format, uint32 numMips, TextureUsageType usageType, uint8* data, GRITexture3DRef& handle)
			: _Sizex(sizex)
			, _Sizey(sizey)
			, _Sizez(sizez)
			, _Format(format)
			, _NumMips(numMips)
			, _UsageType(usageType)
			, _Data(data)
			, _Handle(handle)
		{
		}

		void Execute(GRICommandBufferBase& cmdBuffer);

		uint32				_Sizex; 
		uint32				_Sizey; 
		uint32				_Sizez; 
		uint8				_Format; 
		uint32				_NumMips; 
		TextureUsageType	_UsageType; 
		uint8*				_Data; 
		GRITexture3DRef		_Handle;
	};

	struct GRICreateTextureCubeCommand : GRICommand<GRICreateTextureCubeCommand>
	{
		GRICreateTextureCubeCommand(uint32 size, uint8 format, uint32 numMips, TextureUsageType usageType, uint8* data, GRITextureCubeRef& handle)
			: _Size(size)
			, _Format(format)
			, _NumMips(numMips)
			, _UsageType(usageType)
			, _Data(data)
			, _Handle(handle)
		{
		}

		void Execute(GRICommandBufferBase& cmdBuffer);

		uint32				_Size; 
		uint8				_Format; 
		uint32				_NumMips; 
		TextureUsageType	_UsageType; 
		uint8*				_Data; 
		GRITextureCubeRef	_Handle;
	};

	struct GRICreateSamplerCommand : public GRICommand<GRICreateSamplerCommand>
	{
		GRICreateSamplerCommand(const SamplerState& sState, GRISamplerStateRef& handle)
			: _State(sState)
			, _Handle(handle)
		{
		}

		void Execute(GRICommandBufferBase& cmdBuffer);

		SamplerState		_State; 
		GRISamplerStateRef	_Handle;
	};
}
