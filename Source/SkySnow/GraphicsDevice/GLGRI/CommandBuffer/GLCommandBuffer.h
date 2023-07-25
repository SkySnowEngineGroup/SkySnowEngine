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
#include "GRILowerCommandBuffer.h"
#include "GRICommandBuffer.h"
namespace SkySnow
{
	class GLRenderCommandBuffer : public GRIRenderCommandBuffer, public GRISetCommandBuffer
	{
	public:
		GLRenderCommandBuffer();

		~GLRenderCommandBuffer();

		virtual void CmdReset() final override;
		virtual void CmdBeginCommandBuffer() final override;
		virtual void CmdEndCommandBuffer() final override;

		virtual void CmdBeginRenderPass() final override;
		virtual void CmdEndRenderPass() final override;
	public:
		//globle set
		virtual void CmdBeginViewport(GRIViewportStateRef& viewPort, GRITexture2DRef& renderTexture) final override;
		virtual void CmdEndViewport(GRIViewportStateRef& viewPort, bool present, bool lockToVsync) final override;
	

		virtual void CmdResourceSetExecutor() final override;
	public://Create Resource
		virtual void CmdSetBuffer(int bufferIndex, GRIBufferRef& buffer, int offset) final override;
		virtual void CmdDrawPrimitive(int numPrimitive, int numInstance) final override;
		virtual void CmdSetPipelineShader(GRIPipelineShaderRef& pipelineShaderState) final override;
		virtual void CmdSetGraphicsPipeline(GRIGraphicsPipelineRef& pipelineState) final override;
        
        virtual void CmdSetShaderParameter(GRIPipelineShaderRef& graphicsShader, GRIUniformBufferRef& buffer,int32_t bufferIndex) final override;
        virtual void CmdUpdateUniformBuffer(GRIUniformBufferRef& buffer,const UniformSlotList& contents) final override;
        virtual void CmdSetUniformBufferDescriptor(GRIUniformBufferDescriptorRef& descriptor) final override;
        virtual void CmdSetShaderTexture(GRIPipelineShaderRef& graphicsShader,GRITextureRef& texture,uint32 textureIndex) final override;
        virtual void CmdSetShaderSampler(GRIPipelineShaderRef& graphicsShader,GRISamplerStateRef& sampler,uint32 samplerIndex) final override;
	private:

	};

    class GLCommandBufferPool
    {
    public:
        
    };

}
