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
        GLVertexBufferObject& vboMeta = _PendingState._OGLShaderPipeline->_OGLVertexDeclaration->_GLVertexBuffers[bufferIndex];
        vboMeta._GpuHandle = bufferGL->_GpuHandle;
        vboMeta._Stride = bufferGL->GetStride();
        vboMeta._BufferType = bufferGL->_BufferType;
        vboMeta._Offset = offset;
        if(vboMeta._GLVertexElements.size() == 1)
        {
            vboMeta._GLVertexElements[0]._Offset = offset;
        }
	}

	void  GRIGLDrive::GRISetPipelineShader(GRIPipelineShader* pipelineShaderState)
	{
        _PendingState._OGLShaderPipeline = static_cast<GLPipelineShader*>(pipelineShaderState);
	}

	void GRIGLDrive::GRISetGraphicsPipeline(GRIGraphicsPipeline* pipelineState)
	{
		_PendingState._PrimitiveType = (PrimitiveType)static_cast<GLGraphicPipeline*>(pipelineState)->_PrimitiveType;
        _PendingState._OGLShaderPipeline = static_cast<GLGraphicPipeline*>(pipelineState)->_OGLShaderPipeline;
        _PendingState._OGLShaderPipeline->_OGLVertexDeclaration = static_cast<GLGraphicPipeline*>(pipelineState)->_OGLShaderPipeline->_OGLVertexDeclaration;
	}

	void GRIGLDrive::GRIDrawPrimitive(int numPrimitive, int numInstance)
	{
		GLenum drawMode = GL_TRIANGLES;
		int numElements;
		CheckPrimitiveType(_PendingState._PrimitiveType, numPrimitive, drawMode, numElements);

		SetupVertexFormatBinding(_PendingState, _PendingState._OGLShaderPipeline->_OGLVertexDeclaration, Max_Num_Vertex_Attribute, numElements);
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
	void GRIGLDrive::SetupVertexFormatBinding(GLGraphicPipeline& psoState, GRIGLVertexDeclaration* vertexDec, int bufferIndex, int vertexCount)
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
            for(auto ve : ves)
            {
                GLVertexElement vMeta = ve.second;
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
