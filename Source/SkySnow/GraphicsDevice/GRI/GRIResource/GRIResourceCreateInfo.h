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
#include "Hash.h"
#include <vector>
#include <unordered_map>
namespace SkySnow
{
    class GRIVertexElement;
    struct UniformBufferSlot;
    typedef std::vector<GRIVertexElement> VertexDescriptorElementList;
    typedef std::unordered_map<size_t, UniformBufferSlot> UniformBufferList;
    class GRIVertexElement
    {
    public:
        GRIVertexElement()
            : _GRIBuffer(nullptr)
            , _BufferIndex(-1)
            , _Offset(0)
            , _Strid(0)
            , _AtttitubeIndex(0)
            , _VET_Type(VertexElementType::VET_None)
        {
        }
        GRIVertexElement(
           uint8_t inBufferIndex,
           uint8_t inAtttitubeIndex,
           uint8_t inStrid,
           uint8_t inOffset,
           VertexElementType inVET_Type,
           GRIBuffer* inGRIBuffer = nullptr
        )
            : _BufferIndex(inBufferIndex)
            , _GRIBuffer(inGRIBuffer)
            , _AtttitubeIndex(inAtttitubeIndex)
            , _Strid(inStrid)
            , _Offset(inOffset)
            , _VET_Type(inVET_Type)
        {
        }
        
        void operator=(const GRIVertexElement& other)
        {
            _BufferIndex    = other._BufferIndex;
            _Offset         = other._Offset;
            _Strid          = other._Strid;
            _AtttitubeIndex = other._AtttitubeIndex;
            _GRIBuffer      = other._GRIBuffer;
            _VET_Type       = other._VET_Type;
        }
        //buffer key
        uint8_t             _BufferIndex;       //数据存储的Key值
        uint8_t             _Offset;            //偏移量
        uint8_t             _Strid;             //间隔
        uint8_t             _AtttitubeIndex;    //顶点变量索引id
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
        {
        }
        GRICreateShaderPipelineInfo(
            GRIPipelineShader*       inPipelineShader,
            GRIVertexDescriptor*     inVertexDescriptor
        )
            : _PipelineShader(inPipelineShader)
            , _VertexDescriptor(inVertexDescriptor)
        {
        }
        GRIPipelineShader*       _PipelineShader;
        GRIVertexDescriptor*     _VertexDescriptor;
    };
    //Graphics Pipeline Create Info
	class GRICreateGraphicsPipelineInfo
	{
	public:
		GRICreateGraphicsPipelineInfo()
			: _BlendState(nullptr)
			, _RasterizerState(nullptr)
			, _DepthStencilState(nullptr)
			, _SamplerState(nullptr)
			, _AssemblyState(nullptr)
            , _UniformBufferDescriptor(nullptr)
			, _PrimitiveType(PrimitiveType::PT_Trangles)
		{
		}
		GRICreateGraphicsPipelineInfo(
			GRIBlendState*			    inBlendState,
			GRIRasterizerState*		    inRasterizerState,
			GRIDepthStencilState*	    inDepthStencilState,
			GRISamplerState*		    inSamplerState,
			GRIAssemblyState*		    inAssemblyState,
			PrimitiveType			    inPrimitiveType,
            GRIUniformBufferDescriptor* inUniformBufferDescriptor,
            GRICreateShaderPipelineInfo inShaderPipeline
		)
			: _ShaderPipelineInfo(inShaderPipeline)
            , _BlendState(inBlendState)
			, _RasterizerState(inRasterizerState)
			, _DepthStencilState(inDepthStencilState)
			, _SamplerState(inSamplerState)
			, _AssemblyState(inAssemblyState)
            , _UniformBufferDescriptor(inUniformBufferDescriptor)
			, _PrimitiveType(inPrimitiveType)
		{
		}

		bool operator==(const GRICreateGraphicsPipelineInfo& other) const
		{
			if (_BlendState != other._BlendState ||
				_RasterizerState != other._RasterizerState ||
				_DepthStencilState != other._DepthStencilState ||
				_SamplerState != other._SamplerState ||
				_AssemblyState != other._AssemblyState ||
                _ShaderPipelineInfo._PipelineShader != other._ShaderPipelineInfo._PipelineShader ||
                _ShaderPipelineInfo._VertexDescriptor != other._ShaderPipelineInfo._VertexDescriptor ||
                _UniformBufferDescriptor != other._UniformBufferDescriptor)
			{
				return false;
			}
			return true;
		}
		PrimitiveType			_PrimitiveType;

		GRIBlendState*			_BlendState;
		GRIRasterizerState*		_RasterizerState;
		GRIDepthStencilState*	_DepthStencilState;
		GRISamplerState*		_SamplerState;
		GRIAssemblyState*		_AssemblyState;
        
        GRIUniformBufferDescriptor* _UniformBufferDescriptor;
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
    
    struct UniformBufferSlot
    {
        //A single draw is a list of uniform buffer owned by the current draw
        UniformBufferUsageType  _UBType;
        size_t                  _UBHashKey;
    };
    //Create Uniform Buffer Descriptor Info
    //Depth RenderLoop Descriptor,or Light RenderLoop Descriptor ext
    class GRICreateUniformBufferDescriptorInfo
    {
    public:
        GRICreateUniformBufferDescriptorInfo()
        {
        }
        void AddUniformBuffer(uint8_t bufferIndex,const char* inName, UniformBufferUsageType inUBType)
        {
            UniformBufferSlot ubs;
            ubs._UBType     = inUBType;
            ubs._UBHashKey  = String2Hash(inName);
            _UniformBuffers[bufferIndex] = ubs;
        }

        const UniformBufferList& GetUniformBuffers()
        {
            return _UniformBuffers;
        }
    private:
        UniformBufferList _UniformBuffers;
    };
}
