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

namespace SkySnow
{
#define Max_Num_Vertex_Attribute 16
#define Max_ShaderPipeline_UniformBuffer 6
	enum GRIFeature
	{
		ENone,
		EVulkan,
		EMetal,
		EDx9, //not support
		EDx10,//not support
		EDx11,//not support
		EDX12,//not support
		EGLES,
		EOpenGL,
		ENum
	};

	enum EGRIResourceType
	{
		GRT_None,
		GRT_VertexShader,
		GRT_FragmentShader,
		GRT_PipelineShaderState,
		GRT_GraphicsPipeline,
        GRT_ComputePipeline,
		GRT_Buffer,
        GRT_UniformBuffer,
        GRT_UniformBufferDescriptor,
        GRT_VertexDescriptor,
		GRT_AssemblyState,
        GRT_RasterizerState,
        GRT_DepthStencilState,
        GRT_BlendState,
        GRT_SamplerState,
        GRT_ViewportState,
		GRT_Num
	};

	enum ShaderFrequency
	{
		SF_Vertex		= 0,
		SF_Fragement	= 1,
	};

	enum BufferUsageType
	{
		BUT_None				= 0,
		BUT_VertexBuffer		= 1 << 0,
		BUT_IndexBuffer			= 1 << 1,
		BUT_DynamicBuffer		= 1 << 2,
		BUT_StructuredBuffer	= 1 << 3,
	};
    
    enum class UniformBufferUsageType
    {
        //used for single drawcall then discard
        UBT_SingleDraw = 0,
        //used for multi drawcall at once frame then discard
        UBT_SingleFrame,
        //used for multi drawcall at multi frame
        UBT_MultiFrame
    };
    enum class VertexElementType
    {
        VET_None,
        VET_Float1,
        VET_Float2,
        VET_Float3,
        VET_Float4,
        VET_Max
    };
	enum class PrimitiveType
	{
		PT_Lines,
		PT_Point_Strip,
		PT_Trangles,
		PT_Trangle_Strip,
		PT_Num,
	};
}
