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
#include "GLRealTimeGRI.h"
#include "LogAssert.h"
#include "GLShaderResource.h"
#include "GLPipelineResource.h"
namespace SkySnow
{
	using namespace OGLShader;
	////Create Shader about Resource
	GRIVertexShaderRef GLRealTimeGRI::GRICreateVertexShader(const char* vsCode)
	{
		return OGLShader::CreateShader<GRIVertexShader, GLVertexShader>(vsCode);
	}

	GRIFragmentShaderRef GLRealTimeGRI::GRTCreateFragmentShader(const char* fsCode)
	{
		return OGLShader::CreateShader<GRIFragmentShader, GLFragmentShader>(fsCode);
	}

	GRIPipelineShaderStateRef GLRealTimeGRI::GRICreatePipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs)
	{
		return GRIPipelineShaderStateRef(new GLPipelineShaderState(vs, fs));
	}

	//Shader ������ģ���෽��(��������)
	//===============================================================================================
	//��GLShader������ȫ�ֺ�������Ҫԭ����Ϊ�˴���������
	//��ʵ������cpp�ļ�������������ʹ��static��ǣ��������أ�ʹ��cpp�ɷ��ʣ�������cpp�ļ���������
	//Ȼ����������أ�����һ�������ռ�OGLShader�����������Ѻ�����չ����Ҫ���������ռ��ȫ�ֺ�������
	//�������ռ��µ���

	template<typename GRIShaderType,typename OGLShaderType>
	GRIShaderType* OGLShader::CreateShader(const char* shadercode)
	{
		GRIShaderType* shaderObject = CompileShader<OGLShaderType>(shadercode);
		return shaderObject;
	}

	template<typename OGLShaderType>
	OGLShaderType* OGLShader::CompileShader(const char* shadercode)
	{
		OGLShaderType* shader = new OGLShaderType();
		shader->m_GpuHandle = OpenGL::CreateShader(shader->m_GLTypeEnum);
		CompileCurrentShader(shader->m_GpuHandle,shadercode);
		return shader;
	}

	bool OGLShader::CompileCurrentShader(const GLuint shaderHandle, const char* shadercode)
	{

		SN_LOG("OGL Shader Code:%s", shadercode);
		int codeLength = strlen(shadercode);
		glShaderSource(shaderHandle,1 ,(const GLchar**)&shadercode, &codeLength);
		glCompileShader(shaderHandle);
		return true;
	}
	//===============================================================================================
}