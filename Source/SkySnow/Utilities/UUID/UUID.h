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
#include <stdint.h>
#include "Variable.h"
#include "HashHeader.h"
#include "Random.h"

namespace SkySnow
{
    class UUID
    {
    public:
        UUID();
        UUID(uint64 uuid);
        UUID(const UUID& other);
        ~UUID() = default;
        UUID& operator=(const UUID& other)
        {
            if(this == &other)
                return *this;
            _UUID = other._UUID;
            return *this;
        }
        constexpr bool operator==(const UUID& rhs) const { return _UUID == rhs._UUID;}
        constexpr bool operator!=(const UUID& rhs) const { return !(*this == rhs); }
        constexpr bool Empty() const { return _UUID == 0;}
        operator uint64(){ return _UUID;}
        operator const uint64() const {return _UUID;}
        static UUID EMPTY;
    private:
        uint64 _UUID = 0;
    };
}

namespace std
{
    template<>
    struct hash<SkySnow::UUID>
    {
        std::size_t operator()(const SkySnow::UUID& uuid) const
        {
            const size_t hash = std::hash<size_t>()((uint64_t)uuid);
            return hash;
        }
    };
}
