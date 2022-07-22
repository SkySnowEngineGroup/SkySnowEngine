//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by sunguoqiang(SunGQ1987),wangcan(crygl),
//							 liuqian(SkySnow),zhangshuangxue(Calence)
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
#include "GLPlatformProfiles.h"
#include "GRICommons.h"
#include "RefCounted.h"
#include "GRIResource.h"
namespace SkySnow
{
	//Shader Resource
	class GLShaderBase //: public RefThreadSafeCounted
	{
	public:
		GLShaderBase(GLenum GLTypeEnum, ShaderFrequency shaderFrequency)
			: m_GLTypeEnum(GLTypeEnum)
			, m_ShaderFrequency(shaderFrequency)
		{
		}
		virtual ~GLShaderBase()
		{
			SN_LOG("GLShaderBase DesConstruct.");
		}


	public:
		GLenum			m_GLTypeEnum;//Shader Type at OGL
		ShaderFrequency m_ShaderFrequency;
		GLuint			m_GpuHandle;
#if Debug_Shader
		const char*		m_ShaderCode;
		std::string		mShaderName;
#endif
	};

	class GLVertexShader : public GLShaderBase , public GRIVertexShader
	{
	public:
		GLVertexShader()
			: GLShaderBase(GL_VERTEX_SHADER,SF_Vertex)
			, GRIVertexShader()
		{
		}

		~GLVertexShader()
		{
			SN_LOG("GLVertexShader DesConstruct.");
		}
	private:
	};

	class GLFragmentShader : public GLShaderBase , public GRIFragmentShader
	{
	public:
		GLFragmentShader()
			: GLShaderBase(GL_FRAGMENT_SHADER, SF_Fragement)
			, GRIFragmentShader()
		{
		}

		~GLFragmentShader()
		{
			SN_LOG("GLFragmentShader DesConstruct.");
		}
	};

	
}