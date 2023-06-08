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
#include "GRIResourceCreateInfo.h"
namespace SkySnow
{
	PixelFormatInfo::PixelFormatInfo(
		PixelFormat inPFormat,
		const char* inName,
		int32	inBlockSizeX,
		int32	inBlockSizeY,
		int32	inBlockSizeZ,
		int32	inByteSize,
		int32	inNumComponents,
		bool	inIsSupport)
		: _Name(inName)
		, _PFormat(inPFormat)
		, _BlockSizeX(inBlockSizeX)
		, _BlockSizeY(inBlockSizeY)
		, _BlockSizeZ(inBlockSizeZ)
		, _ByteSize(inByteSize)
		, _NumComponents(inNumComponents)
		, _IsSupport(inIsSupport)
	{
	}
	PixelFormatInfo GPixelFormats[PF_End] =
	{
		//				PixelFormat             Name			BlockSizeX  BlockSizeY  BlockSizeZ  ByteSize  NumComponents    Supported
		PixelFormatInfo(PF_None,				"None",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R8,					"R8",				1,			1,			1,		   1,			1,			1),
		PixelFormatInfo(PF_R8_UINT,				"R8_UINT",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PR_R8_SINT,				"R8_SINT",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R16F,				"R16F",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R16F_FILTER,			"R16F_FILTER",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R16_UINT,			"R16_UINT",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R16_SINT,			"R16_SINT",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R32F,				"R32F",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R32_UINT,			"R32_UINT",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R32_SINT,			"R32_SINT",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R64_UINT,			"R64_UINT",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_G8,					"G8",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_G16,					"G16",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_A8,					"A8",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R8G8,				"R8G8",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R8G8_UINT,			"R8G8_UINT",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R16G16_UINT,			"R16G16_UINT",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R32G32_UINT,			"R32G32_UINT",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_G16R16,				"G16R16",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_G16R16F,				"G16R16F",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_G16R16F_FILTER,		"G16R16F_FILTER",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_G16R16_SNORM,		"G16R16_SNORM",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_G32R32F,				"G32R32F",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R5G6B5_UNORM,		"R5G6B5_UNORM",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R8G8B8A8,			"R8G8B8A8",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_RGB_Float,			"RGB_Float",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R11G11B10_Float,		"R11G11B10_Float",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R32G32B32_UINT,		"R32G32B32_UINT",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R32G32B32_SINT,		"R32G32B32_SINT",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R32G32B32F,			"R32G32B32F",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R8G8B8A8_UINT,		"R8G8B8A8_UINT",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R8G8B8A8_SNORM,		"R8G8B8A8_SNORM",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R16G16B16A16_UINT,	"R16G16B16A16_UINT",0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_R16G16B16A16_SINT,	"R16G16B16A16_SINT",0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_RGBA_Float,			"RGBA_Float",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_B5G5R5A1_UNORM,		"B5G5R5A1_UNORM",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_A8R8G8B8,			"A8R8G8B8",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_A16B16G16R16,		"A16B16G16R16",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_A2B10G10R10,			"A2B10G10R10",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_A32B32G32R32F,		"A32B32G32R32F",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ASTC_4x4,			"ASTC_4x4",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ASTC_6x6,			"ASTC_6x6",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ASTC_8x8,			"ASTC_8x8",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ASTC_10x10,			"ASTC_10x10",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ASTC_12x12,			"ASTC_12x12",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ETC1,				"ETC1",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ETC2_RGB,			"ETC2_RGB",			0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ETC2_RGBA,			"ETC2_RGBA",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ETC2_R11_EAC,		"ETC2_R11_EAC",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ETC2_RG11_EAC,		"ETC2_RG11_EAC",	0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_D24,					"D24",				0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_DepthStencil,		"DepthStencil",		0,			0,			0,		   0,			0,			0),
		PixelFormatInfo(PF_ShadowDepth,			"ShadowDepth",		0,			0,			0,		   0,			0,			0),
	};
}