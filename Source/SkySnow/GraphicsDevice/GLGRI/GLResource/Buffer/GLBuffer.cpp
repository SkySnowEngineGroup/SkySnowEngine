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
#include "GLBuffer.h"
#include "GRIGLDrive.h"
#include "GLBufferResource.h"
namespace SkySnow
{
    //Create Buffer,Buffer Type: indexbuffer\vertexbuffer\SSBO
	void GRIGLDrive::GRICreateBuffer(BufferUsageType usageType, int size,int stride, void* data, GRIBufferRef& handle)
	{
		GLenum bufferType = GL_ARRAY_BUFFER;
		if (usageType == BUT_IndexBuffer)
		{
			bufferType = GL_ELEMENT_ARRAY_BUFFER;//IBO
		}

        GRIGLBuffer* glBuffer = dynamic_cast<GRIGLBuffer*>(handle.GetReference());
		glBuffer->CreateBuffer(bufferType,usageType, size);
		glBuffer->_StreamDraw = true;
		glBuffer->_BufferName = "a";
	}
    //Create Vertex Buffer Declaration
    void GRIGLDrive::GRICreateVertexDescriptor(const VertexElementList& vdel,GRIVertexDescriptorRef& handle)
    {
        GRIGLVertexDescriptor* vertexDecl = dynamic_cast<GRIGLVertexDescriptor*>(handle.GetReference());
        vertexDecl->SetUp(vdel);
    }
	//Create Uniform Buffer
    void GRIGLDrive::GRICreateUniformBuffer(const UniformSlotList& contents,const char* ubName,UniformBufferUsageType ubType,GRIUniformBufferRef& handle)
	{
		GRIGLUniformBuffer* uniformBuffer = dynamic_cast<GRIGLUniformBuffer*>(handle.GetReference());
		uniformBuffer->SetUp(contents,ubName,ubType);
	}
	//Update Uniform Buffer
	void GRIGLDrive::GRIUpdateUniformBuffer(GRIUniformBufferRef& buffer, const UniformSlotList& contents)
	{
		GRIGLUniformBuffer* uniformBuffer = dynamic_cast<GRIGLUniformBuffer*>(buffer.GetReference());
		uniformBuffer->UpdateUniformBuffer(contents);
	}
	//Create Uniform Buffer Declaration
	void GRIGLDrive::GRICreateUniformDescriptor(const UniformBufferList& ubl, GRIUniformBufferDescriptorRef& handle)
	{
		GRIGLUniformBufferDescriptor* glHandle = dynamic_cast<GRIGLUniformBufferDescriptor*>(handle.GetReference());
		glHandle->SetUp(ubl);
	}
    void GRIGLDrive::BindUniformBuffer(GLGraphicPipeline& contextState)
    {
        GLPipelineShader* shaderPipe = contextState.GetPipelineShader();
        GRIGLUniformBufferDescriptor* ubDesc = contextState.GetUniformBufferDescriptor();
        if(ubDesc == nullptr)
        {
            //SN_ERR("Not set GRIUniformBufferDescriptor descriptor for UniformBuffer related processing.");
            return;
        }
        //UniformBuffer State
        GLUniformBufferDesList& ubList = ubDesc->_GLUniformBuffersDes;
        for(auto iter = ubList.begin(); iter != ubList.end(); iter ++)
        {
            GRIGLUniformBuffer*  uniformBuffer = iter->second.GetUniformBuffer();
            UniformBuffers& internalUBs = shaderPipe->_InternalUBs;
            bool find_ub = internalUBs.find(uniformBuffer->_HashKey) != internalUBs.end();
            //Program Bind Binding
            if (uniformBuffer->_UniformBufferUsagType != UniformBufferUsageType::UBT_UV_SingleDraw && OpenGL::SupportUniformBuffer() && find_ub)
            {
                GLuint binding = internalUBs[uniformBuffer->_HashKey]._BindingIndex;
                if (binding == -1)
                {
                    binding = uniformBuffer->_BindingIndex;
                    GLuint blockIndex = internalUBs[uniformBuffer->_HashKey]._BlockIndex;
                    //Bind Program BlockIndex To Binding
                    glUniformBlockBinding(shaderPipe->_ProgramId, blockIndex, binding);
                    internalUBs[uniformBuffer->_HashKey]._BindingIndex = binding;
                    internalUBs[uniformBuffer->_HashKey]._UBGpuHandle = uniformBuffer->_GpuHandle;
                }
                glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer->_GpuHandle);
                //Bind UniformBuffer To Binding
                glBindBufferBase(GL_UNIFORM_BUFFER, uniformBuffer->_BindingIndex, uniformBuffer->_GpuHandle);
            }
            //Update Uniform Array
            if(uniformBuffer->_UniformBufferUsagType == UniformBufferUsageType::UBT_UV_SingleDraw && uniformBuffer->_Dirty)
            {
                OGLBuffer::UniformVariableUpdate(uniformBuffer->_UniformBufferData,internalUBs[0]);
                uniformBuffer->_Dirty = false;
            }
        }
    }
    //Get Raw Pointer
    GRIGLUniformBuffer* GLUniformBufferSlotDesc::GetUniformBuffer()
    {
        return dynamic_cast<GRIGLUniformBuffer*>(_UniformBuffer.GetReference());
    }
	namespace OGLBuffer
	{
        void UniformVariableUpdate(const std::vector<std::pair<size_t, void*>>& newValue,GLUniformBufferSlot& internalValue)
        {
            for(auto iter = newValue.begin(); iter < newValue.end(); iter ++)
            {
                size_t hashKey = iter->first;
                void*  data = iter->second;
                std::unordered_map<size_t, GLUniformSlot> inSlots = internalValue._UniformSlots;
                bool find_flag = inSlots.find(hashKey) != inSlots.end();
                bool mat_transpose = false;
                if(find_flag)
                {
                    const GLUniformSlot uSlot = inSlots[hashKey];
                    switch(uSlot._Type)
                    {
                        case GL_FLOAT:
                            if(uSlot._Size > 1)
                            {
                                glUniform1fv(uSlot._Location, uSlot._Size,(GLfloat*)(data));
                            }else{
                                glUniform1f(uSlot._Location,*(GLfloat*)(data));
                            }
                            break;
                        case GL_INT:break;
                            if(uSlot._Size > 1)
                            {
                                glUniform1iv(uSlot._Location, uSlot._Size,(GLint*)(data));
                            }else{
                                glUniform1i(uSlot._Location,*(GLint*)(data));
                            }
                        case GL_FLOAT_VEC2:
                            if(uSlot._Size > 1)
                            {
                                glUniform2fv(uSlot._Location, uSlot._Size,(GLfloat*)(data));
                            }else{
                                float* array = (GLfloat*)(data);
                                glUniform2f(uSlot._Location,array[0],array[1]);
                            }
                            break;
                        case GL_FLOAT_VEC3:
                            if(uSlot._Size > 1)
                            {
                                glUniform3fv(uSlot._Location, uSlot._Size,(GLfloat*)(data));
                            }else{
                                float* array = (GLfloat*)(data);
                                glUniform3f(uSlot._Location,array[0],array[1],array[2]);
                            }
                            break;
                        case GL_FLOAT_VEC4:
                            if(uSlot._Size > 1)
                            {
                                glUniform4fv(uSlot._Location, uSlot._Size,(GLfloat*)(data));
                            }else{
                                float* array = (GLfloat*)(data);
                                glUniform4f(uSlot._Location,array[0],array[1],array[2],array[3]);
                            }
                            break;
                        case GL_INT_VEC2:
                            if(uSlot._Size > 1)
                            {
                                glUniform2iv(uSlot._Location, uSlot._Size,(GLint*)(data));
                            }else{
                                int* array = (GLint*)(data);
                                glUniform2i(uSlot._Location,array[0],array[1]);
                            }
                            break;
                        case GL_INT_VEC3:
                            if(uSlot._Size > 1)
                            {
                                glUniform3iv(uSlot._Location, uSlot._Size,(GLint*)(data));
                            }else{
                                int* array = (GLint*)(data);
                                glUniform3i(uSlot._Location,array[0],array[1],array[2]);
                            }
                            break;
                        case GL_INT_VEC4:
                            if(uSlot._Size > 1)
                            {
                                glUniform4iv(uSlot._Location, uSlot._Size,(GLint*)(data));
                            }else{
                                int* array = (GLint*)(data);
                                glUniform4i(uSlot._Location,array[0],array[1],array[2],array[3]);
                            }
                            break;
                        case GL_FLOAT_MAT2:
                            glUniformMatrix2fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        case GL_FLOAT_MAT2x3:
                            glUniformMatrix2x3fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        case GL_FLOAT_MAT2x4:
                            glUniformMatrix2x4fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        case GL_FLOAT_MAT3:
                            glUniformMatrix3fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        case GL_FLOAT_MAT3x2:
                            glUniformMatrix3x2fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        case GL_FLOAT_MAT3x4:
                            glUniformMatrix3x4fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        case GL_FLOAT_MAT4:
                            glUniformMatrix4fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        case GL_FLOAT_MAT4x2:
                            glUniformMatrix4x2fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        case GL_FLOAT_MAT4x3:
                            glUniformMatrix4x3fv(uSlot._Type, uSlot._Type, mat_transpose, (GLfloat*)(data));
                            break;
                        default:
                            SN_WARN("UniformSlot Type Not Support Type:%d.",uSlot._Type);
                            break;

                    }
                }
                //====Single UniformSlot End
            }
            //==== Single UniformSlot Array End
        }
	}
}
