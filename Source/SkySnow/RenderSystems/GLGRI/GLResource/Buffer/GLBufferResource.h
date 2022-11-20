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
		friend class GRIGLDrive;
	public:
		GLBuffer()
			: GRIBuffer()
			, _BufferType(0)
			, _GpuHandle(0)
			, _StreamDraw(false)
			, _Data(nullptr)
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
		GLBuffer(BufferUsageType usageType,GLuint size,int stride,const void* data,bool streamDraw = false)
			: GRIBuffer(usageType, size, stride) 
			, _Data(data)
			, _StreamDraw(streamDraw)
		{
			
		}

		~GLBuffer()
		{
		}
		//��GLES3.1��GL4.3���ϣ����������ͣ��������ݻ�ȡ���Ϊ��������
		//�������ֻ�ǵ����Ĵ���Buffer���ɣ���DrawPrimitive��ʱ���ڸ���
		//SetBuffer���õ����ͽ���<��������ָ��>��<����������λ�ȡ>������
		void CreateBuffer(GLenum bufferType,GLenum usageType,GLuint size)
		{
			_BufferType = bufferType;
			OpenGL::GenBuffers(1,&_GpuHandle);
			OpenGL::BindBuffer(_BufferType, _GpuHandle);
			OpenGL::BufferData(_BufferType, size, _Data, IsDynamic() ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		}

	public:
		GLuint		_GpuHandle;
		GLenum		_BufferType;
	private:
		bool		_StreamDraw;
		const void* _Data;
		
	};
}