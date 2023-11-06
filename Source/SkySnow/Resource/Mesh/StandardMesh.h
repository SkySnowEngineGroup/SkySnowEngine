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
#include "SPtr.h"
#include <vector>
namespace SkySnow
{
	enum DefaultMeshType
	{
		DMT_None,
		DMT_Quad,
		DMT_Cube,
		DMT_Sphere,
		DMT_Cone
	};
	struct Pos
	{
		Pos(float vx,float vy,float vz)
			: x(vx)
			, y(vy)
			, z(vz)
		{
		}
		float x = 0;
		float y = 0;
		float z = 0;
	};
	struct Uv
	{
		Uv(float uvx,float uvy)
			: u(uvx)
			, v(uvy)
		{
		}
		float u = 0;
		float v = 0;
	};
	struct Normal
	{
		Normal(float nx,float ny,float nz)
			: x(nx)
			, y(ny)
			, z(nz)
		{
		}
		float x = 0;
		float y = 0;
		float z = 0;
	};
	
	struct VMeta
	{
		VMeta(Pos ver,Uv uv,Normal nor)
			: _Vertex(ver)
			, _Uv(uv)
			, _Normal(nor)
		{
		}
		VMeta(float vx,float vy,float vz,
			  float uvx,float uvy,
			  float nx,float ny,float nz)
			: _Vertex(vx,vy,vz)
			, _Uv(uvx,uvy)
			, _Normal(nx,ny,nz)
		{
		}
		Pos		_Vertex;
		Uv		_Uv;
		Normal	_Normal;
	};
	struct MQuad
	{
		MQuad()
		{
			InitData();
		}
		std::vector<Pos>	_Poss;
		//DrawElement
		std::vector<VMeta>	_Vertexs;
		std::vector<int>	_Indices;
		//DrawArray
		std::vector<VMeta>	_VertexArray;
		
	private:
		void InitData();
	};

	struct MCube
	{
        float* _Vertex = new float[]
                            {   0.5,0.5,0.5,
                                0.5,0.5,-0.5,
                                -0.5,0.5,-0.5,
                                -0.5,0.5,0.5,//
                                0.5,-0.5,0.5,
                                0.5,-0.5,-0.5,
                                -0.5,-0.5,-0.5,
                                -0.5,-0.5,0.5};
	};

	struct MSphere
	{

	};

	struct MCone
	{

	};
}
