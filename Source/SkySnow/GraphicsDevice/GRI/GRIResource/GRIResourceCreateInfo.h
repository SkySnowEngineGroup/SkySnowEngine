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
namespace SkySnow
{
	class GRICreateGraphicsPipelineInfo
	{
	public:
		GRICreateGraphicsPipelineInfo()
			: _BlendState(nullptr)
			, _RasterizerState(nullptr)
			, _DepthStencilState(nullptr)
			, _SamplerState(nullptr)
			, _AssemblyState(nullptr)
			, _PrimitiveType(PrimitiveType::PT_Trangles)
			, _PipelineShader(nullptr)
			, _VertexDeclaration(nullptr)
		{
		}
		GRICreateGraphicsPipelineInfo(
			GRIBlendState*			inBlendState,
			GRIRasterizerState*		inRasterizerState,
			GRIDepthStencilState*	inDepthStencilState,
			GRISamplerState*		inSamplerState,
			GRIAssemblyState*		inAssemblyState,
			PrimitiveType			inPrimitiveType,
			GRIPipelineShader*		inPipelineShader,
			GRIVertexDeclaration*	inVertexDeclaration
		)
			: _BlendState(inBlendState)
			, _RasterizerState(inRasterizerState)
			, _DepthStencilState(inDepthStencilState)
			, _SamplerState(inSamplerState)
			, _AssemblyState(inAssemblyState)
			, _PrimitiveType(inPrimitiveType)
			, _PipelineShader(inPipelineShader)
			, _VertexDeclaration(inVertexDeclaration)
		{
		}
		size_t operator()(const GRICreateGraphicsPipelineInfo& other) const
		{
			return 0;
		}
		bool operator==(const GRICreateGraphicsPipelineInfo& other) const
		{
			if (_BlendState != other._BlendState ||
				_RasterizerState != other._RasterizerState ||
				_DepthStencilState != other._DepthStencilState ||
				_SamplerState != other._SamplerState ||
				_AssemblyState != other._AssemblyState ||
				_PipelineShader != other._PipelineShader ||
				_VertexDeclaration != other._VertexDeclaration)
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

		GRIPipelineShader*		_PipelineShader;
		GRIVertexDeclaration*	_VertexDeclaration;
	};
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
}
