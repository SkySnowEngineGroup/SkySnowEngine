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
#include "GLResource.h"
#include "LogAssert.h"
#include "GLShaderResource.h"
namespace SkySnow
{
	using namespace OGLShader;
	////Create Shader about Resource
	GRIVertexShaderRef GLRealTimeGRI::GRICreateVertexShader(const char* vsCode)
	{
		return OGLShader::CreateProxyShader<GRIVertexShader,OGLVertexShaderProxy>(vsCode);
	}

	GRIFragmentShaderRef GLRealTimeGRI::GRTCreateFragmentShader(const char* fsCode)
	{
		return OGLShader::CreateProxyShader<GRIFragmentShader,OGLFragementShaderProxy>(fsCode);
	}

	//Shader 创建的模板类方法(公共方法)
	//===============================================================================================
	//在GLShader中声明全局函数，主要原因是为了代码清晰度
	//其实可以在cpp文件中声明函数，使用static标记，进行隐藏，使此cpp可访问，对其它cpp文件进行隐藏
	//然后针对于隐藏，加了一个明明空间OGLShader，依次来提醒后续拓展，不要将此命名空间的全局函数在其
	//它命名空间下调用

	template<typename GRIType, typename OGLProxy>
	GRIType* OGLShader::CreateProxyShader(const char* shadercode)
	{
		OGLProxy* shaderProxy = new OGLProxy();
		OGLProxy::OGLResourceType* shaderType = CompileShader<typename OGLProxy::OGLResourceType>(shadercode, shaderProxy);
		shaderProxy->SetOGLResourceObject(shaderType);

		return shaderProxy;
	}

	template<typename ShaderType>
	ShaderType* OGLShader::CompileShader(const char* shadercode, GRIShader* GRIShader)
	{
		ShaderType* shader = new ShaderType();
		CompileCurrentShader(shader->m_GLTypeEnum,shadercode);
		return shader;
	}

	bool OGLShader::CompileCurrentShader(const GLuint ShaderType, const char* shadercode)
	{

		SN_LOG("OGL Shader Code:%s", shadercode);
		return true;
	}
	//===============================================================================================
}