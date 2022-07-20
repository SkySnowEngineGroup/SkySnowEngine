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
#include "GLPlatformProfiles.h"
#include "RealTimeGRI.h"
#include "GLPipelineResource.h"


namespace SkySnow
{
	/*
		brief: Each real-time rendering API (GRI) unifies the base class of the external interface. 
			   Different rendering APIs inherit from this class and implement the functions of 
			   different APIs with the same capability
	*/
	/*
		思考一个问题:vulkan及metal中都是没有renderthread的概念，即没有Context的概念
					vulkan及metal中可以在多个CMDPool分配多个Encoder并行编码，并行提交
					不会触发不是一个context而导致崩溃问题，那么该处如何兼容这两个框架？
					1.解决思路一
					  对外GRI统一提供标准接口，并添加Command层进行封装处理，换句话说，即
					  用Command层对GRI进行封装，针对OGL实行一套仿照vulkan&metal的Command机制
					  这种机制，需要对GLGRI进行处理，其不能单单继承GRI，还需继承GLCommand的接口概念
					  方便后面Encoder层对其使用；那么这种处理方式，就要考虑针对OGL的处理不能污染
					  vulkan&metal的Encoder的概念，此处需谨慎考虑(核心是Command需要有类型区分)
					  可以让GLGRI在继承一个Command(比如说RenderCommand、ComputeCommand)的思路，
					  将之与vulkan&metal原生的Encoder拆分独立
					  需要后面主要思考的问题 ****** <不使用这种方式>
					2.在OGL的Pipeline中进行处理
					  这种思路将是单独针对OGL进行Encoder特殊逻辑收缩到GLGRI中，但是此种方式中一些
					  CMDlist(双向链表处理)思路将特别不友好，需要用到大量的proxy(代理)思路，并且可
					  能会为了代码简洁复用而使用模板编程，这对阅读拓展来讲，确实非常痛苦
					  另外，GLGRI的接口调用需要再次进行封装，不能在调用GL命令，而是转而放到GLEnv中
					  GLGRI与GLEnv中做一个线程安全的处理，这种方式处理起来，感觉比第一种更为复杂，
					  命令问题及线程安全及部分代码复用问题，都是需要深思熟虑，目前来看，暂未有引擎用
					  这种方式来进行处理
					综述
					  两种思路，我本人思虑的并不周全，需进一步验证与思考优缺点，目前更倾向于第一种方式
					  也是UE5的处理方式；第二种方式需要对逻辑分离点、数据分离点进行精准思虑，最好是把
					  OGL与Vulkan的接口统一进行功能相似对比，框架区别进行对比，这个处理起来感觉会很复杂
					  结果又可能是行不通(暂未看到有人在这方面进行论述过)
					  曾看到过，按照OGL的接口标准，去替换成vulkan&metal的论述，但是个人认为这种方式属于
					  饮鸩止渴，如果渲染压力在GPU，那么这种处理方式在处理起细小颗粒的优化，就有点力不从心
				    final
					  最终决定使用第一种方式。
		final最终解决方式
			拆分资源创建为RealTimeGRI
			拆分资源设置(Drawcall一次的渲染状态)为GRICommands
			对CommandBuffer层将分为GRC&GRS方式
			GRC: Graphics Render Create
			GRS: Graphics Render Set
	
	*/
	class GLRealTimeGRI : public RealTimeGRI
	{
	public:
		GLRealTimeGRI();

		~GLRealTimeGRI() {}

		GRIFeature GetGRIFeatureType() override { return OpenGL::GetFeatureType(); }
		//Test Demo
		virtual void GRIClearColor(float red, float green, float blue, float alpha) final override;
		//Create Vertex Shader
		virtual GRIVertexShaderRef GRICreateVertexShader(const char* vsCode) final override;
		//Create Fragment Shader
		virtual GRIFragmentShaderRef GRTCreateFragmentShader(const char* fsCode) final override;
		//如果是使用第一种方案思路，这个接口在GRI层保留，但不能是纯虚函数，是虚函数
		//GLGRI在继承GLEncoder，在GLEncoder中进行纯虚函数声明，方便上层调度Encoder的类型
		virtual GRIPipelineShaderStateRef GRICreatePipelineShaderState(GRIVertexShader* vs, GRIFragmentShader* fs) final override;
		//Create Pipeline State 此处同上所述--暂时不处理PipelineCache的方式，并且OGL不要调用此接口，回头统一思路
		virtual GRIGraphicsPipelineStateRef GRICreateGraphicsPipelineState() final override;
		virtual GRIBufferRef GRICreateBuffer(BufferUsageType usageType, int size,int stride, void* data) final override;

	private:
		//ContextState渲染上下文状态，其内保留一次Drawcall的状态
		//ContextState中将有一个LRU的缓存机制，ContextState另外一个作用是串联起pipeline
		//功能属性有点类似于vulkan&metal的pipelinecache的概念；因此丢弃ContextState命名
		//改为PipelineCache命名，以与vulkan&metal的pipelinecache对齐
		GLGraphicPipelineStateCache m_PipelineCache;
	};
}