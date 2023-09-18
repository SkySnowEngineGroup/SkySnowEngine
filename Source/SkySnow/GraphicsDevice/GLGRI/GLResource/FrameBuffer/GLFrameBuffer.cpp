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
#include "GLFrameBuffer.h"
#include "GRIGLDrive.h"
namespace SkySnow
{

    void RenderTargetCache::Add(RenderTargetKey& rtKey)
    {
        _RenderTargetCache[rtKey] = rtKey._RenderTarget->GetGpuHandle();
    }

    GLuint RenderTargetCache::GetRenderTarget(RenderTargetKey& rtKey)
    {
        if (_RenderTargetCache.find(rtKey) != _RenderTargetCache.end())
        {
            return _RenderTargetCache[rtKey];
        }
        return 0;
    }

    void RenderTargetCache::ReleaseRenderTarget(GRITexture* texture)
    {
        RenderTargetKey deleteKey;
        for (const auto& entry : _RenderTargetCache)
        {
            RenderTargetKey rtKey = entry.first;
            if(texture == rtKey._Texture)
            {
                deleteKey = rtKey;
                break;
            }
        }
        
        if(deleteKey._Texture != nullptr)
        {
            Delete_Object(deleteKey._RenderTarget);
            _RenderTargetCache.erase(deleteKey);
        }
    }

    void GRIGLDrive::GRIBeginRenderPass(const RenderPassInfo& rpInfo, const char* passName)
    {
        _PendingState._RenderPassInfo = rpInfo;
    }

    void GRIGLDrive::GRINextRenderSubPass()
    {

    }

    void GRIGLDrive::GRIEndRenderPass()
    {

    }

    namespace OGLRenderTarget
    {
        void SetRenderTargetAndClear(uint32 numRenderTarget, const RenderTargetView* newColorRTV, const DepthRenderTargetView* newDSRTV)
        {

        }
    }
}
