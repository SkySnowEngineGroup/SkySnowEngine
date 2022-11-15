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
#include <stdlib.h>
#include <iostream>
#include "Application.h"
#include "LogAssert.h"
#include "GRIProfiles.h"
#include "OSPlatform.h"
#include "File.h"
#include "SkySnowConfigInfo.h"
#include "StackAllocator.h"
#include "GRICommandBuffer.h"
using namespace SkySnow;
class Triangle : public SkySnow::Application
{
public:
	Triangle(const char* name, const char* description)
		: Application(name, description)
		, m_File(nullptr)
		, m_VsData(nullptr)
		, m_FsData(nullptr)
	{
		_GQueue.Init();
        SN_LOG("Application is name:%s", name);
        SN_WARN("Application description info:%s", description);
	}
    
    ~Triangle()
    {
        SN_LOG("Trangle Application is quit.");
		Delete_Object(m_File);
		Delete_Object(m_VsData);
		Delete_Object(m_FsData);
    }

	bool Init(int32_t argc, const char* const* _argv, uint32_t width, uint32_t height)
	{
        SN_LOG("Trangle is Initial success (width:%d, height:%d)", width,height);
		string vsShaderPath = GetMaterialAllPath("Test/BaseVertex.sns");
		string fsShaderPath = GetMaterialAllPath("Test/BaseFragment.sns");
		m_File = new File();
		m_VsData = new Data();
		m_FsData = new Data();
		m_File->ReadData(vsShaderPath, m_VsData);
		m_File->ReadData(fsShaderPath, m_FsData);

		GRICreateGraphicsPipelineStateInfo psoCreateInfo;
		
		m_vsRef = GRI->GRICreateVertexShader((char*)m_VsData->GetBytes());
		m_fsRef = GRI->GRTCreateFragmentShader((char*)m_FsData->GetBytes());
		m_PipelineShaderStateRef = GRI->GRICreatePipelineShaderState(m_vsRef, m_fsRef);
		float vertices[] = { -0.5f, -0.5f, 0.0f,
							 0.5f,  -0.5f, 0.0f,
							 0.0f,  0.5f,  0.0f};
		SN_LOG("Vertex Size:%d",sizeof(vertices));
		psoCreateInfo._PrimitiveType = PrimitiveType::PT_Lines;
		m_VertexBufferRef = GRI->GRICreateBuffer(BufferUsageType::BUT_VertexBuffer,
												sizeof(vertices),
												3, 
												vertices);
		m_PSORef = GRI->GRICreateGraphicsPipelineState(psoCreateInfo);

		SN_LOG("Major:%d", OpenGL::GetMajorVersion());
		SN_LOG("Minor:%d", OpenGL::GetMinorVersion());

		//void* pt1 = m_MemStack.Alloc(4);
		//void* pt2 = m_MemStack.Alloc(4);
		//void* pt3 = m_MemStack.Alloc(4);
		//void* pt4 = m_MemStack.Alloc(4);
		//SN_LOG("pt1:%p", pt1);
		//SN_LOG("pt2:%p", pt2);
		//SN_LOG("pt3:%p", pt3);
		//SN_LOG("pt4:%p", pt4);
		//m_MemStack.Flush();
		return 0;
	}

	void Update()
	{
		GRIResource::FlushResourceRelease();
		GRI->GRIClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		
		GRI->GRISetBuffer(0,m_VertexBufferRef,0);
		GRI->GRISetPipelineShaderState(m_PipelineShaderStateRef);
		GRI->GRISetGraphicsPipelineState(m_PSORef);
		GRI->GRIDrawPrimitive(3,1);
	}

private:
	MemStack				m_MemStack;
	File*					m_File;
	Data*					m_VsData;
	Data*					m_FsData;
	GRIVertexShaderRef		m_vsRef;
	GRIFragmentShaderRef	m_fsRef;
	GRIBufferRef			m_VertexBufferRef;
	GRIPipelineShaderStateRef m_PipelineShaderStateRef;
	GRIGraphicsPipelineStateRef m_PSORef;
};

SkySnow_DEFINE_APPLICATION_MAIN(
	Triangle
	, "03-Triangles"
	, "Draw Trangle At Window&MacOS."
);
