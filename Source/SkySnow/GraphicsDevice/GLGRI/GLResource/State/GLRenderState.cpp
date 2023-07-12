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
#include "GLProfiles.h"
#include "GRICommons.h"
#include "GRIResource.h"
#include "GRIGLDrive.h"
#include "GLRenderStateResource.h"
#include "GLRenderState.h"
namespace SkySnow
{
    void GRIGLDrive::GRICreateSampler(const SamplerState& sState, GRISamplerStateRef& handle)
    {
        OGLState::CreateSamplerState(handle, sState);
    }

    //RenderState Rasterizer
    void GRIGLDrive::GRICreateRasterizer(const RasterizerStateInfo& state, GRIRasterizerStateRef& handle)
    {

    }
    //RenderState DepthStencil
    void GRIGLDrive::GRICreateDepthStencil(const DepthStencilStateInfo& state, GRIDepthStencilStateRef& handle)
    {

    }
    //RenderState BlendState
    void GRIGLDrive::GRICreateBlendState(const BlendStateInfo& state, GRIBlendStateRef& handle)
    {

    }

    namespace OGLState
    {
        void CreateSamplerState(GRISamplerStateRef& handle,const SamplerState& sState)
        {
            GRIGLSamplerState* sampler = dynamic_cast<GRIGLSamplerState*>(handle.GetReference());
            
            sampler->_WrapS = SamplerAddressMode(sState._AddressU);
            sampler->_WrapT = SamplerAddressMode(sState._AddressV);
            sampler->_WrapR = SamplerAddressMode(sState._AddressW);
            sampler->_LodBias = sState._MipBias;
            
            const bool comparisonEnabled = (sState._CompareFun != SCF_Never);
            
            switch(sState._Filter)
            {
                case SF_Point:
                    sampler->_MagFilter = GL_NEAREST;
                    sampler->_MinFilter = GL_NEAREST_MIPMAP_NEAREST;

                    break;
                case SF_Bilinear:
                    sampler->_MagFilter = GL_LINEAR;
                    sampler->_MinFilter = GL_LINEAR_MIPMAP_NEAREST;
                    break;
                case SF_Trilinear:
                    sampler->_MagFilter = GL_LINEAR;
                    sampler->_MinFilter = comparisonEnabled ? GL_LINEAR : GL_LINEAR_MIPMAP_LINEAR;
                    break;
                case SF_AnisotropicLinear:
                    sampler->_MagFilter = GL_LINEAR;
                    sampler->_MinFilter = comparisonEnabled ? GL_LINEAR : GL_LINEAR_MIPMAP_LINEAR;
                    sampler->_MaxAnisotropy = 1;//TODO: Cala
                    break;
                default:
                    SN_WARN("SkySnowEngine Not Support SamplerFilter Id:%d",sState._Filter);
                    break;
            }

            if (comparisonEnabled)
            {
                sampler->_CompareMode = GL_COMPARE_REF_TO_TEXTURE;
                sampler->_CompareFunc = GL_LESS;
            }
            else
            {
                sampler->_CompareMode = GL_NONE;
            }


            glGenSamplers(1, &sampler->_GpuHandle);

            glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_WRAP_S, sampler->_WrapS);
            glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_WRAP_T, sampler->_WrapT);
            if (OpenGL::SupportTex3D())
            {
                glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_WRAP_R, sampler->_WrapR);
            }
            if (OpenGL::SupportTexLODBias())
            {
                glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_LOD_BIAS, sampler->_LodBias);
            }

            glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_MIN_FILTER, sampler->_MinFilter);
            glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_MAG_FILTER, sampler->_MagFilter);
            if (OpenGL::SupportsTexFilterAnisotropic())
            {
                glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_MAX_ANISOTROPY_EXT, sampler->_MaxAnisotropy);
            }

            if (OpenGL::SupportsTexCompare())
            {
                glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_COMPARE_MODE, sampler->_CompareMode);
                glSamplerParameteri(sampler->_GpuHandle, GL_TEXTURE_COMPARE_FUNC, sampler->_CompareFunc);
            }
        }
    
        GLenum SamplerGLAddressSTR(SamplerAddressMode address)
        {
            switch(address)
            {
                case SAM_Clamp:
                    return GL_CLAMP_TO_EDGE;
                    break;
                case SAM_Mirror:
                    return GL_MIRRORED_REPEAT;
                    break;
                case SAM_Border:
                    return GL_CLAMP_TO_BORDER;
                    break;
                default:
                    return GL_REPEAT;
                    break;
            }
        }
    }
}
