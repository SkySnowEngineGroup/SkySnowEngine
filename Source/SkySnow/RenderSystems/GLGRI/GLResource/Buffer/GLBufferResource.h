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


	//GLBuffer其处理的主要对象为IndexBuffer、VertexBuffer、StructureBuffer(SSBO)
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
		//streamDraw 暂时不用
		//Static 表示VBO中的数据将不会被改动（一次指定多次使用）
		//Dynamic 表示数据将会被频繁改动（反复指定与使用）
		//Stream 表示每帧数据都要改变（一次指定一次使用）
		//draw 表示数据将被发送到GPU以待绘制（应用程序到GL）
		//read 表示数据将被客户端程序读取（GL到应用程序）
		//copy 表示数据可用于绘制与读取（GL到GL）
		//针对于indexBuffer  vertexBuffer  SSBO，即使用Draw即可
		GLBuffer(BufferUsageType usageType,GLuint size,int stride,const void* data,bool streamDraw = false)
			: GRIBuffer(usageType, size, stride) 
			, _Data(data)
			, _StreamDraw(streamDraw)
		{
			
		}

		~GLBuffer()
		{
		}
		//在GLES3.1及GL4.3以上，将顶点类型，顶点数据获取拆分为两个部分
		//因此这里只是单独的创建Buffer即可，在DrawPrimitive的时候，在根据
		//SetBuffer设置的类型进行<数据类型指定>与<数据类型如何获取>的设置
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