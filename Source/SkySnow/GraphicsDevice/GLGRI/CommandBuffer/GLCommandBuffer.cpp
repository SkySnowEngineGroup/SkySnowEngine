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
#include "GLCommandBuffer.h"
#include "GLShader.h"
#include "GLShaderResource.h"
#include "GLBufferResource.h"
#include "GLPipelineResource.h"
#include "GRIPipelineCache.h"
#include "GRI.h"
namespace SkySnow
{
	GLRenderCommandBuffer::GLRenderCommandBuffer()
		: GRIRenderCommandBuffer()
	{
        _CMType = Render;
	}

	GLRenderCommandBuffer::~GLRenderCommandBuffer()
	{
	}

	void GLRenderCommandBuffer::CmdReset()
	{
        _StackMem.Flush();
        _NumCommands = 0;
        _Curr = nullptr;
        _Head = nullptr;
        _CMState = Invalid;
	}
	void GLRenderCommandBuffer::CmdBeginCommandBuffer()
	{

	}
	void GLRenderCommandBuffer::CmdEndCommandBuffer()
	{

	}

	void GLRenderCommandBuffer::CmdBeginRenderPass()
	{

	}
	void GLRenderCommandBuffer::CmdEndRenderPass()
	{

	}

	void GLRenderCommandBuffer::CmdBeginViewport()
	{
		Alloc_CommandSet(CmdBeginViewportCommand)();
	}

	void GLRenderCommandBuffer::CmdEndViewport()
	{
		Alloc_CommandSet(CmdEndViewportCommand)();
	}

	//ResourceSet====================================================================
	void GLRenderCommandBuffer::CmdSetBuffer(int bufferIndex, GRIBuffer* buffer, int offset)
	{
		Alloc_CommandSet(CmdSetBufferCommand)(bufferIndex, buffer, offset);
	}
	void GLRenderCommandBuffer::CmdDrawPrimitive(int numPrimitive, int numInstance)
	{
		Alloc_CommandSet(CmdDrawPrimitiveCommand)(numPrimitive, numInstance);
	}
	void GLRenderCommandBuffer::CmdSetPipelineShader(GRIPipelineShader* pipelineShaderState)
	{
		Alloc_CommandSet(CmdSetPipelineShaderCommand)(pipelineShaderState);
	}
	void GLRenderCommandBuffer::CmdSetGraphicsPipeline(GRIGraphicsPipeline* pipelineState)
	{
		Alloc_CommandSet(CmdSetGraphicsPipelineCommand)(pipelineState);
	}
	void GLRenderCommandBuffer::CmdResourceSetExecutor()
	{
        GRICommandBase* cmd = _Head;
        while (cmd)
        {
            cmd->ExecuteCommand(*this);
            cmd = cmd->_Next;
        }
        CmdReset();
	}
}
