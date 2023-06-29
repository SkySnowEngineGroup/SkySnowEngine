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
#include "GLBase.h"

namespace SkySnow
{
	class OpenGL3 : public OpenGLBase
	{
	public:
		//后面将在这里进行BufferCache的优化操作
		static void inline GenBuffers(GLsizei size, GLuint* buffer)
		{
			glGenBuffers(size,buffer);
		}
        static inline bool TexStorage3D(GLenum target, GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type)
        {
            if(SupportStorageTexture())
            {
                glTexStorage3D(target, levels, internalFormat, width, height, depth);
                return true;
            }
            else
            {
                //bool isArray = target == GL_TEXTURE_2D_ARRAY || target == GL_TEXTURE_CUBE_MAP_ARRAY;
                //for(int il = 0; il < levels; il ++)
                //{
                //    glTexImage3D(
                //                 target,
                //                 il,
                //                 internalFormat,
                //                 std::max<uint32>(1,(width >> il)),
                //                 std::max<uint32>(1,(width >> il)),
                //                 (isArray) ? depth : std::max<uint32>(1,(depth >> il)),
                //                 0,
                //                 format,
                //                 type,
                //                 NULL);
                //}
                return false;
            }
        }
        static inline bool TexStorage2D(GLenum target, GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLenum format,GLenum type)
        {
            if(SupportStorageTexture())
            {
                glTexStorage2D(target, levels, internalFormat, width, height);
                return true;
            }
            else
            {
                //for(int il = 0; il < levels; il ++)
                //{
                //    glTexImage2D(
                //                 target,
                //                 il,
                //                 internalFormat,
                //                 std::max<uint32>(1,(width >> il)),
                //                 std::max<uint32>(1,(width >> il)),
                //                 0,
                //                 format,
                //                 type,
                //                 nullptr);
                //}
                return false;
            }
        }
		static void InitialExtensions();
	};
}
