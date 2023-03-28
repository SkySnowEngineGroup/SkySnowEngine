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
#include <stdlib.h>
#include <iostream>
#include "Application.h"
#include "LogAssert.h"
#include "File.h"
#include "GRI.h"
#include "GRICommandBuffer.h"
using namespace SkySnow;
class Triangle : public SkySnow::Application
{
public:
	Triangle(const char* name, const char* description)
		: Application(name, description)
		, _File(nullptr)
		, _VsData(nullptr)
		, _FsData(nullptr)
	{
		_CMBPool = new GRICommandBufferPool();
        SN_LOG("Application is name:%s", name);
        SN_WARN("Application description info:%s", description);
	}
    
    ~Triangle()
    {
		SN_LOG("Trangle Application is quit.");
		Delete_Object(_File);
		Delete_Object(_VsData);
		Delete_Object(_FsData);
		GRIExit();
    }

	bool Init(int32_t argc, const char* const* _argv, uint32_t width, uint32_t height)
	{
        OSPlatformInfo osPlatformInfo;
        osPlatformInfo._NativeWindow = GetNativeWindow();
		GRIInit(osPlatformInfo);
		_CMB = (GRIRenderCommandBuffer*)_CMBPool->AllocCommandBuffer();
        SN_LOG("Trangle is Initial success (width:%d, height:%d)", width,height);
		string vsShaderPath = GetMaterialAllPath("Test/BaseVertex.sns");
		string fsShaderPath = GetMaterialAllPath("Test/BaseFragment.sns");
		_File = new File();
		_VsData = new Data();
		_FsData = new Data();
		_File->ReadData(vsShaderPath, _VsData);
		_File->ReadData(fsShaderPath, _FsData);

		GRICreateGraphicsPipelineStateInfo psoCreateInfo;

		_vsRef = CreateVertexShader((char*)_VsData->GetBytes());
		_fsRef = CreateFragmentShader((char*)_FsData->GetBytes());
		_PipelineShaderStateRef = CreatePipelineShaderState(_vsRef, _fsRef);
		float vertices[] = { -0.5f, -0.5f, 0.0f,
							 0.5f,  -0.5f, 0.0f,
							 0.0f,  0.5f,  0.0f};
		SN_LOG("Vertex Size:%d",sizeof(vertices));
		psoCreateInfo._PrimitiveType = PrimitiveType::PT_Lines;
		_VertexBufferRef = CreateBuffer(BufferUsageType::BUT_VertexBuffer,
												sizeof(vertices),
												3,
												vertices);
		_PSORef = CreateGraphicsPipelineState(psoCreateInfo);

		//SN_LOG("Major:%d", OpenGL::GetMajorVersion());
		//SN_LOG("Minor:%d", OpenGL::GetMinorVersion());
//
//		void* pt1 = _MemStack.Alloc(4);
//		void* pt2 = _MemStack.Alloc(4);
//		void* pt3 = _MemStack.Alloc(4);
//		void* pt4 = _MemStack.Alloc(4);
//		SN_LOG("pt1:%p", pt1);
//		SN_LOG("pt2:%p", pt2);
//		SN_LOG("pt3:%p", pt3);
//		SN_LOG("pt4:%p", pt4);
//		_MemStack.Flush();
		return 0;
	}

	void Update()
	{
		_GQueue->BeginFrame();

		GRIResource::FlushResourceRelease();

		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0,0.0,0.0,1.0);

		_CMB->CmdBeginCommandBuffer();
		_CMB->CmdBeginRenderPass();

		_CMB->CmdSetBuffer(0,_VertexBufferRef,0);
		_CMB->CmdSetPipelineShaderState(_PipelineShaderStateRef);
		_CMB->CmdSetGraphicsPipelineState(_PSORef);
		_CMB->CmdDrawPrimitive(3,1);

		_CMB->CmdEndRenderPass();
		_CMB->CmdEndCommandBuffer();

		_GQueue->SubmitQueue(_CMB);
		_GQueue->PresentQueue();

		_GQueue->EndFrame();
	}

private:
	MemStack				    _MemStack;
	File*					    _File;
	Data*					    _VsData;
	Data*					    _FsData;
	GRIVertexShaderRef		    _vsRef;
	GRIFragmentShaderRef	    _fsRef;
	GRIBufferRef			    _VertexBufferRef;
	GRIPipelineShaderStateRef   _PipelineShaderStateRef;
	GRIGraphicsPipelineStateRef _PSORef;
	GRICommandBufferPool*	    _CMBPool;
	GRIRenderCommandBuffer*	    _CMB;
};

SkySnow_DEFINE_APPLICATION_MAIN(
	Triangle
	, "03-Triangles"
	, "Draw Trangle At Window&MacOS."
);
