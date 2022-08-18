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
	public:
		GLBuffer()
			: GRIBuffer()
			, _BufferType(0)
			, _GpuHandle(0)
			, b_StreamDraw(false)
			, m_Data(nullptr)
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
		GLBuffer(GLenum bufferType,BufferUsageType usageType,GLuint size,int stride,const void* data,bool streamDraw = false)
			: GRIBuffer(usageType, size, stride)
			, _BufferType(bufferType)
			, m_Data(data)
			, b_StreamDraw(streamDraw)
		{
			CreateBuffer(usageType,size);
		}

		~GLBuffer()
		{
		}
		//在GLES3.1及GL4.3以上，将顶点类型，顶点数据获取拆分为两个部分
		//因此这里只是单独的创建Buffer即可，在DrawPrimitive的时候，在根据
		//SetBuffer设置的类型进行<数据类型指定>与<数据类型如何获取>的设置
		//对于数据的类型，一种是结构数组SOA，一种是数组结构AOS
		//对于AOS来说，VBO1对应Position，VBO2对应法线......
		//对于SOA来说，VBO中的数据对应有V/N/T(顶点、法线、uv等)，其组装格式有
		//V/N/UV/V/N/UV 或者 V/V/V/N/N/N/UV/UV/UV 对于此种需要计算offset，即计算layout布局
		//从性能上来讲，AOS是优于SOA的，但是Mali显卡有IDVS架构，在显卡级别处理将SOA处理为AOS的操作(这个操作也会浪费一部分GPU的资源)
		//glBufferData的作用是初始化数据，而glBufferSubData的作用是初始化或更新数据
		//因此可以使用glBufferSubData代替glBufferData，其基础功能一样，但是glBufferSubData功能多一些，其处理非交叉的SOA数据更简单快捷一些
		void CreateBuffer(GLenum usageType,GLuint size)
		{
			OpenGL::GenBuffers(1,&_GpuHandle);
			OpenGL::BindBuffer(_BufferType, _GpuHandle);
			OpenGL::BufferData(_BufferType, size, m_Data, IsDynamic() ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

			//glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE,m_Stride * sizeof(GLfloat),(GLvoid*)0);
			//glBindBuffer(_BufferType,0);
		}

	public:
		GLuint		_GpuHandle;
		GLenum		_BufferType;
	private:
		bool		b_StreamDraw;
		const void* m_Data;
		
	};
}