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
#include "GLShader.h"
#include "GRIGLDrive.h"
#include "LogAssert.h"
#include "GLShaderResource.h"
#include "GLPipelineResource.h"
#include "Hash.h"
namespace SkySnow
{
	using namespace OGLShader;
	////Create Shader about Resource
	void GRIGLDrive::GRICreateVertexShader(const char* vsCode, GRIVertexShaderRef& handle)
	{
		OGLShader::CreateShader<GRIVertexShader, GLVertexShader>(vsCode, handle);
	}

	void GRIGLDrive::GRICreateFragmentShader(const char* fsCode, GRIFragmentShaderRef& handle)
	{
		OGLShader::CreateShader<GRIFragmentShader, GLFragmentShader>(fsCode, handle);
	}

	void GRIGLDrive::GRICreatePipelineShader(GRIPipelineShaderRef& handle)
	{
		GLPipelineShader* shaderPipe = dynamic_cast<GLPipelineShader*>(handle.GetReference());
		GLVertexShader* glvs = dynamic_cast<GLVertexShader*>(shaderPipe->GetVertexShader());
		GLFragmentShader* glfs = dynamic_cast<GLFragmentShader*>(shaderPipe->GetFragmentShader());
		OGLShader::CreateProgram(shaderPipe,glvs->_GpuHandle,glfs->_GpuHandle, shaderPipe->_ProgramId);
	}

	//Shader 创建的模板类方法(公共方法)
	//===============================================================================================
	//在GLShader中声明全局函数，主要原因是为了代码清晰度
	//其实可以在cpp文件中声明函数，使用static标记，进行隐藏，使此cpp可访问，对其它cpp文件进行隐藏
	//然后针对于隐藏，加了一个明明空间OGLShader，依次来提醒后续拓展，不要将此命名空间的全局函数在其
	//它命名空间下调用

	template<typename GRIShaderType,typename OGLShaderType>
	void OGLShader::CreateShader(const char* shadercode, GRIShaderType* handle)
	{
		OGLShaderType* shaderObject = dynamic_cast<OGLShaderType*>(handle);
		CompileShader<OGLShaderType>(shadercode, shaderObject);
	}

	template<typename OGLShaderType>
	void OGLShader::CompileShader(const char* shadercode,OGLShaderType* handle)
	{
		handle->_GpuHandle = glCreateShader(handle->_GLTypeEnum);
		bool flag = CompileCurrentShader(handle->_GpuHandle,shadercode);
		if (!flag)
		{
			SN_ERR("Compile Shader fail.");
		}
	}

	bool OGLShader::CompileCurrentShader(const GLuint shaderHandle, const char* shadercode)
	{
		if (shadercode == nullptr)
		{
			SN_ERR("ShaderCode is nullptr.");
			return false;
		}
//		SN_LOG("OGL Shader Code:%s", shadercode);
		int codeLength = strlen(shadercode);
		glShaderSource(shaderHandle,1 ,(const GLchar**)&shadercode, &codeLength);
		glCompileShader(shaderHandle);
        GLint success;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[512];
            glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
            SN_ERR("Shader::Compilation_Failed:%s",infoLog);
        }
		return true;
	}

	bool OGLShader::CreateProgram(GLPipelineShader* pipelineShader,const GLuint vshandle, const GLuint fshandle, GLuint& program)
	{
		program = glCreateProgram();
		glAttachShader(program, vshandle);
		glAttachShader(program, fshandle);
		glLinkProgram(program);
        //Collect Uniform And UniformBuffer
        CollectUniformBuffer(pipelineShader,program);

		return true;
	}

    bool OGLShader::CollectUniformBuffer(GLPipelineShader* pipelineShader,GLuint program)
    {
        //Collect Uniform Var
        {
            glUseProgram(program);
            //Uniform Buffer Block;
            GLUniformBufferSlot block;
            
            GLint numUniforms = 0;
            glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numUniforms);
            
            GLint maxLength = 0;
            glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
            char* uniformName = new char[maxLength];
            for (GLint i = 0; i < numUniforms; i++)
            {
                GLenum type;
                GLuint location;
                GLint  size;
                
                glGetActiveUniform(program, i, maxLength, nullptr, &size, &type, uniformName);
                location = glGetUniformLocation(program, uniformName);
                //Filter out parameters in UniformBlock
                if(location != -1)
                {
                    GLUniformSlot uSlot;
                    uSlot._Type     = type;
                    uSlot._Location = location;
                    uSlot._Size     = size;
                    uSlot._Offset   = 0;
                    block._UniformSlots[String2Hash(uniformName)] = uSlot;
                    //SN_LOG("uniformName:%s type:%d location:%d size:%d",uniformName,uSlot._Type,uSlot._Location,uSlot._Size);
                }
            }
            //0 is SingleDraw
            pipelineShader->_InternalUBs[0] = block;
            delete[] uniformName;
            uniformName = nullptr;
        }
        //If Support UniformBuffer Collect UniformBlock
        if(OpenGLBase::SupportUniformBuffer())
        {
            GLint numUniformBlock = 0;
            glGetProgramiv(program, GL_ACTIVE_UNIFORM_BLOCKS, &numUniformBlock);
            GLint maxLength = 0;
            glGetProgramiv(program, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &maxLength);
            GLchar* uniformBlockName = new GLchar[maxLength];
            for(int i = 0; i < numUniformBlock; i ++)
            {
                
                GLuint bindingIndex = -1;
                GLuint location = -1;
                GLint  offset;
                //Get Block Name
                glGetActiveUniformBlockName(program, i, maxLength, NULL, uniformBlockName);
                //Get Block Binding Index
                glGetActiveUniformBlockiv(program, i, GL_UNIFORM_BLOCK_INDEX, (GLint*)&bindingIndex);
                //Get Block Offset
                glGetActiveUniformBlockiv(program, i, GL_UNIFORM_BLOCK_DATA_SIZE, &offset);
                //Get Block Name
                location = glGetUniformBlockIndex(program, uniformBlockName);
                if(location != -1)
                {
                    GLUniformBufferSlot uBlock;
                    if(bindingIndex == -1)
                    {
                        glUniformBlockBinding(program,location,i);
                        uBlock._BindingIndex = i;
                    }
                    uBlock._Location = location;
                    uBlock._Offset = offset;
                    ////Get UniformBlock UniformSlot
                    //GLint u_numSlots = 0;
                    //glGetActiveUniformBlockiv(program, location,GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, (GLint*)&u_numSlots);
                    //GLint* u_uniformLocations = new GLint[u_numSlots];
                    //glGetActiveUniformBlockiv(program, location,GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, u_uniformLocations);
                    //GLint u_maxLength = 0;
                    //glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &u_maxLength);
                    //GLchar* u_uniformName = new GLchar[u_maxLength];
                    //for (int i = 0; i < u_numSlots; i ++)
                    //{
                    //    GLUniformSlot u_slot;
                    //    GLint u_location = u_uniformLocations[i];
                    //    GLsizei um_size = 0;
                    //    GLint   u_offset;
                    //    GLenum  u_type;
                    //    glGetActiveUniformName(program,u_location, u_maxLength,&um_size,u_uniformName);
                    //    glGetActiveUniformsiv(program,1,(GLuint*)&u_location,GL_UNIFORM_SIZE,&um_size);
                    //    glGetActiveUniformsiv(program,1,(GLuint*)&u_location,GL_UNIFORM_OFFSET,&u_offset);
                    //    glGetActiveUniformsiv(program,1,(GLuint*)&u_location,GL_UNIFORM_TYPE,(GLint*)&u_type);
                    //    u_slot._Location = u_location;
                    //    u_slot._Type     = u_type;
                    //    u_slot._Size     = um_size;
                    //    u_slot._Offset   = u_offset;
                    //    uBlock._UniformSlots[String2Hash(u_uniformName)] = u_slot;
                    //    //SN_LOG("uniformBlockName:%s uniformName:%s type:%d location:%d size:%ld Offset:%d", uniformBlockName,u_uniformName, u_type, u_location, um_size, u_offset);
                    //    //if (GL_FLOAT_VEC4 == u_type)
                    //    //{
                    //    //    SN_LOG("Is GL_FLOAT_VEC4");
                    //    //}
                    //}
                    //delete[] u_uniformName;
                    //u_uniformName = nullptr;
                    pipelineShader->_InternalUBs[String2Hash(uniformBlockName)] = uBlock;
                    SN_LOG("uniformBlockName HashKey:%ld", String2Hash(uniformBlockName));
                    //SN_LOG("uniformBlockName:%s Binding:%d Offset:%d Location:%d",uniformBlockName,uBlock._BindingIndex,uBlock._Offset,uBlock._Location);
                }
            }
            delete[] uniformBlockName;
            uniformBlockName = nullptr;
        }
        glUseProgram(0);
        return true;
    }
	//===============================================================================================
}
