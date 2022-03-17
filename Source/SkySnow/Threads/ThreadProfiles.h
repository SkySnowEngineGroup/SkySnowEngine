//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
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
#include "PlatformProfiles.h"
#if PLATFORM == PLATFORM_IOS
#include <unistd.h>
#endif // PLATFORM == PLATFORM_IOS
namespace SkySnow
{
	enum ThreadPriority
	{
		ETP_Low = 0,
		ETP_Normal = 1,
		ETP_Hight = 2
	};
    //该函数可用宏定义，但是本人讨厌宏编程，因此使用c类型函数
    static void SNSleep(unsigned int millisecond)//单位ms
    {
#if PLATFORM == PLATFORM_IOS || PLATFORM == PLATFORM_MAC
            sleep(millisecond/1000);//该接口ios为秒
#else
            Sleep(millisecond);
#endif
    }
}
