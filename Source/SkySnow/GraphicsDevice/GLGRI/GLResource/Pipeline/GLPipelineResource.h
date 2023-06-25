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
#include "GRIResourceCreateInfo.h"
#include <vector>
namespace SkySnow
{
	class GLGraphicPipeline : public GRIGraphicsPipeline
	{
	public:
        GLGraphicPipeline()
			: GRIGraphicsPipeline()
			, _PrimitiveType(PrimitiveType::PT_Num)
			, _ShaderPipeline(nullptr)
            , _VertexDescriptor(nullptr)
            , _UBODescriptor(nullptr)
		{
		}

        GLGraphicPipeline(const GRICreateGraphicsPipelineInfo& createInfo)
			: GRIGraphicsPipeline()
			, _PrimitiveType(createInfo._PrimitiveType)
            , _ShaderPipeline(createInfo._ShaderPipelineInfo._PipelineShader)
			, _VertexDescriptor(createInfo._ShaderPipelineInfo._VertexDescriptor)
			, _UBODescriptor(createInfo._ShaderPipelineInfo._UniformBufferDescriptor)
		{
		}

		virtual ~GLGraphicPipeline()
		{
            SN_LOG("GLGraphicPipeline DesConstruct.");
		}
        
        PrimitiveType GetPrimitiveType() const
        {
            return _PrimitiveType;
        }
        GLPipelineShader* GetPipelineShader()
        {
            return dynamic_cast<GLPipelineShader*>(_ShaderPipeline.GetReference());
        }
        GRIGLVertexDescriptor* GetVertexDescriptor()
        {
            return dynamic_cast<GRIGLVertexDescriptor*>(_VertexDescriptor.GetReference());
        }
        GRIGLUniformBufferDescriptor* GetUniformBufferDescriptor()
        {
            return dynamic_cast<GRIGLUniformBufferDescriptor*>(_UBODescriptor.GetReference());
        }
        //this function use for _PendingState,other not use this function
        void InitialPipelineState()
        {
            _Textures.resize(Max_Num_Texture_Unit);
            _Samplers.resize(Max_Num_Sampler_Unit);
        }
	public:
		PrimitiveType			        _PrimitiveType;
        GRIPipelineShaderRef            _ShaderPipeline;
        GRIVertexDescriptorRef          _VertexDescriptor;
        GRIUniformBufferDescriptorRef   _UBODescriptor;
        std::vector<GRITextureRef>      _Textures;
        std::vector<GRISamplerStateRef> _Samplers;
	};
    class GLComputePipeline : public GRIComputePipeline
    {
    public:
        
    };
}
