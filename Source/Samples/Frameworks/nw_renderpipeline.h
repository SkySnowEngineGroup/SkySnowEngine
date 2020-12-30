#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace nw
{
    class RenderPipeline
    {
    public:
        RenderPipeline();
        RenderPipeline(const char* vertShaderSrc, const char* fragShaderSrc);

    private:
        GLuint loadShader(GLenum type, const char* shaderSrc);

    private:
        GLuint pipeline = -1;
    };
}
