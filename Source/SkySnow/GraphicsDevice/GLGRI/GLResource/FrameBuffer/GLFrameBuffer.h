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
#include "GRIGLDrive.h"
#include "GRIResource.h"
#include "NonCopyable.h"
#include <unordered_map>
namespace SkySnow
{
    class GLRenderTarget;
    class RenderTargetKey;
    using RT_HashFun = HMapHashFn<RenderTargetKey>;
    typedef std::unordered_map<RenderTargetKey,uint32,RT_HashFun> RenderTargetMap;
    class RenderTargetCache : public NonCopyable
    {
    public:
        static RenderTargetCache& Instance()
        {
            static RenderTargetCache renderTargetCache;
            return renderTargetCache;
        }
        
        void Add(RenderTargetKey& rtKey);
        
        GLuint GetRenderTarget(RenderTargetKey& rtKey);
        
        void ReleaseRenderTarget(GRITexture* texture);
    private:
        RenderTargetCache(){}
        ~RenderTargetCache(){}
    private:
        RenderTargetMap     _RenderTargetCache;
    };
	class GLRenderTarget
    {
    public:
        GLRenderTarget()
            : _GPUHandle(0)
        {
        }
        ~GLRenderTarget()
        {
            glDeleteFramebuffers( 1, &_GPUHandle);
            _GPUHandle= 0;
        }
        
        uint32 GetGpuHandle()
        {
            return _GPUHandle;
        }
        
        void SetGpuHandle(uint32 gphHandle)
        {
            _GPUHandle = gphHandle;
        }

        bool operator==(const GLRenderTarget& other) const
        {
            return other._GPUHandle == _GPUHandle &&
                   other._DriveContext == _DriveContext;
        }
    private:
        GLuint          _GPUHandle;
        DriveContext*   _DriveContext;
    };
    

    struct RenderTargetKey
    {
        RenderTargetKey()
            : _RenderTarget(nullptr)
            , _Texture(nullptr)
        {
        }
        
        RenderTargetKey(GLRenderTarget* rt,GRITexture* texture)
            : _RenderTarget(rt)
            , _Texture(texture)
        {
        }
        
        bool operator==(const RenderTargetKey& other) const
        {
            return other._RenderTarget == _RenderTarget &&
                   other._Texture == _Texture;
        }
        GLRenderTarget* _RenderTarget;
        GRITexture*     _Texture;
    };
    
}