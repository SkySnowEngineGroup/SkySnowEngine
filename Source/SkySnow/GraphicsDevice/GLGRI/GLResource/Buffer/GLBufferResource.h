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
    struct GRIGLVertexDescriptor : public GRIVertexDescriptor
    {
    public:
        GRIGLVertexDescriptor()
            : GRIVertexDescriptor()
        {
        }
        void SetUp(const VertexDescriptorElementList& vdel)
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
            : GRIUniformBuffer()
            , _GpuHandle(-1)
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

        void SetUp(UniformBufferSlot* ubSlot)
        {
            _UniformBufferUsagType = ubSlot->GetUsageType();
            _HashKey = ubSlot->GetUniformBufferKey();
            _Size = ubSlot->GetSize();
            
            RecordUniformData(ubSlot);
            std::vector<std::pair<size_t, void*>> inData = ubSlot->GetUniformBuffers();
            if (_UniformBufferUsagType != UniformBufferUsageType::UBT_UV_SingleDraw)
            {
                bool stream = (_UniformBufferUsagType == UniformBufferUsageType::UBT_SingleDraw || _UniformBufferUsagType == UniformBufferUsageType::UBT_SingleFrame);
                glGenBuffers(1,&_GpuHandle);
                glBindBuffer(GL_UNIFORM_BUFFER, _GpuHandle);
                //TODO Map Buffer Object
                glBufferData(GL_UNIFORM_BUFFER, _Size, inData.data(), stream ? GL_STREAM_DRAW : GL_STATIC_DRAW);
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
            }
            _Dirty = true;
        }

        void UpdateUniformBuffer(UniformBufferSlot* ubSlot)
        {
            RecordUniformData(ubSlot);
            if (_UniformBufferUsagType != UniformBufferUsageType::UBT_UV_SingleDraw)
            {
                std::vector<std::pair<size_t, void*>> inData = ubSlot->GetUniformBuffers();
                glBindBuffer(GL_UNIFORM_BUFFER, _GpuHandle);
                glBufferSubData(GL_UNIFORM_BUFFER, 0, _Size, inData.data());
            }
            _Dirty = true;
        }
    private:
        void RecordUniformData(UniformBufferSlot* ubSlot)
        {
            ClearUniformData();
            std::vector<std::pair<size_t, void*>> inData = ubSlot->GetUniformBuffers();
            if (_UniformBufferUsagType == UniformBufferUsageType::UBT_UV_SingleDraw)
            {
                _HashKey = 0;
                for (auto iter = inData.begin();iter != inData.end();iter++)
                {
                    char* inData = static_cast<char*>(iter->second);
                    int lenght = strlen(inData);
                    char* newData = new char[lenght];
                    std::memcpy(newData, inData, lenght);
                    _UniformBufferData.push_back(std::make_pair(iter->first, newData));
                }
            }
        }
        void ClearUniformData()
        {
            for (auto iter = _UniformBufferData.begin();iter != _UniformBufferData.end();)
            {
                void* data = iter->second;
                delete[] data;
                data = nullptr;
                iter = _UniformBufferData.erase(iter);
            }
            _UniformBufferData.clear();
        }
    public:
        int8_t                              _Dirty;
        int                                 _Size;
        GLuint                              _GpuHandle;
        size_t                              _HashKey;
        UniformBufferUsageType              _UniformBufferUsagType;
        std::vector<std::pair<size_t, void*>>   _UniformBufferData;
    };

    //UniformBuffer Descriptor
    class GRIGLUniformBufferDescriptor : public GRIUniformBufferDescriptor
    {
        typedef std::unordered_map<int, GLUniformBufferSlotDesc> GLUniformBufferDesList;
    public:
        GRIGLUniformBufferDescriptor()
            : GRIUniformBufferDescriptor()
        {
        }
        
        ~GRIGLUniformBufferDescriptor()
        {
            SN_LOG("GRIGLUniformBufferDescriptor Destruct");
        }

        void SetUp(UniformBufferList& list)
        {
            for (auto iter = list.begin(); iter != list.end(); iter ++)
            {
                GLUniformBufferSlotDesc ubDescriptor;
                UniformBufferSlotDesc ubs = iter->second;

                ubDescriptor._UBType = ubs._UBType;
                ubDescriptor._UBHashKey = ubs._UBHashKey;

                _GLUniformBuffersDes[iter->first] = ubDescriptor;
            }
        }
    public:
        GLUniformBufferDesList _GLUniformBuffersDes;
    };
}
