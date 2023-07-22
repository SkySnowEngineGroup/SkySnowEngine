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

#include "OSPlatform.h"
#include "SkySnowProfiles.h"
#include "WindowOSPlatform.h"
#include "AndroidOSPlatform.h"
#include "IOSOSPlatform.h"
#include "MacOSPlatform.h"
#include "LinuxOSPlatform.h"
#include "LogAssert.h"
namespace SkySnow
{
    OSPlatform* CreateTargetOSPlatform()
    {
        OSPlatform* osPlatform;
        //Create Target OSPlatform
    #if PLATFORM == PLATFORM_WINDOW
        osPlatform = new WindowOSPlatform();
    #elif PLATFORM == PLATFORM_IOS
        osPlatform = new IOSOSPlatform();
    #elif PLATFORM == PLATFORM_MAC
        osPlatform = new MacOSPlatform();
    #elif PLATFORM == PLATFORM_ANDROID
        osPlatform = new AndroidOSPlatform();
    #elif  PLATFORM == PLATFORM_LINUX
        osPlatform = new LinuxOSPlatform();
    #endif
        return osPlatform;
    }
}
