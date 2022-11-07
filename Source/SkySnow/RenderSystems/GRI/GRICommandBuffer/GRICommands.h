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
#include "GRIResource.h"
#include "OSPlatform.h"
namespace SkySnow
{
	class GRICommandBuffer;
	struct GRICommandBase
	{
		virtual void ExecuteCMD(GRICommandBuffer& cmdBuffer) = 0;
		GRICommandBase* _Next = nullptr;
	};

	template<typename T>
	struct GRICommand : public GRICommandBase
	{
	public:
		void ExecuteCMD(GRICommandBuffer& cmdBuffer) override final
		{
			T* cmd = static_cast<T*>(this);
			cmd->Execute(cmdBuffer);
			cmd->~T();
		}
	};
    //RenderDrive Interface
	//======================================================================================================================
	struct GRINullCMD : public GRICommand<GRINullCMD>
	{
		void Execute(GRICommandBuffer& cmdBuffer) {}
	};
	//======================================================================================================================
	// RenderResource Set 
	
	//======================================================================================================================
	// RenderResource Create
	// CreateVertexShader
	struct GRICreateVertexShaderCMD : public GRICommand<GRICreateVertexShaderCMD>
	{
		GRICreateVertexShaderCMD(GRIVertexShaderRef handle,const char* vsCode)
			: _VsCode(vsCode)
			, _Handle(handle)
		{
		}
		void Execute(GRICommandBuffer& cmdBuffer);

		const char*			_VsCode;
		GRIVertexShaderRef	_Handle;
	};


}
