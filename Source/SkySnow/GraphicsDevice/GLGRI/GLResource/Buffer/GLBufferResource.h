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
#include "GLBuffer.h"
#include <unordered_map>
namespace SkySnow
{
    struct GLVertexElement;
    struct GLVertexBufferObject;
    typedef std::unordered_map<int,GLVertexElement>         GLVertexElements;
    typedef std::unordered_map<int,GLVertexBufferObject>    GLVertexBuffers;

	class GLBuffer : public GRIBuffer
	{
		friend class GRIGLDrive;
	public:
		GLBuffer()
			: GRIBuffer()
			, _BufferType(0)
			, _GpuHandle(0)
			, _StreamDraw(false)
			, _Data(nullptr)
		{
		}
		//
        GLBuffer(BufferUsageType usageType,GLuint size,int stride,const void* data,bool streamDraw = false)
			: GRIBuffer(usageType, size, stride) 
			, _Data(data)
			, _StreamDraw(streamDraw)
		{
		}

		~GLBuffer()
		{
		}
        //Create Buffer with buffer type
		void CreateBuffer(GLenum bufferType,GLenum usageType,GLuint size)
		{
			_BufferType = bufferType;
			glGenBuffers(1,&_GpuHandle);
			glBindBuffer(_BufferType, _GpuHandle);
			glBufferData(_BufferType, size, _Data, IsDynamic() ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
			glBindBuffer(_BufferType, 0);
		}

	public:
		GLuint		_GpuHandle;
		GLenum		_BufferType;
	private:
		bool		_StreamDraw;
		const void* _Data;
	};
    //Vertex Declaration layout
    //vdlStart==============================================================================================
    struct GLVertexElement
    {
        GLVertexElement()
        {
        }
        //vertex element type:GL_FLOAT or GL_SHORT
        GLenum  _Type;
        GLuint  _Offset;
        GLuint  _Stride;
        uint8_t _AttritubeIndex;
        uint8_t _bNormalized;
        uint8_t _bConvertToFloat;
    };
    struct GLVertexBufferObject
    {
        GLenum              _BufferType;
        GLuint              _GpuHandle;
        GLuint              _Stride;
        GLuint              _Offset;
        GLVertexElements    _GLVertexElements;
    };
    struct GRIGLVertexDeclaration : public GRIVertexDeclaration
    {
    public:
        GRIGLVertexDeclaration()
            : GRIVertexDeclaration()
        {
        }
        void SetUp(const VertexDeclarationElementList& vdel)
        {
            int bufferIndex = -1;
            for(int32_t index = 0; index < vdel.size(); index ++)
            {
                GRIVertexElement element = vdel[index];
                if(bufferIndex != element._BufferIndex)
                {
                    GLVertexBufferObject vbo;
                    GLBuffer* bufferGL = dynamic_cast<GLBuffer*>(element._GRIBuffer);
                    vbo._GpuHandle = bufferGL? bufferGL->_GpuHandle : -1;
                    vbo._BufferType = bufferGL ? bufferGL->_BufferType : -1;
                    vbo._Stride = element._Strid;
                    vbo._Offset = element._Offset;
                    _GLVertexBuffers[element._BufferIndex] = vbo;
                    bufferIndex = element._BufferIndex;
                }
                GLVertexElements& vertexElements = _GLVertexBuffers[element._BufferIndex]._GLVertexElements;
                GLVertexElement glElement;
                glElement._AttritubeIndex = element._AtttitubeIndex;
                glElement._Offset = element._Offset;
                switch(element._VET_Type)
                {
                    case VertexElementType::VET_Float1:
                        glElement._Type = GL_FLOAT;
                        glElement._Stride = 1;
                        glElement._bNormalized = false;
                        glElement._bConvertToFloat = true;
                        break;
                    case VertexElementType::VET_Float2:
                        glElement._Type = GL_FLOAT;
                        glElement._Stride = 2;
                        glElement._bNormalized = false;
                        glElement._bConvertToFloat = true;
                        break;
                    case VertexElementType::VET_Float3:
                        glElement._Type = GL_FLOAT;
                        glElement._Stride = 3;
                        glElement._bNormalized = false;
                        glElement._bConvertToFloat = true;
                        break;
                    case VertexElementType::VET_Float4:
                        glElement._Type = GL_FLOAT;
                        glElement._Stride = 4;
                        glElement._bNormalized = false;
                        glElement._bConvertToFloat = true;
                        break;
                    default:
                        SN_ERR("Unknown GRI vertex element type %u",element._VET_Type);
                        break;
                }
                vertexElements[element._AtttitubeIndex] = glElement;
            }
        }
    public:
        GLVertexBuffers    _GLVertexBuffers;
    };
    //vdlEnd================================================================================================

    //UniformBuffer
    class GRIGLUniformBuffer : public GRIUniformBuffer
    {
    public:
        GRIGLUniformBuffer()
        {
        }
        
        ~GRIGLUniformBuffer()
        {
        }
    public:
        GLuint          _GpuHandle;
        GLuint          _BindingIndex;
    };
}
