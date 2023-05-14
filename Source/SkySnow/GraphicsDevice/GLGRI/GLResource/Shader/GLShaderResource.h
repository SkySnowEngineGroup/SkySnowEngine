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
#include "GRICommons.h"
#include "RefCounted.h"
#include "GRIResource.h"
#include "GLBufferResource.h"
namespace SkySnow
{
	//Shader Resource Base Class Internal
	class GLShaderBase
	{
	public:
		GLShaderBase(GLenum GLTypeEnum)
			: _GLTypeEnum(GLTypeEnum)
			, _GpuHandle(0)
#if Debug_Shader
			, _ShaderCode(nullptr)
			, mShaderName("")
#endif
		{
		}
		virtual ~GLShaderBase()
		{
			SN_LOG("GLShaderBase DesConstruct.");
		}


	public:
		GLenum			_GLTypeEnum;//Shader Type at OGL
		GLuint			_GpuHandle;
#if Debug_Shader
		const char*		_ShaderCode;
		std::string		mShaderName;
#endif
	};
    //顶点着色器
	class GLVertexShader : public GLShaderBase , public GRIVertexShader
	{
	public:
		GLVertexShader()
			: GLShaderBase(GL_VERTEX_SHADER)
			, GRIVertexShader()
		{
		}

		~GLVertexShader()
		{
			SN_LOG("GLVertexShader DesConstruct.");
		}
	private:
	};
    //片元着色器
	class GLFragmentShader : public GLShaderBase , public GRIFragmentShader
	{
	public:
		GLFragmentShader()
			: GLShaderBase(GL_FRAGMENT_SHADER)
			, GRIFragmentShader()
		{
		}

		~GLFragmentShader()
		{
			SN_LOG("GLFragmentShader DesConstruct.");
		}
	};

    //GL Program
    class GLPipelineShader : public GRIPipelineShader
    {
        typedef std::unordered_map<size_t, GLUniformBufferSlot> UniformBuffers;
    public:
        GLPipelineShader(GRIVertexShader* vs, GRIFragmentShader* fs)
            : GRIPipelineShader()
            , _ProgramId(0)
            , _OGLVertexDescriptor(nullptr)
            , _OGLVertexShader(dynamic_cast<GLVertexShader*>(vs))
            , _OGLFragmentShader(dynamic_cast<GLFragmentShader*>(fs))
        {
        }
        
        ~GLPipelineShader()
        {
            _UniformBuffers.clear();
            SN_LOG("GLPipelineShader DesConstruct");
        }
        inline GLVertexShader* GetVertexShader() { return _OGLVertexShader; }
        inline GLFragmentShader* GetFragmentShader() { return _OGLFragmentShader; }

        const GLShaderBase* GetShader(ShaderFrequency sf)
        {
            switch (sf)
            {
            case SkySnow::SF_Vertex:
                return GetVertexShader();
                break;
            case SkySnow::SF_Fragement:
                return GetFragmentShader();
                break;
            default:
                break;
            }
            return nullptr;
        }
    public:
        GLuint                  _ProgramId;
        //Cache Array or LRUCache
        GRIGLVertexDescriptor*  _OGLVertexDescriptor;
        GLVertexShader*         _OGLVertexShader;
        GLFragmentShader*       _OGLFragmentShader;
        //UBO会在此列表存储
        //0 is SingleDraw
        UniformBuffers          _UniformBuffers;
    };
}
