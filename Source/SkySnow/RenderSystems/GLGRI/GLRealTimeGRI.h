//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
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
#include "RealTimeGRI.h"
#include "PlatformProfiles.h"

//The rendering API allocates different API header imports depending on the platform
#if PLATFORM == PLATFORM_ANDROID
#	include "GLESAndroid.h"
#elif PLATFORM == PLATFORM_IOS
#	include "GLESIos.h"
#elif PLATFORM == PLATFORM_WINDOW
#	include "GLWindow.h"
#elif PLATFORM == PLATFORM_MAC
#	include "GLMac.h"
#endif

namespace SkySnow
{
	/*
		brief: Each real-time rendering API (GRI) unifies the base class of the external interface. 
			   Different rendering APIs inherit from this class and implement the functions of 
			   different APIs with the same capability
	*/
	/*
		˼��һ������:vulkan��metal�ж���û��renderthread�ĸ����û��Context�ĸ���
					vulkan��metal�п����ڶ��CMDPool������Encoder���б��룬�����ύ
					���ᴥ������һ��context�����±������⣬��ô�ô���μ�����������ܣ�
					1.���˼·һ
					  ����GRIͳһ�ṩ��׼�ӿڣ������Encoder����з�װ�������仰˵����
					  ��Encoder���GRI���з�װ�����OGLʵ��һ�׷���vulkan&metal��Encoder����
					  ���ֻ��ƣ���Ҫ��GLGRI���д����䲻�ܵ����̳�GRI������̳�Encoder�Ľӿڸ���
					  �������Encoder�����ʹ�ã���ô���ִ���ʽ����Ҫ�������OGL�Ĵ�������Ⱦ
					  vulkan&metal��Encoder�ĸ���˴����������(������Encoder��Ҫ����������)
					  ������GLGRI�ڼ̳�һ��Encoder��˼·����֮��vulkan&metalԭ����Encoder��ֶ���
					  ��Ҫ������Ҫ˼��������
					2.��OGL��Pipeline�н��д���
					  ����˼·���ǵ������OGL����Encoder�����߼�������GLGRI�У����Ǵ��ַ�ʽ��һЩ
					  CMDlist(˫��������)˼·���ر��Ѻã���Ҫ�õ�������proxy(����)˼·�����ҿ�
					  �ܻ�Ϊ�˴����ิ�ö�ʹ��ģ���̣�����Ķ���չ������ȷʵ�ǳ�ʹ��
					  ���⣬GLGRI�Ľӿڵ�����Ҫ�ٴν��з�װ�������ڵ���GL�������ת���ŵ�GLEnv��
					  GLGRI��GLEnv����һ���̰߳�ȫ�Ĵ������ַ�ʽ�����������о��ȵ�һ�ָ�Ϊ���ӣ�
					  �������⼰�̰߳�ȫ�����ִ��븴�����⣬������Ҫ��˼���ǣ�Ŀǰ��������δ��������
					  ���ַ�ʽ�����д���
					����
					  ����˼·���ұ���˼�ǵĲ�����ȫ�����һ����֤��˼����ȱ�㣬Ŀǰ�������ڵ�һ�ַ�ʽ
					  Ҳ��UE5�Ĵ���ʽ���ڶ��ַ�ʽ��Ҫ���߼�����㡢���ݷ������о�׼˼�ǣ�����ǰ�
					  OGL��Vulkan�Ľӿ�ͳһ���й������ƶԱȣ����������жԱȣ�������������о���ܸ���
					  ����ֿ������в�ͨ(��δ�����������ⷽ�����������)
					  ��������������OGL�Ľӿڱ�׼��ȥ�滻��vulkan&metal�����������Ǹ�����Ϊ���ַ�ʽ����
					  ���ֹ�ʣ������Ⱦѹ����GPU����ô���ִ���ʽ�ڴ�����ϸС�������Ż������е���������
	
	*/
	class GLRealTimeGRI :public RealTimeGRI
	{
	public:
		GLRealTimeGRI();

		~GLRealTimeGRI() {}

		GRIFeature GetGRIFeatureType() override { return OpenGL::GetGRIFeatureType(); }
		//Test Demo
		virtual void GRIClearColor(float red, float green, float blue, float alpha) final override;
		//Create Vertex Shader
		virtual GRIVertexShaderRef GRICreateVertexShader(const char* vsCode) final override;
		//Create Fragment Shader
		virtual GRIFragmentShaderRef GRTCreateFragmentShader(const char* fsCode) final override;
		//�����ʹ�õ�һ�ַ���˼·������ӿ���GRI�㱣�����������Ǵ��麯�������麯��
		//GLGRI�ڼ̳�GLEncoder����GLEncoder�н��д��麯�������������ϲ����Encoder������
		virtual GRIPipelineShaderStateRef GRICreatePipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs) final override;
		//Create Pipeline State �˴�ͬ������
		virtual GRIGraphicsPipelineStateRef GRICreateGraphicsPipelineState() final override;
		virtual GRIBufferRef GRICreateBuffer(BufferUsageType usageType, int size,int offset, void* data) final override;
		//Call Draw,that draw primitive
		virtual void GRIDrawPrimitive(int numPrimitive, int numInstance) final override;

	private:
		//ContextState��Ⱦ������״̬�����ڱ���һ��Drawcall��״̬
		//ContextState�н���һ��LRU�Ļ�����ƣ�ContextState����һ�������Ǵ�����pipeline
		//���������е�������vulkan&metal��pipelinecache�ĸ����˶���ContextState����
		//��ΪPipelineCache����������vulkan&metal��pipelinecache����
		GLGraphicPipelineStateCache m_PipelineCache;

		//�Ѿ����ã����ύ��GPUִ�е�pipelinestate
		GLGraphicPipelineState m_PendingState;
		//�Ѿ�������GPU�е�pipelinestate
		GLGraphicPipelineState  m_ExistingState;
	};
}