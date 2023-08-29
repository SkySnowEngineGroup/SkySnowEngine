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
#include "HashUtil.h"
namespace SkySnow
{
	using namespace OGLShader;
	////Create Shader about Resource
	void GRIGLDrive::GRICreateVertexShader(ResourceData& rData, GRIVertexShaderRef& handle)
	{
		OGLShader::CreateShader<GRIVertexShader, GLVertexShader>((char*)rData.GetResourceData(), handle);
        rData.Release();
	}

	void GRIGLDrive::GRICreateFragmentShader(ResourceData& rData, GRIFragmentShaderRef& handle)
	{
		OGLShader::CreateShader<GRIFragmentShader, GLFragmentShader>((char*)rData.GetResourceData(), handle);
        rData.Release();
	}

	void GRIGLDrive::GRICreatePipelineShader(GRIPipelineShaderRef& handle)
	{
		GLPipelineShader* shaderPipe = dynamic_cast<GLPipelineShader*>(handle.GetReference());
		GLVertexShader* glvs = dynamic_cast<GLVertexShader*>(shaderPipe->GetVertexShader());
		GLFragmentShader* glfs = dynamic_cast<GLFragmentShader*>(shaderPipe->GetFragmentShader());
		OGLShader::CreateProgram(shaderPipe,glvs->_GpuHandle,glfs->_GpuHandle, shaderPipe->_ProgramId);
	}

	//Shader Intern Function
	//===============================================================================================
    //Create Shader
	template<typename GRIShaderType,typename OGLShaderType>
	void OGLShader::CreateShader(const char* shadercode, GRIShaderType* handle)
	{
		OGLShaderType* shaderObject = dynamic_cast<OGLShaderType*>(handle);
		CompileShader<OGLShaderType>(shadercode, shaderObject);
	}
    //Compile Shader
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
    //Compile Shader
	bool OGLShader::CompileCurrentShader(const GLuint shaderHandle, const char* shadercode)
	{
		if (shadercode == nullptr)
		{
			SN_ERR("ShaderCode is nullptr.");
			return false;
		}
//		SN_LOG("OGL Shader Code:%s", shadercode);
		int codeLength = (int)strlen(shadercode);
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
    // Create Program and Link Program
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
    //Collect uniform var location and uniformBuffer location,binding at first runtime frame setup
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
                std::string uStr = uniformName;
                location = glGetUniformLocation(program, uniformName);
                bool isUVar = uStr.find("_Sampler") == std::string::npos;
                //收集Uniform变量分类收集，包含: UniformVar、UniformSampler、UniformSSBO ext
                if(location != -1 && isUVar)//单纯收集Uniform Var
                {
                    GLUniformSlot uSlot;
                    uSlot._Type     = type;
                    uSlot._Location = location;
                    uSlot._Size     = size;
                    block._UniformSlots[String2Hash(uniformName)] = uSlot;
//                    SN_LOG("Var UniformName:%s type:%d location:%d size:%d",uniformName,uSlot._Type,uSlot._Location,uSlot._Size);
                }
                else if(location != -1 && !isUVar)//收集Sampler并设置绑定点
                {
                    CollectSamplerAndBinding(uniformName,type,location,size,pipelineShader);
//                    SN_LOG("Sampler UniformName:%s type:%d location:%d size:%d",uniformName,type,location,size);
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
                GLuint blockIndex = -1;
                GLint  offset;
                //Get Block Name
                glGetActiveUniformBlockName(program, i, maxLength, NULL, uniformBlockName);
                //Get Block Binding Index
                glGetActiveUniformBlockiv(program, i, GL_UNIFORM_BLOCK_INDEX, (GLint*)&bindingIndex);
                //Get Block Offset
                glGetActiveUniformBlockiv(program, i, GL_UNIFORM_BLOCK_DATA_SIZE, &offset);
                //Get Block Name
                blockIndex = glGetUniformBlockIndex(program, uniformBlockName);
                if(blockIndex != -1)
                {
                    GLUniformBufferSlot uBlock;
                    uBlock._BlockIndex = blockIndex;
                    pipelineShader->_InternalUBs[String2Hash(uniformBlockName)] = uBlock;
//                    SN_LOG("uniformBlockName HashKey:%ld", String2Hash(uniformBlockName));
//                    SN_LOG("uniformBlockName:%s Binding:%d Offset:%d BlockIndex:%d",uniformBlockName,uBlock._BindingIndex,offset,uBlock._BlockIndex);
                }
            }
            delete[] uniformBlockName;
            uniformBlockName = nullptr;
        }
        glUseProgram(0);
        return true;
    }
    //Collect the sampler object, bind the location of the sampler object to the corresponding texture unit
    //(the format of the sampler name is xx_0, this _0 is added when the material is parsed and recorded in
    //the ShaderParameter of the material), bind the location of the sampler object to texture unit 0.
    bool OGLShader::CollectSamplerAndBinding(char* uSName,GLenum type,GLuint location,GLint size,GLPipelineShader* pShader)
    {
        std::string uSStr = uSName;
        std::string unitStr = uSStr.substr(uSStr.find("_Sampler") + 8);
        int unitNum = std::stoi(unitStr);
        GLUniformSlot uSlot;
        uSlot._Location = location;
        uSlot._Type     = type;
        uSlot._Size     = size;
        glUniform1i(uSlot._Location, unitNum);
        pShader->_InternalUSamplers._UniformSlots[unitNum] = uSlot;
//        SN_LOG("Sampler Texture Unit Is:%d",unitNum);
        //TODO: Support Bindless Texture
        return true;
    }
	//===============================================================================================
}
