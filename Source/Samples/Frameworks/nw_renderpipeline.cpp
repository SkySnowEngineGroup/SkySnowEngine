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
#include "nw_renderpipeline.h"

namespace nw
{
    RenderPipeline::RenderPipeline()
        :pipeline(-1)
    {

    }

    RenderPipeline::RenderPipeline(const char* vertShaderSrc, const char* fragShaderSrc)
    {

    }

    GLuint RenderPipeline::loadShader(GLenum type, const char* shaderSrc)
    {
        GLuint shader;
        GLint compiled;

        //Create the shader object
        shader = glCreateShader(type);

        if(shader == 0)
        {
            return 0;
        }

        //Load the shader source
        glShaderSource(shader, 1, &shaderSrc, NULL);

        //Compile the shader
        glCompileShader(shader);

        // Check the compile status
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if(!compiled)
        {
            GLint infoLen = 0;
            
        }

        return 0;
    }
}