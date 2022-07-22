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
namespace SkySnow
{

	struct GLShaderStateInfo
	{
		GLShaderStateInfo()
			: gpuHandle(0)
		{

		}

		GLuint gpuHandle;
	};

	//���Կ�����Shader��Utilȫ�ֹ��ߺ���������ʹ��OGLShader��������ռ�
	//�Դ����Ѹ�ȫ��Util���ߺ���������Shaderģ��ſ��Ե��õġ�
	namespace OGLShader
	{
		template<typename GRIShaderType, typename OGLShaderType>
		GRIShaderType* CreateShader(const char* shadercode);
		//������飬���ῼ�Ƕ�������ɫ���ļ����棬��������ɫ���������ܵ���������Ż�
		//���Ҽ��뻺��hash���ƣ����������е���ɫ����������еĶ�����ɫ���ǲ�һ�µģ��б�Ҫ
		//������ɫ�������ڱ���ʱ�ķ�ϵͳ��Դ�����⡣
		template<typename OGLShaderType>
		OGLShaderType* CompileShader(const char* shadercode);

		bool CompileCurrentShader(const GLuint shaderHandle,const char* shadercode);

		bool CreateProgram(const GLuint vshandle,const GLuint fshandle,GLuint& program);

	}
}