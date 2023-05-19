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
#include "GRIGLDrive.h"
#include "GLShader.h"
namespace SkySnow
{
	GRIGLDrive::GRIGLDrive()
		: _GLContext(nullptr)
	{
	}
    GRIGLDrive::~GRIGLDrive()
    {
        if(_GLContext)
        {
            delete  _GLContext;
            _GLContext = nullptr;
        }
    }
    void GRIGLDrive::Init()
    {
#if PLATFORM == PLATFORM_WINDOW
        _GLContext = new GLContextWin();
#elif PLATFORM == PLATFORM_IOS
        _GLContext = new GLContextIos();
#elif PLATFORM == PLATFORM_MAC
        _GLContext = new GLContextMac();
#elif PLATFORM == PLATFORM_ANDROID
        _GLContext = new GLContextAndroid();
#elif  PLATFORM == PLATFORM_LINUX
//            _GLContext = new GLContextLinux();
#endif
        _GLContext->CreateGLContext();
		//OpenGL::InitialExtensions();
    }

    void GRIGLDrive::Exit()
    {
        _GLContext->DestroyGLContext();
    }

	//GRIRenderPipe===========================================================================================================================
	void GRIGLDrive::GRIBeginViewport()
	{
		//Swith glcontext
		_GLContext->MakeCurrContext();
	}
	void GRIGLDrive::GRIEndViewport()
	{
		_GLContext->SwapBuffer();
	}
	//GRIRenderPipe===========================================================================================================================

	//GRISet==================================================================================================================================
	void GRIGLDrive::GRISetBuffer(int bufferIndex, GRIBuffer* buffer, int offset)
	{
		GLBuffer* bufferGL = dynamic_cast<GLBuffer*>(buffer);

		if (_PendingState._OGLShaderPipeline == nullptr)
		{
			SN_ERR("Set GRIPipelineShader first, and then set GRISetBuffer.");
			return;
		}
		if (_PendingState._OGLShaderPipeline->_OGLVertexDescriptor == nullptr)
		{
			SN_ERR("You need to set the GRIVertexDescriptor first, and then you need to set the GRISetBuffer.");
			return;
		}

		GLVertexBuffers& vbos = _PendingState._OGLShaderPipeline->_OGLVertexDescriptor->_GLVertexBuffers;
		if (vbos.find(bufferIndex) != vbos.end())
		{
			GLVertexBufferObject& vboMeta = vbos[bufferIndex];
			vboMeta._GpuHandle = bufferGL->_GpuHandle;
			vboMeta._Stride = bufferGL->GetStride();
			vboMeta._BufferType = bufferGL->_BufferType;
			vboMeta._Offset = offset;
			if (vboMeta._GLVertexElements.size() == 1)
			{
				vboMeta._GLVertexElements[0]._Offset = offset;
			}
		}
		else
		{
			GLVertexBufferObject vboMeta;
			vboMeta._GpuHandle = bufferGL->_GpuHandle;
			vboMeta._Stride = bufferGL->GetStride();
			vboMeta._BufferType = bufferGL->_BufferType;
			vboMeta._Offset = offset;
			vbos[bufferIndex] = vboMeta;
			if (vboMeta._GLVertexElements.size() == 1)
			{
				vboMeta._GLVertexElements[0]._Offset = offset;
			}
		}
	}

	void  GRIGLDrive::GRISetPipelineShader(GRIPipelineShader* pipelineShaderState)
	{
        _PendingState._OGLShaderPipeline = dynamic_cast<GLPipelineShader*>(pipelineShaderState);
	}
	void GRIGLDrive::GRISetShaderParameter(GRIPipelineShader* graphicsShader, GRIUniformBuffer* buffer, int32_t bufferIndex)
	{
		GLPipelineShader* shaderPipe = dynamic_cast<GLPipelineShader*>(graphicsShader);
		GRIGLUniformBuffer* uniformBuffer = dynamic_cast<GRIGLUniformBuffer*>(buffer);
		if (_PendingState._OGLShaderPipeline == nullptr)
		{
			_PendingState._OGLShaderPipeline = shaderPipe;
		}
		if (shaderPipe->_OGLUBDescriptor == nullptr)
		{
			SN_ERR("Need to set the GRIUniformBufferDescriptor first and then the call GRISetShaderParameter.");
			return;
		}
		GLUniformBufferDesList& ubDesc = _PendingState._OGLShaderPipeline->_OGLUBDescriptor->_GLUniformBuffersDes;
		if (ubDesc.find(bufferIndex) != ubDesc.end())
		{
			ubDesc[bufferIndex]._UBType = uniformBuffer->_UniformBufferUsagType;
			ubDesc[bufferIndex]._UBHashKey = uniformBuffer->_HashKey;
			ubDesc[bufferIndex]._UinformBuffer = uniformBuffer;
		}
		else {
			GLUniformBufferSlotDesc ubDescriptor;
			ubDescriptor._UBType = uniformBuffer->_UniformBufferUsagType;
			ubDescriptor._UBHashKey	= uniformBuffer->_HashKey;
			ubDescriptor._UinformBuffer = uniformBuffer;
			ubDesc[bufferIndex]	= ubDescriptor;
		}
		//将UBO绑定到对应的绑定点上
		if (uniformBuffer->_UniformBufferUsagType != UniformBufferUsageType::UBT_UV_SingleDraw && OpenGL::SupportUniformBuffer())
		{
			UniformBuffers& internalUBs = shaderPipe->_InternalUBs; 
			if (internalUBs.find(uniformBuffer->_HashKey) == internalUBs.end())
			{
				//当前Program没有对应的UBO名字，不进行绑定
				SN_WARN("CurrDraw Program Not Has UniformBlock.");
				return;
			}
			GLuint binding = internalUBs[uniformBuffer->_HashKey]._BindingIndex;
			if (binding == -1)
			{
				binding = uniformBuffer->_BindingIndex;
				GLuint blockIndex = internalUBs[uniformBuffer->_HashKey]._BlockIndex;
				glUniformBlockBinding(shaderPipe->_ProgramId, blockIndex, binding);
				internalUBs[uniformBuffer->_HashKey]._BindingIndex = binding;
				internalUBs[uniformBuffer->_HashKey]._UBGpuHandle = uniformBuffer->_GpuHandle;
			}
		}
	}
	//Set UniformBuffer Descriptor
	void GRIGLDrive::GRISetUniformBufferDescriptor(GRIUniformBufferDescriptor* descriptor)
	{
		if (_PendingState._OGLShaderPipeline == nullptr)
		{
			SN_ERR("You need to set up GRIPipelineShader first.");
			return;
		}
		_PendingState._OGLShaderPipeline->_OGLUBDescriptor = dynamic_cast<GRIGLUniformBufferDescriptor*>(descriptor);
	}
	void GRIGLDrive::GRISetGraphicsPipeline(GRIGraphicsPipeline* pipelineState)
	{
		GLGraphicPipeline* gPipeline = dynamic_cast<GLGraphicPipeline*>(pipelineState);
		if (gPipeline->_PrimitiveType != PrimitiveType::PT_Num)
		{
			_PendingState._PrimitiveType = gPipeline->_PrimitiveType;
		}
		else
		{
			SN_ERR("Need Set PrimitiveType.");
		}
		if (gPipeline->_OGLShaderPipeline == nullptr)
		{
			SN_ERR("GRIPipelineShader Not Attach GRIGraphicsPipeline,Need Attach Or Set GRIPipelineShader.");
			return;
		}
		_PendingState._OGLShaderPipeline = gPipeline->_OGLShaderPipeline;
		if (_PendingState._OGLShaderPipeline->_OGLVertexDescriptor == nullptr)
		{
			_PendingState._OGLShaderPipeline->_OGLVertexDescriptor = gPipeline->_OGLShaderPipeline->_OGLVertexDescriptor;
		}
		else
		{
			SN_ERR("GRIVertexDescriptor Not Attach GRIPipelineShader,Need Attach Or Set GRIVertexDescriptor.");
		}
		if (_PendingState._OGLShaderPipeline->_OGLUBDescriptor)
		{
			_PendingState._OGLShaderPipeline->_OGLUBDescriptor = gPipeline->_OGLShaderPipeline->_OGLUBDescriptor;
		}
		else
		{
			SN_ERR("GRIUniformBufferDescriptor Not Attach GRIPipelineShader,Need Attach Or Call GRISetUniformBufferDescriptor.");
		}
	}

	void GRIGLDrive::GRIDrawPrimitive(int numPrimitive, int numInstance)
	{
		GLenum drawMode = GL_TRIANGLES;
		int numElements;
		CheckPrimitiveType(_PendingState._PrimitiveType, numPrimitive, drawMode, numElements);

		SetupVertexFormatBinding(_PendingState, _PendingState._OGLShaderPipeline->_OGLVertexDescriptor, Max_Num_Vertex_Attribute, numElements);
		CommitUniformBuffer();
		if (numInstance > 1)
		{

		}
		else
		{
			glUseProgram(_PendingState._OGLShaderPipeline->_ProgramId);
			glDrawArrays(drawMode, 0, numElements);
		}
	}
	//GRISet==================================================================================================================================

	//GRIprivate==============================================================================================================================
	void GRIGLDrive::SetupVertexFormatBinding(GLGraphicPipeline& psoState, GRIGLVertexDescriptor* vertexDec, int bufferIndex, int vertexCount)
	{
//		if (OpenGL::SupportVertexFormatBinding())
//		{
//
//		}
        GLVertexBuffers vertexBuffers = vertexDec->_GLVertexBuffers;
        for(auto entry : vertexBuffers)
        {
            GLVertexBufferObject vbo = entry.second;
            glBindBuffer(vbo._BufferType,vbo._GpuHandle);
            GLVertexElements ves = vbo._GLVertexElements;
            for(auto iter = ves.begin(); iter != ves.end(); iter ++)
            {
                GLVertexElement vMeta = iter->second;
                glEnableVertexAttribArray(vMeta._AttritubeIndex);
                glVertexAttribPointer(vMeta._AttritubeIndex, vMeta._Stride,vMeta._Type, vMeta._bNormalized,vMeta._Stride * sizeof(vMeta._Type),(GLvoid*)vMeta._Offset);
            }
        }
	}
	void GRIGLDrive::CheckPrimitiveType(PrimitiveType primitiveType, int numPrimitives, GLenum& glPrimitiveType, int& numElements)
	{
		glPrimitiveType = GL_TRIANGLES;
		numElements = numPrimitives;
		switch (primitiveType)
		{
		case PrimitiveType::PT_Lines:
			glPrimitiveType = GL_LINES;
			numElements = numPrimitives * 2;
			break;
		case PrimitiveType::PT_Point_Strip:
			glPrimitiveType = GL_POINTS;
			numElements = numPrimitives;
			break;
		case PrimitiveType::PT_Trangles:
			glPrimitiveType = GL_TRIANGLES;
			numElements = numPrimitives * 3;
			break;
		case PrimitiveType::PT_Trangle_Strip:
			glPrimitiveType = GL_TRIANGLE_STRIP;
			numElements = numPrimitives + 2;
			break;
		default:
			SN_LOG("There is no primitive matching type:%d", primitiveType);
			break;
		}
	}
	//GRIprivate==============================================================================================================================
}
