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
#pragma once
#include <stdint.h>
#include <stddef.h>
#include "AllocMacros.h"
namespace SkySnow
{
    inline uint32_t murmur3(const uint32_t* key, size_t wordCount, uint32_t seed) noexcept 
    {
        uint32_t h = seed;
        size_t i = wordCount;
        do {
            uint32_t k = *key++;
            k *= 0xcc9e2d51u;
            k = (k << 15u) | (k >> 17u);
            k *= 0x1b873593u;
            h ^= k;
            h = (h << 13u) | (h >> 19u);
            h = (h * 5u) + 0xe6546b64u;
        } while (--i);
        h ^= wordCount;
        h ^= h >> 16u;
        h *= 0x85ebca6bu;
        h ^= h >> 13u;
        h *= 0xc2b2ae35u;
        h ^= h >> 16u;
        return h;
    }

    template<typename T>
    struct HMapHashFn 
    {
        uint32_t operator()(const T& key) const noexcept 
        {
//            T& newKey = const_cast<T&>(key);
//            T* newKey1 = AlignPointer(&newKey,4);//进行四字节对齐
//            SN_LOG("origin key size:%d",sizeof(key));
//            SN_LOG("align key size:%d",sizeof(newKey1));
//            static_assert(0 == (sizeof(newKey1) & 3u), "Hashing requires a size that is a multiple of 4.");
            return murmur3((const uint32_t*)&key, sizeof(key) / 4, 0);
        }
    };
}
