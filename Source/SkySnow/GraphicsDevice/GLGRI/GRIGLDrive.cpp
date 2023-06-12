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
#include "GLTexture.h"
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
        OpenGL::InitialExtensions();
		OGLTexture::InitTextureFormat();
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
        GRIGLBuffer* bufferGL = dynamic_cast<GRIGLBuffer*>(buffer);
		if (_PendingState._OGLVertexDescriptor == nullptr)
		{
			SN_ERR("GRISetBuffer set GRIBuffer is nullptr.");
			return;
		}

		GLVertexBuffers& vbos = _PendingState._OGLVertexDescriptor->_GLVertexBuffers;
		if (vbos.find(bufferIndex) != vbos.end())
		{
            GLVertexBufferSlot& vboMeta = vbos[bufferIndex];
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
            GLVertexBufferSlot vboMeta;
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
    
    void GRIGLDrive::GRISetShaderTexture(GRIPipelineShader* graphicsShader, GRITexture* texture, uint32 textureIndex)
    {
        
    }
    
    void GRIGLDrive::GRISetShaderSampler(GRIPipelineShader* graphicsShader, GRISamplerState* sampler, uint32 samplerIndex)
    {
        
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
		GLUniformBufferDesList& ubDesc = _PendingState._OGLUBDescriptor->_GLUniformBuffersDes;
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
	}
	//Set UniformBuffer Descriptor
	void GRIGLDrive::GRISetUniformBufferDescriptor(GRIUniformBufferDescriptor* descriptor)
	{
        GRIGLUniformBufferDescriptor* ides = dynamic_cast<GRIGLUniformBufferDescriptor*>(descriptor);
		if (ides == nullptr)
		{
			SN_ERR("GRISetUniformBufferDescriptor set GRIUniformBufferDescriptor is nullptor.");
			return;
		}
		_PendingState._OGLUBDescriptor = ides;
	}
	void GRIGLDrive::GRISetGraphicsPipeline(GRIGraphicsPipeline* pipelineState)
	{
		GLGraphicPipeline* gPipeline = dynamic_cast<GLGraphicPipeline*>(pipelineState);
		if (gPipeline->_PrimitiveType != PrimitiveType::PT_Num)
		{
			_PendingState._PrimitiveType = gPipeline->_PrimitiveType;
		}
		if (gPipeline->_OGLShaderPipeline)
		{
            _PendingState._OGLShaderPipeline = gPipeline->_OGLShaderPipeline;
		}
		if (gPipeline->_OGLVertexDescriptor)
		{
			_PendingState._OGLVertexDescriptor = gPipeline->_OGLVertexDescriptor;
		}
		if (gPipeline->_OGLUBDescriptor)
		{
			_PendingState._OGLUBDescriptor = gPipeline->_OGLUBDescriptor;
		}
	}

	void GRIGLDrive::GRIDrawPrimitive(int numPrimitive, int numInstance)
	{
        //Bind Some About PipelineShader State
        BindPipelineShaderState(_PendingState);
		GLenum drawMode = GL_TRIANGLES;
		int numElements;
		CheckPrimitiveType(_PendingState._PrimitiveType, numPrimitive, drawMode, numElements);

		SetupVertexFormatBinding(_PendingState, _PendingState._OGLVertexDescriptor, Max_Num_Vertex_Attribute, numElements);
		
        //TODO Instance numInstance>1
        glUseProgram(_PendingState._OGLShaderPipeline->_ProgramId);
        glDrawArrays(drawMode, 0, numElements);
	}
	//GRISet==================================================================================================================================

	//GRIprivate==============================================================================================================================
    void GRIGLDrive::BindPipelineShaderState(GLGraphicPipeline& contextState)
    {
        GLPipelineShader* shaderPipe = contextState._OGLShaderPipeline;
        //PepelineShader State
        glUseProgram(shaderPipe->_ProgramId);
        
        BindUniformBuffer(contextState);
        
    }

	void GRIGLDrive::SetupVertexFormatBinding(GLGraphicPipeline& psoState, GRIGLVertexDescriptor* vertexDec, int bufferIndex, int vertexCount)
	{
//		if (OpenGL::SupportVertexFormatBinding())
//		{
//
//		}
        GLVertexBuffers vertexBuffers = vertexDec->_GLVertexBuffers;
        for(auto entry : vertexBuffers)
        {
            GLVertexBufferSlot vbo = entry.second;
            glBindBuffer(vbo._BufferType,vbo._GpuHandle);
            GLVertexElements ves = vbo._GLVertexElements;
            for(auto iter = ves.begin(); iter != ves.end(); iter ++)
            {
                GLVertexElement vMeta = iter->second;
                glEnableVertexAttribArray(vMeta._AttributeIndex);
                glVertexAttribPointer(vMeta._AttributeIndex, vMeta._Stride,vMeta._Type, vMeta._bNormalized,vMeta._Stride * sizeof(vMeta._Type),(GLvoid*)vMeta._Offset);
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
