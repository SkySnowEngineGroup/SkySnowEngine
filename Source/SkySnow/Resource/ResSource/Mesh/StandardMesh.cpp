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
#include "StandardMesh.h"

namespace SkySnow
{
	void MQuad::InitData()
	{
		/*
		*		0--------1
		*		|		 |	
		*		|		 |
		*		|		 |
		*	    3--------2
		*/
		std::vector<float> tempVertex =
		{
			-1, 1,0, 0,0,1, 0,1,//0
			-1,-1,0, 0,0,1, 0,0,//3
			 1,-1,0, 0,0,1, 1,0,//2

			-1, 1,0, 0,0,1, 0,1,//0
			 1,-1,0, 0,0,1, 1,0,//2
			 1, 1,0, 0,0,1, 1,1 //1
		};
		int stride = 8;
		int davCount = 6;

		_ArrayStream = CreateSPtr<VertexStream>();
        _ArrayStream->ReserveBuffer(davCount);
		_ArrayStream->AddVertexElementSlot(VLS_TexCoord0, VertexElementType::VET_Float2);
		_ArrayStream->AddVertexElementSlot(VLS_Normal, VertexElementType::VET_Float3);
        _ArrayStream->AddVertexElementSlot(VLS_Position, VertexElementType::VET_Float3);
        
		for (int i = 0; i < davCount; i ++)
		{
			float px = tempVertex[i * stride + 0];
			float py = tempVertex[i * stride + 1];
			float pz = tempVertex[i * stride + 2];

			float nx = tempVertex[i * stride + 3];
			float ny = tempVertex[i * stride + 4];
			float nz = tempVertex[i * stride + 5];

			float ux = tempVertex[i * stride + 6];
			float uy = tempVertex[i * stride + 7];

            _ArrayStream->PushVertex<Vector2f>(VLS_TexCoord0, Vector2f(ux,uy));
			_ArrayStream->PushVertex<Vector3f>(VLS_Position, Vector3f(px,py,pz));
			_ArrayStream->PushVertex<Vector3f>(VLS_Normal, Vector3f(nx,ny,nz));
			
		}
	}
}
