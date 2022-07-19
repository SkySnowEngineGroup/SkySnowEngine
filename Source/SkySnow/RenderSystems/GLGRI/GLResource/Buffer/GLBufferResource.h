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
#include "GLPlatformProfiles.h"
#include "GRIResource.h"
#include "GLBuffer.h"

namespace SkySnow
{
	//IndexBuffer
	//VertexBuffer
	//UniformBuffer
	//SSBO
	//MapBuffer&unMapBuffer
	//TranstBuffer
	//PackPixelBuffer&unPackPixelBuffer


	//GLBuffer�䴦�����Ҫ����ΪIndexBuffer��VertexBuffer��StructureBuffer(SSBO)
	class GLBuffer : public GRIBuffer
	{
	public:
		GLBuffer()
			: GRIBuffer()
		{
		}
		//streamDraw ��ʱ����
		//Static ��ʾVBO�е����ݽ����ᱻ�Ķ���һ��ָ�����ʹ�ã�
		//Dynamic ��ʾ���ݽ��ᱻƵ���Ķ�������ָ����ʹ�ã�
		//Stream ��ʾÿ֡���ݶ�Ҫ�ı䣨һ��ָ��һ��ʹ�ã�
		//draw ��ʾ���ݽ������͵�GPU�Դ����ƣ�Ӧ�ó���GL��
		//read ��ʾ���ݽ����ͻ��˳����ȡ��GL��Ӧ�ó���
		//copy ��ʾ���ݿ����ڻ������ȡ��GL��GL��
		//�����indexBuffer  vertexBuffer  SSBO����ʹ��Draw����
		GLBuffer(GLenum bufferType,BufferUsageType usageType,GLuint size,int stride,const void* data,bool streamDraw = false)
			: GRIBuffer(usageType, size, stride)
			, m_BufferType(bufferType)
			, m_Data(data)
			, b_StreamDraw(streamDraw)
		{
			CreateBuffer(usageType,size);
		}

		~GLBuffer()
		{
		}
		//��GLES3.1��GL4.3���ϣ����������ͣ��������ݻ�ȡ���Ϊ��������
		//�������ֻ�ǵ����Ĵ���Buffer���ɣ���DrawPrimitive��ʱ���ڸ���
		//SetBuffer���õ����ͽ���<��������ָ��>��<����������λ�ȡ>������
		//�������ݵ����ͣ�һ���ǽṹ����SOA��һ��������ṹAOS
		//����AOS��˵��VBO1��ӦPosition��VBO2��Ӧ����......
		//����SOA��˵��VBO�е����ݶ�Ӧ��V/N/T(���㡢���ߡ�uv��)������װ��ʽ��
		//V/N/UV/V/N/UV ���� V/V/V/N/N/N/UV/UV/UV ���ڴ�����Ҫ����offset��������layout����
		//��������������AOS������SOA�ģ�����Mali�Կ���IDVS�ܹ������Կ�������SOA����ΪAOS�Ĳ���(�������Ҳ���˷�һ����GPU����Դ)
		//glBufferData�������ǳ�ʼ�����ݣ���glBufferSubData�������ǳ�ʼ�����������
		//��˿���ʹ��glBufferSubData����glBufferData�����������һ��������glBufferSubData���ܶ�һЩ���䴦��ǽ����SOA���ݸ��򵥿��һЩ
		void CreateBuffer(GLenum usageType,GLuint size)
		{
			glGenVertexArrays(1,&m_Vao);
			glBindVertexArray(m_Vao);

			OpenGL::GenBuffers(1,&m_GPUHandle);
			OpenGL::BindBuffer(m_BufferType,m_GPUHandle);
			OpenGL::BufferData(m_BufferType, size, m_Data, IsDynamic() ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
			//�ú������ƶ���DrawPrimitive�����У�����PipelineState���д�������������Դ��GRISetBuffer
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_Stride*sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			
			glBindBuffer(m_BufferType,0);
			glBindVertexArray(0);
		}

	public:
		GLuint		m_Vao;
		GLenum		m_BufferType;
	private:
		bool		b_StreamDraw;
		GLuint		m_GPUHandle;
		const void* m_Data;
		
	};
}