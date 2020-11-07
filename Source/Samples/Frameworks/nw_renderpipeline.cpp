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