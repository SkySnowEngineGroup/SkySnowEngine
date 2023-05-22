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
#include "GRIResourceCreateInfo.h"
#include <unordered_map>
namespace SkySnow
{
	class GRIGLBuffer : public GRIBuffer
	{
		friend class GRIGLDrive;
	public:
        GRIGLBuffer()
			: GRIBuffer()
			, _BufferType(0)
			, _GpuHandle(0)
			, _StreamDraw(false)
			, _Data(nullptr)
		{
		}
		//
        GRIGLBuffer(BufferUsageType usageType,GLuint size,int stride,const void* data,bool streamDraw = false)
			: GRIBuffer(usageType, size, stride) 
			, _Data(data)
			, _StreamDraw(streamDraw)
            , _GpuHandle(-1)
		{
		}

		~GRIGLBuffer()
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
    struct GRIGLVertexDescriptor : public GRIVertexDescriptor
    {
    public:
        GRIGLVertexDescriptor()
            : GRIVertexDescriptor()
        {
        }
        void SetUp(const VertexElementList& vdel)
        {
            int bufferIndex = -1;
            for(int32_t index = 0; index < vdel.size(); index ++)
            {
                VertexElementSlot element = vdel[index];
                if(bufferIndex != element._BufferIndex)
                {
                    GLVertexBufferSlot vbo;
                    GRIGLBuffer* bufferGL = dynamic_cast<GRIGLBuffer*>(element._GRIBuffer);
                    vbo._GpuHandle = bufferGL? bufferGL->_GpuHandle : -1;
                    vbo._BufferType = bufferGL ? bufferGL->_BufferType : -1;
                    vbo._Stride = element._Strid;
                    vbo._Offset = element._Offset;
                    _GLVertexBuffers[element._BufferIndex] = vbo;
                    bufferIndex = element._BufferIndex;
                }
                GLVertexElements& vertexElements = _GLVertexBuffers[element._BufferIndex]._GLVertexElements;
                GLVertexElement glElement;
                glElement._AttributeIndex = element._AttributeIndex;
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
                vertexElements[element._AttributeIndex] = glElement;
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
            : GRIUniformBuffer()
            , _GpuHandle(-1)
            , _BindingIndex(-1)
            , _UniformBufferUsagType(UniformBufferUsageType::UBT_None)
            , _Size(0)
            , _HashKey(0)
            , _Dirty(false)
        {
        }
        
        ~GRIGLUniformBuffer()
        {
            SN_LOG("GRIGLUniformBuffer Destruct");
            ClearUniformData();
        }

        void SetUp(const UniformSlotList& contents,const char* ubName,UniformBufferUsageType ubType)
        {
            _UniformBufferUsagType = ubType;
            _HashKey = String2Hash(ubName);
            for (int i = 0; i < contents.size(); i ++)
            {
                _Size += contents[i]._Size;
            }
            RecordUniformData(contents);
            if (_UniformBufferUsagType != UniformBufferUsageType::UBT_UV_SingleDraw)
            {
                bool stream = (_UniformBufferUsagType == UniformBufferUsageType::UBT_SingleDraw || _UniformBufferUsagType == UniformBufferUsageType::UBT_SingleFrame);
                glGenBuffers(1,&_GpuHandle);
                glBindBuffer(GL_UNIFORM_BUFFER, _GpuHandle);
                //TODO Map Buffer Object
                char* combindData = new char[_Size];
                uint8_t offset = 0;
                for (int i = 0; i < contents.size(); i ++)
                {
                    std::memcpy(static_cast<char*>(combindData + offset), contents[i]._Data, contents[i]._Size);
                    offset = offset + contents[i]._Size;
                }
                glBufferData(GL_UNIFORM_BUFFER, _Size, (void*)(combindData), stream ? GL_STREAM_DRAW : GL_STATIC_DRAW);
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
                _BindingIndex = OGLBuffer::UBCounter::ICInstance().GetCount();
                OGLBuffer::UBCounter::ICInstance().AddCount();
                delete[] combindData;
                combindData = nullptr;
            }
            _Dirty = true;
        }

        void UpdateUniformBuffer(const UniformSlotList& contents)
        {
            RecordUniformData(contents);
            if (_UniformBufferUsagType != UniformBufferUsageType::UBT_UV_SingleDraw)
            {
                char* combindData = new char[_Size];
                uint8_t offset = 0;
                for (int i = 0; i < contents.size(); i++)
                {
                    std::memcpy(static_cast<char*>(combindData + offset), contents[i]._Data, contents[i]._Size);
                    offset = offset + contents[i]._Size;
                }
                glBindBuffer(GL_UNIFORM_BUFFER, _GpuHandle);
                //TODO Map Buffer Object
                glBufferSubData(GL_UNIFORM_BUFFER, 0, _Size, (void*)combindData);
                delete[] combindData;
                combindData = nullptr;
            }
            _Dirty = true;
        }
    private:
        void RecordUniformData(const UniformSlotList& contents)
        {
            ClearUniformData();
            if (_UniformBufferUsagType == UniformBufferUsageType::UBT_UV_SingleDraw)
            {
                _HashKey = 0;
                for (int i = 0; i < contents.size(); i ++)
                {
                    _UniformBufferData.push_back(std::make_pair(contents[i]._Hash, contents[i]._Data));
                }
            }
        }
        void ClearUniformData()
        {
            _UniformBufferData.clear();
        }
    public:
        bool                                _Dirty;
        int                                 _Size;
        GLuint                              _GpuHandle;
        GLuint                              _BindingIndex;
        size_t                              _HashKey;
        UniformBufferUsageType              _UniformBufferUsagType;
        std::vector<std::pair<size_t,void*>>   _UniformBufferData;
    };

    //UniformBuffer Descriptor
    typedef std::unordered_map<int, GLUniformBufferSlotDesc> GLUniformBufferDesList;
    class GRIGLUniformBufferDescriptor : public GRIUniformBufferDescriptor
    {
        
    public:
        GRIGLUniformBufferDescriptor()
            : GRIUniformBufferDescriptor()
        {
        }
        
        ~GRIGLUniformBufferDescriptor()
        {
            SN_LOG("GRIGLUniformBufferDescriptor Destruct");
        }

        void SetUp(const UniformBufferList& list)
        {
            for (int i = 0; i < list.size(); i ++)
            {
                UniformBufferSlot ubSlot = list[i];
                GLUniformBufferSlotDesc ubSlotDesc;

                ubSlotDesc._UBType        = ubSlot._UBType;
                ubSlotDesc._UBHashKey     = ubSlot._UBHashKey;
                ubSlotDesc._UinformBuffer = dynamic_cast<GRIGLUniformBuffer*>(ubSlot._UniformBuffer);
                _GLUniformBuffersDes[ubSlot._UBIndex] = ubSlotDesc;
            }
        }
    public:
        GLUniformBufferDesList _GLUniformBuffersDes;
    };
}
