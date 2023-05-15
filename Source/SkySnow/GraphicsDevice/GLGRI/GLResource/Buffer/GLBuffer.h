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
#include "GLProfiles.h"
#include <unordered_map>
namespace SkySnow
{
	struct GLVertexElement;
	struct GLVertexBufferObject;
	typedef std::unordered_map<int, GLVertexElement>         GLVertexElements;
	typedef std::unordered_map<int, GLVertexBufferObject>    GLVertexBuffers;
    //Vertex Element Info
    struct GLVertexElement
    {
        //vertex element type:GL_FLOAT or GL_SHORT
        GLenum  _Type;
        GLuint  _Offset;
        GLuint  _Stride;
        uint8_t _AttritubeIndex;
        uint8_t _bNormalized;
        uint8_t _bConvertToFloat;
    };
    struct GLVertexBufferObject
    {
        GLenum              _BufferType;
        GLuint              _GpuHandle;
        GLuint              _Stride;
        GLuint              _Offset;
        GLVertexElements    _GLVertexElements;
    };
    //Uniform Slot Parameter
    struct GLUniformSlot
    {
        GLenum _Type;
        GLuint _Location;
        GLint  _Size;
        GLint  _Offset;
        //char*  _Name;
    };
    //Uniform Buffer Block
    struct GLUniformBufferSlot
    {
        GLuint          _BindingIndex = -1;
        GLuint          _Location = -1;
        GLint           _Offset;
        std::unordered_map<size_t, GLUniformSlot>    _UniformSlots;
        //char*  _Name;
    };
    struct GLUniformBufferSlotDesc
    {
        //A single draw is a list of uniform buffer owned by the current draw
        UniformBufferUsageType  _UBType;
        size_t                  _UBHashKey;
    };
	namespace OGLBuffer
	{

	}
}
