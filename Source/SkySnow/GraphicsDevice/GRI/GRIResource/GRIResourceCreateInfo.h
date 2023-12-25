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
#include "GRICommons.h"
#include "GRIResource.h"
#include "HashUtil.h"
#include <vector>
#include <unordered_map>
#include "AllocatorBase.h"
namespace SkySnow
{
    struct UniformSlot;
    struct UniformBufferSlot;
    class VertexElementSlot;
    typedef std::vector<VertexElementSlot>  VertexElementList;
    typedef std::vector<UniformSlot>        UniformSlotList;
    typedef std::vector<UniformBufferSlot>  UniformBufferList;
    class VertexElementSlot
    {
    public:
        VertexElementSlot()
            : _GRIBuffer(nullptr)
            , _VESize(0)
            , _BufferIndex(-1)
            , _Offset(0)
            , _Strid(0)
            , _AttributeIndex(0)
            , _VET_Type(VertexElementType::VET_None)
        {
        }
        VertexElementSlot(
           uint8_t inBufferIndex,//VBO Index stream index
           uint8_t inAttributeIndex,//Vertex Attri
           uint8_t inStrid,
           uint8_t inOffset,
           VertexElementType inVET_Type,
           uint8_t _VESize = 0,
           GRIBuffer* inGRIBuffer = nullptr
        )
            : _BufferIndex(inBufferIndex)
            , _VESize(0)
            , _GRIBuffer(inGRIBuffer)
            , _AttributeIndex(inAttributeIndex)
            , _Strid(inStrid)
            , _Offset(inOffset)
            , _VET_Type(inVET_Type)
        {
        }
        
        void operator=(const VertexElementSlot& other)
        {
            _VESize         = other._VESize;
            _BufferIndex    = other._BufferIndex;
            _Offset         = other._Offset;
            _Strid          = other._Strid;
            _AttributeIndex = other._AttributeIndex;
            _GRIBuffer      = other._GRIBuffer;
            _VET_Type       = other._VET_Type;
        }
        //buffer key
        uint8_t             _VESize;            //顶点基础数据类型大小float\char
        uint8_t             _BufferIndex;       //数据存储的Key值
        uint8_t             _Offset;            //偏移量
        uint8_t             _Strid;             //间隔
        uint8_t             _AttributeIndex;    //顶点变量索引id
        GRIVertexBuffer*    _GRIBuffer;         //顶点数据对象
        VertexElementType   _VET_Type;          //数据类型
    };
    //Program Create Info
    class GRICreateShaderPipelineInfo
    {
    public:
        GRICreateShaderPipelineInfo()
            : _PipelineShader(nullptr)
            , _VertexDescriptor(nullptr)
            , _UniformBufferDescriptor(nullptr)
        {
            _Textures.resize(Max_Num_Texture_Unit);
            _Samplers.resize(Max_Num_Sampler_Unit);
        }
        GRICreateShaderPipelineInfo(
            GRIPipelineShader*       inPipelineShader,
            GRIVertexDescriptor*     inVertexDescriptor,
            GRIUniformBufferDescriptor* inUniformBufferDescriptor
        )
            : _PipelineShader(inPipelineShader)
            , _VertexDescriptor(inVertexDescriptor)
            , _UniformBufferDescriptor(inUniformBufferDescriptor)
        {
            _Textures.resize(Max_Num_Texture_Unit);
            _Samplers.resize(Max_Num_Sampler_Unit);
        }
        GRIPipelineShaderRef            _PipelineShader;
        GRIVertexDescriptorRef          _VertexDescriptor;
        GRIUniformBufferDescriptorRef   _UniformBufferDescriptor;
        std::vector<GRITextureRef>      _Textures;
        std::vector<GRISamplerStateRef> _Samplers;
    };
    //Graphics Pipeline Create Info
	class GRICreateGraphicsPipelineInfo
	{
	public:
		GRICreateGraphicsPipelineInfo()
			: _BlendState(nullptr)
			, _RasterizerState(nullptr)
			, _DepthStencilState(nullptr)
			, _SamplerState(nullptr)//, _AssemblyState(nullptr)
			, _PrimitiveType(PrimitiveType::PT_Trangles)
		{
		}
		GRICreateGraphicsPipelineInfo(
			GRIBlendState*			    inBlendState,
			GRIRasterizerState*		    inRasterizerState,
			GRIDepthStencilState*	    inDepthStencilState,
			GRISamplerState*		    inSamplerState,//GRIAssemblyState*            inAssemblyState,
			PrimitiveType			    inPrimitiveType,
            GRICreateShaderPipelineInfo inShaderPipeline
		)
			: _ShaderPipelineInfo(inShaderPipeline)
            , _BlendState(inBlendState)
			, _RasterizerState(inRasterizerState)
			, _DepthStencilState(inDepthStencilState)
			, _SamplerState(inSamplerState)//, _AssemblyState(inAssemblyState)
			, _PrimitiveType(inPrimitiveType)
		{
		}

		bool operator==(const GRICreateGraphicsPipelineInfo& other) const
		{
			if (_BlendState != other._BlendState ||
				_RasterizerState != other._RasterizerState ||
				_DepthStencilState != other._DepthStencilState ||
				_SamplerState != other._SamplerState ||//_AssemblyState != other._AssemblyState ||
                _ShaderPipelineInfo._PipelineShader != other._ShaderPipelineInfo._PipelineShader ||
                _ShaderPipelineInfo._VertexDescriptor != other._ShaderPipelineInfo._VertexDescriptor)
			{
				return false;
			}
			return true;
		}
		PrimitiveType			    _PrimitiveType;

		GRIBlendStateRef			_BlendState;
		GRIRasterizerStateRef		_RasterizerState;
		GRIDepthStencilStateRef	    _DepthStencilState;
		GRISamplerStateRef		    _SamplerState;
//		GRIAssemblyStateRef		    _AssemblyState;
        
        
        GRICreateShaderPipelineInfo _ShaderPipelineInfo;

	};
    //Create Compute Pipeline Info
    class GRICreateComputePipelineInfo
    {
	public:
		GRICreateComputePipelineInfo()
		{
		}
		bool operator==(const GRICreateGraphicsPipelineInfo& other) const
		{
			return true;
		}
    };
    //UniformBuffer Create About Info
    struct UniformSlot
    {
        UniformSlot(const char* inName,void* inData,uint8_t size)
            : _Hash(String2Hash(inName))
            , _Size(size)
        { 
            _Data = GMalloc::Alloc(size);
            std::memcpy(_Data, inData, size);
        }
        ~UniformSlot()
        {
        }

        void Release()
        {
            if (_Data)
            {
                GMalloc::Free(_Data);
            }
        }
        uint8_t _Size;
        void*   _Data;
        size_t  _Hash;
    };
    //Create Uniform Buffer Descriptor Info
    //Depth RenderLoop Descriptor,or Light RenderLoop Descriptor ext
    struct UniformBufferSlot
    {
        UniformBufferSlot(uint8_t inUBIndex,const char* inUBName,UniformBufferUsageType inType,GRIUniformBuffer* inUB = nullptr)
            : _UBIndex(inUBIndex)
            , _UBType(inType)
            , _UBHashKey(String2Hash(inUBName))
            , _UniformBuffer(inUB)
        {
        }
        //A single draw is a list of uniform buffer owned by the current draw
        uint8_t                 _UBIndex;
        UniformBufferUsageType  _UBType;
        size_t                  _UBHashKey;
        GRIUniformBufferRef     _UniformBuffer;
    };
    //Sampler Create Info
    struct SamplerState
    {
        SamplerState() {}
        SamplerState(
            SamplerFilter inFilter,
            SamplerAddressMode inAddressU   = SamplerAddressMode::SAM_Wrap,
            SamplerAddressMode inAddressV   = SamplerAddressMode::SAM_Wrap,
            SamplerAddressMode inAddressW   = SamplerAddressMode::SAM_Wrap,
            SamplerCompareFun  inCompareFun = SamplerCompareFun::SCF_Never,
            float inMipBias         = 0,
            float inMipmapLevel     = 0,
            float inMaxMipmapLevel  = FLT_MAX,
            int32 inMaxAnisotropy   = 0,
            int32 inBorderColor     = 0
            )
            : _Filter(inFilter)
            , _AddressU(inAddressU)
            , _AddressV(inAddressV)
            , _AddressW(inAddressW)
            , _CompareFun(inCompareFun)
            , _MipBias(inMipBias)
            , _MipmapLevel(inMipmapLevel)
            , _MaxMipmapLevel(inMaxMipmapLevel)
            , _MaxAnisotropy(inMaxAnisotropy)
            , _BorderColor(inBorderColor)
        {
        }

        friend bool operator== (const SamplerState& left, const SamplerState& right);
        SamplerFilter _Filter           = SamplerFilter::SF_Point;
        SamplerAddressMode _AddressU    = SamplerAddressMode::SAM_Wrap;
        SamplerAddressMode _AddressV    = SamplerAddressMode::SAM_Wrap;
        SamplerAddressMode _AddressW    = SamplerAddressMode::SAM_Wrap;
        SamplerCompareFun  _CompareFun  = SamplerCompareFun::SCF_Never;
        float _MipBias          = 0.0f;
        float _MipmapLevel      = 0.0f;
        float _MaxMipmapLevel   = FLT_MAX;
        int32 _MaxAnisotropy    = 0;
        int32 _BorderColor      = 0;
    };
    //Texture2D Update Sub Data
    struct Texture2DRegion
    {
        Texture2DRegion()
            : _OffsetX(0)
            , _OffsetY(0)
            , _DestX(0)
            , _DestY(0)
            , _Width(0)
            , _Height(0)
        {
        }
        Texture2DRegion(uint32 inDestX,uint32 inDestY,uint32 inOffsetX, uint32 inOffset, uint32 inWidth, uint32 inHeight)
            : _DestX(inDestX)
            , _DestY(inDestY)
            , _OffsetX(inOffsetX)
            , _OffsetY(inOffset)
            , _Width(inWidth)
            , _Height(inHeight)
        {
        }
        //offset in texture
        uint32 _OffsetX;
        uint32 _OffsetY;
        //image source data offset
        uint32 _DestX;
        uint32 _DestY;
        //target texture size
        uint32 _Width;
        uint32 _Height;
    };
    //Texture3D Update Sub Data
    struct Texture3DRegion
    {
        Texture3DRegion()
            : _OffsetX(0)
            , _OffsetY(0)
            , _OffsetZ(0)
            , _DestX(0)
            , _DestY(0)
            , _DestZ(0)
            , _Width(0)
            , _Height(0)
            , _Depth(0)
        {
        }
        Texture3DRegion(uint32 inDestX,uint32 inDestY,uint32 inDestZ,uint32 inOffsetX,uint32 inOffsetY,uint32 inOffsetZ,uint32 inWidth,uint32 inHeight,uint32 inDepth)
            : _DestX(inDestX)
            , _DestY(inDestY)
            , _DestZ(inDestZ)
            , _OffsetX(inOffsetX)
            , _OffsetY(inOffsetY)
            , _OffsetZ(inOffsetZ)
            , _Width(inWidth)
            , _Height(inHeight)
            , _Depth(inDepth)
        {
        }
        //offset in texture
        uint32 _OffsetX;
        uint32 _OffsetY;
        uint32 _OffsetZ;
        //image source data offset
        uint32 _DestX;
        uint32 _DestY;
        uint32 _DestZ;
        //target texture size
        uint32 _Width;
        uint32 _Height;
        uint32 _Depth;
    };
    //Pixel block size and byteSizes
	struct PixelFormatInfo
	{
		PixelFormatInfo() = delete;
        PixelFormatInfo(
            PixelFormat inPFormat,
            const char* inName,
            int32	inBlockSizeX,
            int32	inBlockSizeY,
            int32	inBlockSizeZ,
            int32	inByteSize,
            int32	inNumComponents,
            bool	inIsSupport,
            bool	inIsCompressed);

		const char* _Name;
		PixelFormat		_PFormat;
		int32			_BlockSizeX;
		int32			_BlockSizeY;
		int32			_BlockSizeZ;
		int32			_ByteSize;
		int32			_NumComponents;
		bool			_IsSupport;
        bool            _IsCompressed;
	};
    extern PixelFormatInfo GPixelFormats[PF_End];

    struct RasterizerStateInfo
    {
        friend bool operator== (const RasterizerStateInfo& left,const RasterizerStateInfo& right);
        RasterizerFillMode _FillMode;
        RasterizerCullMode _CullMode;
        float              _DepthBias;
        float              _SlopeScaleDepthBias;
        bool               _EnableMsaa;
        bool               _EnableLineAA;
    };

    struct DepthStencilStateInfo
    {
        DepthStencilStateInfo(
            bool inEnableDepthWrite = true,
            CompareFun inDepthTest = CF_LessEqual,
            bool inEnableFrontStencil = false,
            CompareFun inFrontStencilTest = CF_Always,
            StencilOp inFrontStencilFailSO = SO_Keep,
            StencilOp inFrontDepthFailSO = SO_Keep,
            StencilOp inFrontPassFailSO = SO_Keep,
            bool inEnableBackStencil = false,
            CompareFun inBackStencilTest = CF_Always,
            StencilOp inBackStencilFailSO = SO_Keep,
            StencilOp inBackDepthFailSO = SO_Keep,
            StencilOp inBackPassFailSO = SO_Keep,
            uint8 inStencilReadMask = 0xFF,
            uint8 inStencilWriteMask = 0xFF
            )
        {
        }
        friend bool operator== (const DepthStencilStateInfo& left, const DepthStencilStateInfo& right);
       
        bool        _EnableDepthWrite = true;
        CompareFun  _DepthTest = CF_LessEqual;

        bool        _EnableFrontStencil = false;
        CompareFun  _FrontStencilTest = CF_Always;
        StencilOp   _FrontStencilFailSO = SO_Keep;
        StencilOp   _FrontDepthFailSO = SO_Keep;
        StencilOp   _FrontPassFailSO = SO_Keep;

        bool        _EnableBackStencil = false;
        CompareFun  _BackStencilTest = CF_Always;
        StencilOp   _BackStencilFailSO = SO_Keep;
        StencilOp   _BackDepthFailSO = SO_Keep;
        StencilOp   _BackPassFailSO = SO_Keep;

        uint8       _StencilReadMask = 0xFF;
        uint8       _StencilWriteMask = 0xFF;
    };

    struct BlendStateInfo
    {

    };

    struct RenderTargetView
    {
        bool operator==(const RenderTargetView& other) const
        {
            return  _LSOp == other._LSOp &&
                    _Texture == other._Texture;
        }

        ERenderTargetLSOp   _LSOp;
        GRITextureRef       _Texture;
    };

    struct DiscardRenderTarget
    {
        bool operator==(const DiscardRenderTarget& other) const
        {
            return _Depth == other._Depth &&
                    _Stencil == other._Stencil &&
                    _ColorBitMask == other._ColorBitMask;
        }
        bool        _Depth;
        bool        _Stencil;
        uint32      _ColorBitMask;
    };
    struct DepthRenderTargetView
    {
        
        bool operator==(const DepthRenderTargetView& other) const
        {
            return _DepthLoadOp == other._DepthLoadOp &&
                    _DepthStoreOp == other._DepthStoreOp &&
                    _StencilLoadOp == other._StencilLoadOp &&
                    _StencilStoreOp == other._StencilStoreOp &&
                    _Texture == other._Texture;
        }
        RenderTargetLoadOp  _DepthLoadOp;
        RenderTargetStoreOp _DepthStoreOp;
        RenderTargetLoadOp  _StencilLoadOp;
        RenderTargetStoreOp _StencilStoreOp;
        GRITextureRef       _Texture;
    };

    struct RenderPassInfo
    {
        RenderPassInfo();

        RenderPassInfo(const RenderPassInfo& other);

        RenderPassInfo& operator=(const RenderPassInfo& other);

        DiscardRenderTarget     _DiscardRT;

        RenderTargetView        _ColorRTV[Max_RenderTarget_Textures];
        DepthRenderTargetView   _DepthStencilRTV;

        RenderTargetView        _ColorResolveRTV[Max_RenderTarget_Textures];
        DepthRenderTargetView   _DepthStencilResolveRTV;


    };
    struct DataMemory
    {
        uint8* _Data = nullptr;
        uint32 _DataSize = 0;
    };
    struct ResourceData
    {
    private:
        typedef void (*DeleteFunction)(void* ptr, void* userData);
    public:
        ResourceData(const char* resourceName = "")
            : _ResourceName(resourceName)
            , _DeleteFunction(nullptr)
            , _UserData(nullptr)
            , _DataMemory(nullptr)
            , _IsRef(false)
        {
        }
        //Copy Ext Data,and delete copy data ptr
        void MakeCopy(const void* data, uint32 size)
        {
            _IsRef = false;
            _DataMemory = new DataMemory();
            _DataMemory->_Data = (uint8*)GMalloc::Alloc(size);
            _DataMemory->_DataSize = size;
            std::memcpy(_DataMemory->_Data, data, size);
        }
        //not copy ext data,and call callBack function to delete data ptr
        void MakeRef(const void* data, uint32 size, DeleteFunction deleteFun = nullptr, void* userData = nullptr)
        {
            _DataMemory = new DataMemory();
            _DataMemory->_Data = (uint8*)data;
            _DataMemory->_DataSize = size;
            _DeleteFunction = deleteFun;
            _UserData = userData;
            _IsRef = true;
        }

        void Release()
        {
            if(_IsRef)
            {
                if(_DeleteFunction && _DataMemory)
                {
                    _DeleteFunction(_DataMemory->_Data,_UserData);
                }
                if(_DataMemory)
                {
                    delete _DataMemory;
                    _DataMemory = nullptr;
                }
            }
            else
            {
                if(_DataMemory)
                {
                    GMalloc::Free(_DataMemory->_Data);
                    delete _DataMemory;
                    _DataMemory = nullptr;
                }
            }
        }

        const char* GetResourceName()
        {
            return _ResourceName;
        }
        const uint8* GetResourceData() const
        {
            return _DataMemory ? _DataMemory->_Data : nullptr;
        }

        uint32 GetResourceSize() const
        {
            return _DataMemory ? _DataMemory->_DataSize : 0;
        }

        bool IsReference() const
        {
            return _IsRef;
        }
    private:
        DeleteFunction  _DeleteFunction;
        void*           _UserData;
        bool            _IsRef;
        const char*     _ResourceName;
        DataMemory*     _DataMemory;
    };
}
