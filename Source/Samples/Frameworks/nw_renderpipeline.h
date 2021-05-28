#pragma once
#include "GRIProfiles.h"
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
