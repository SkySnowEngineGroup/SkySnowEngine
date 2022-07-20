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
#include "GLShaderResource.h"
#include "GLBufferResource.h"
#include "GLBuffer.h"
#include "GLShader.h"

namespace SkySnow
{
	class GLPipelineShaderState : public GRIPipelineShaderState
	{
	public:
		GLPipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs)
			: GRIPipelineShaderState()
			, m_OGLVertexShader(dynamic_cast<GLVertexShader*>(vs))
			, m_OGLFragmentShader(dynamic_cast<GLFragmentShader*>(fs))
		{
		}

		inline GLVertexShader* GetVertexShader() { return m_OGLVertexShader; }
		inline GLFragmentShader* GetFragmentShader() { return m_OGLFragmentShader; }

		const GLShaderBase* GetShader(ShaderFrequency sf)
		{
			switch (sf)
			{
			case SkySnow::SF_Vertex:
				return GetVertexShader();
				break;
			case SkySnow::SF_Fragement:
				return GetFragmentShader();
				break;
			default:
				break;
			}
			return nullptr;
		}
	public:
		GLuint m_ProgramId;
	private:
		//Cache Array or LRUCache
		//temp is ptr
		GLVertexShader* m_OGLVertexShader;
		GLFragmentShader* m_OGLFragmentShader;
		
	};
	// ��vulkan�У���Drawcall֮ǰ���Ὣ��Ⱦ��Դ���а������ã���ô������Ƿ���Vulkan��˼·
	class GLGraphicPipelineState : public GRIGraphicsPipelineState
	{
	public:
		GLGraphicPipelineState()
			: GRIGraphicsPipelineState()
		{
		}

		virtual ~GLGraphicPipelineState()
		{
		}
	public:
		GLBufferInfo			vertexBufferInfo[Num_GL_Vertex_Attribute];
		GLShaderStateInfo		shaderStateInfo;
		//������˵�����ǵ��ǽ�ͼԪ������GLBuffer���ã����ǿ��ǵ���Runtime��ʱ��
		//���ܻ��޸�ͼԪ�����ͣ���ô��õķ�ʽ�Ƿ���PipelineState�С�
		PrimitiveType			primitiveType;
	};
	//����������vulkan&metal��pipelinecache
	//��UE5�������Ƶĸ�����Ǵ����������
	//��ContextStateʵ����PipelineCache��ͻ(���ҵ��������������ʷ����)
	//(vulkan&metal��pipelinestate�ɴ洢��Ӳ�������ϣ������ڶ�������ɫ����)
	//��ContextState���߱�������
	//SkySnowΪ��ͳһOpenGL��Vulkan&Metal�Ĺ淶����˾�������
	//ContextState�ĸ��ת��ʹ��PipelineCache�ĸ��
	class GLGraphicPipelineStateCache
	{
	public:

	};
}