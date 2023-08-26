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
#include "HashUtil.h"

namespace SkySnow
{
    uint64_t FingerprintString(const char* s, size_t len) {
        const uint64_t seed = 0x87654321;
        const int hash_loop_count = (len / 8) + 1;
        uint64_t hash = seed;

        for (int i = 0; i < hash_loop_count; ++i) {
            const int off = i * 8;
            const int num_chars_left = len - (off);
            uint64_t new_hash = seed;

            if (num_chars_left > 7) {
                const int off2 = i * 8;
                new_hash = static_cast<uint64_t>(s[off2]) << 56 |
                    static_cast<uint64_t>(s[off2 + 1]) << 48 |
                    static_cast<uint64_t>(s[off2 + 2]) << 40 |
                    static_cast<uint64_t>(s[off2 + 3]) << 32 |
                    static_cast<uint64_t>(s[off2 + 4]) << 24 |
                    static_cast<uint64_t>(s[off2 + 5]) << 16 |
                    static_cast<uint64_t>(s[off2 + 6]) << 8 | s[off2 + 7];
            }
            else {
                for (int j = 0; j < num_chars_left; ++j) {
                    new_hash |= static_cast<uint64_t>(s[off + j])
                        << (64 - ((num_chars_left - j) * 8));
                }
            }

            hash = HashCombine(new_hash, hash);
        }

        if (hash < std::numeric_limits<uint64_t>::max() - 1)
            hash += 2;
        return hash;
    }
}