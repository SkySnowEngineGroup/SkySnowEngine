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
		OGLShader::CreateProgram(glvs->_GpuHandle,glfs->_GpuHandle, shaderPipe->_ProgramId);
	}

	//Shader ������ģ���෽��(��������)
	//===============================================================================================
	//��GLShader������ȫ�ֺ�������Ҫԭ����Ϊ�˴���������
	//��ʵ������cpp�ļ�������������ʹ��static��ǣ��������أ�ʹ��cpp�ɷ��ʣ�������cpp�ļ���������
	//Ȼ����������أ�����һ�������ռ�OGLShader�����������Ѻ�����չ����Ҫ���������ռ��ȫ�ֺ�������
	//�������ռ��µ���

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
		//SN_LOG("OGL Shader Code:%s", shadercode);
		int codeLength = strlen(shadercode);
		glShaderSource(shaderHandle,1 ,(const GLchar**)&shadercode, &codeLength);
		glCompileShader(shaderHandle);
		return true;
	}

	bool OGLShader::CreateProgram(const GLuint vshandle, const GLuint fshandle, GLuint& program)
	{
		program = glCreateProgram();
		glAttachShader(program, vshandle);
		glAttachShader(program, fshandle);
		glLinkProgram(program);
		return true;
	}
	//===============================================================================================
}
