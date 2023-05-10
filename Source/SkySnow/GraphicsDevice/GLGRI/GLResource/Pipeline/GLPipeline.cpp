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
#include "GLPipeline.h"
#include "GRIGLDrive.h"
#include "GLPipelineResource.h"
namespace SkySnow
{
	void GRIGLDrive::GRICreateGraphicsPipeline(const GRICreateGraphicsPipelineInfo& createInfo, GRIGraphicsPipelineRef& handle)
	{
        GLGraphicPipeline* glPipeline = dynamic_cast<GLGraphicPipeline*>(handle.GetReference());
        GLPipelineShader* shaderPipeline = dynamic_cast<GLPipelineShader*>(createInfo._ShaderPipelineInfo._PipelineShader);
        glPipeline->_PrimitiveType = createInfo._PrimitiveType;
        glPipeline->_OGLShaderPipeline = dynamic_cast<GLPipelineShader*>(createInfo._ShaderPipelineInfo._PipelineShader);
        glPipeline->_OGLShaderPipeline->_OGLVertexDeclaration = dynamic_cast<GRIGLVertexDeclaration*>(createInfo._ShaderPipelineInfo._VertexDeclaration);
	}

    void GRIGLDrive::GRICreateComputePipeline(const GRICreateComputePipelineInfo& createInfo,GRIComputePipelineRef& handle)
    {
    }
}
