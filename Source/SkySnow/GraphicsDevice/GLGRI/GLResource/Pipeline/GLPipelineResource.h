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
#include "GLProfiles.h"
#include "GRIResource.h"
#include "GLShaderResource.h"
#include "GLBufferResource.h"
#include "GLBuffer.h"
#include "GLShader.h"
#include "GRIResourceCreateInfo.h"
namespace SkySnow
{
	class GLPipelineShaderState : public GRIPipelineShaderState
	{
	public:
		GLPipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs)
			: GRIPipelineShaderState()
			, _ProgramId(0)
			, _OGLVertexShader(dynamic_cast<GLVertexShader*>(vs))
			, _OGLFragmentShader(dynamic_cast<GLFragmentShader*>(fs))
		{
		}

		inline GLVertexShader* GetVertexShader() { return _OGLVertexShader; }
		inline GLFragmentShader* GetFragmentShader() { return _OGLFragmentShader; }

		const GLShaderBase* GetShader(ShaderFrequency sf)
		{
			switch (sf)
			{
			case SkySnow::SF_Vertex:
				return GetVertexShader();
				break;
			case SkySnow::SF_Fragement:
				return GetFragmentShader();
				break;
			default:
				break;
			}
			return nullptr;
		}
	public:
		GLuint _ProgramId;
	private:
		//Cache Array or LRUCache
		//temp is ptr
		GLVertexShader*     _OGLVertexShader;
		GLFragmentShader*   _OGLFragmentShader;
		
	};
    
	class GLGraphicPipeline : public GRIGraphicsPipeline
	{
	public:
        GLGraphicPipeline()
			: GRIGraphicsPipeline()
			, _PrimitiveType(PrimitiveType::PT_Num)
		{
		}

        GLGraphicPipeline(const GRICreateGraphicsPipelineInfo& createInfo)
			: GRIGraphicsPipeline()
			, _PrimitiveType(createInfo._PrimitiveType)
		{
		}

		virtual ~GLGraphicPipeline()
		{
		}
	public:
		GLBufferInfo			_BufferInfo[Num_GL_Vertex_Attribute];
		GLShaderStateInfo		_ShaderStateInfo;
		PrimitiveType			_PrimitiveType;
	};
    class GLComputePipeline : public GRIComputePipeline
    {
    public:
        
    };

    class GLPipelineCache
	{
	public:
	};
}
