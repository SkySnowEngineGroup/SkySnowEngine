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
#include "VarType.h"
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
        GRT_Texture2D,
        GRT_Texture2DArray,
        GRT_Texture3D,
        GRT_Texture3DArray,
        GRT_TextureCube,
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
		UBT_None = 0,
        //used for single drawcall then discard; uv is uniform variable
		UBT_UV_SingleDraw,
        UBT_SingleDraw,
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
	enum class SamplerFilter
	{
		SF_Point,
		SF_Bilinear,
		SF_Trilinear,
		SF_AnisotropicPoint
	};
	enum class SamplerAddressMode
	{
		SAM_Wrap,
		SAM_Clamp,
		SAM_Mirror,
		SAM_Border
	};
	enum class TextureUsageType : uint64
	{
		//No Use
		TUT_None = 0,
		//As RT Resolve
		TUT_RenderTarget	            = 1 << 0,
		//Use a Shader Resource
		TUT_ShaderResource	            = 1 << 1,
		TUT_sRGB			            = 1 << 2,
        TUT_DepthStencilRenderTarget    = 1 << 3,
        //MRT to normal rt
        TUT_ResolveRenderTarget         = 1 << 4
	};

	enum PixelFormat
	{
		PF_None,
		PF_R8,
		PF_R8_UINT,
		PR_R8_SINT,
		PF_R16F,
		PF_R16F_FILTER,
		PF_R16_UINT,
		PF_R16_SINT,
		PF_R32F,
		PF_R32_UINT,
		PF_R32_SINT,
		PF_R64_UINT,
		PF_G8,
		PF_G16,
		PF_A8,
		PF_R8G8,
		PF_R8G8_UINT,
		PF_R16G16_UINT,
		PF_R32G32_UINT,
		PF_G16R16,
		PF_G16R16F,
		PF_G16R16F_FILTER,
		PF_G16R16_SNORM,
		PF_G32R32F,
		PF_R5G6B5_UNORM,
		PF_R8G8B8A8,
		PF_RGB_Float,
		PF_R11G11B10_Float,
		PF_R32G32B32_UINT,
		PF_R32G32B32_SINT,
		PF_R32G32B32F,
		PF_R8G8B8A8_UINT,
		PF_R8G8B8A8_SNORM,
		PF_R16G16B16A16_UINT,
		PF_R16G16B16A16_SINT,
		PF_RGBA_Float,
		PF_B5G5R5A1_UNORM,
		PF_A8R8G8B8,
		PF_A16B16G16R16,
		PF_A2B10G10R10,
		PF_A32B32G32R32F,
		PF_ASTC_4x4,//8.00 bpp
		PF_ASTC_6x6,//3.56 bpp
		PF_ASTC_8x8,//2.00 bpp
		PF_ASTC_10x10,//1.28 bpp
		PF_ASTC_12x12,//0.89 bpp
		PF_ETC1,
		PF_ETC2_RGB,
		PF_ETC2_RGBA,
		PF_ETC2_R11_EAC,
		PF_ETC2_RG11_EAC,
		PF_D24,
		PF_DepthStencil,
		PF_ShadowDepth,
		PF_End
	};
}
