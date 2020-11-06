#ifndef NWRENDERPIPELINE_H
#define NWRENDERPIPELINE_H

#include <GLFW/glfw3.h>

namespace nw
{
    class RenderPipeline
    {
    public:
        RenderPipeline();
        RenderPipeline(const char* vertShaderSrc, const char* fragShaderSrc);

    private:
        GLuint loadShader(GLenum type, const char* shaderScr);

    private:
        GLuint pipeline = -1;
    };
}

#endif