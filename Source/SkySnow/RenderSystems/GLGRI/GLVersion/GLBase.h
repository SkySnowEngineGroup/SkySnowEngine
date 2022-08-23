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
#include "Imports_GL.h"
#include "Imports_GLES.h"
#include <string>
//����API�汾�������ı�׼���У������ڴ���վ��ѯ:https://docs.gl/
//������ں��ı�׼��API�����������ض��壬ֻ������������һЩ��չ����֧�ֺ����ж�
//��Import_GL&Import_GLES�޸�֧�ֵı�־λ�����������ض��嵽Import_GL&Import_GLES��
namespace SkySnow
{
	class OpenGLBase
	{
	public:
		//static inline GRIFeature GetFeatureType() { return ENone; }

		static inline GLuint CreateShader(GLenum shadertype) 
		{ 
			return glCreateShader(shadertype); 
		}

		static inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
		{
			glBufferSubData(target,offset,size,data);
		}
		static inline void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
		{
			glBufferData(target,size,data,usage);
		}
		//���Ʒ���\��������\SSBO�İ�
		static inline void BindBuffer(GLenum type,GLuint buffer)
		{
			glBindBuffer(type, buffer);
		}
		static inline void InitialTest()
		{
			ui_MajorVersion = 3;
			ui_MinorVersion = 2;
		}
		
		static inline bool SupportVertexFormatBinding() { return b_SupportVertexFormatBinding; };
		static inline GLuint GetMajorVersion() { return ui_MajorVersion; };
		static inline GLuint GetMinorVersion() { return ui_MinorVersion; };
		static void InitialExtensions();
	protected:
		static void CheckExtensions(const std::string& targetStr);
	protected:
		static bool		b_SupportVertexFormatBinding;
		static GLuint	ui_MajorVersion;
		static GLuint	ui_MinorVersion;
	};
}