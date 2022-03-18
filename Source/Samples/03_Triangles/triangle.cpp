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
#include <stdlib.h>
#include <iostream>
#include "Application.h"
#include "LogAssert.h"
class Triangle : public SkySnow::Application
{
public:
	Triangle(const char* name, const char* description)
		: Application(name, description)
	{
        SN_LOG("Application is name:%s", name);
        SN_WARN("Application description info:%s", description);
	}
    
    ~Triangle()
    {
        SN_LOG("Trangle Application is quit.");
    }

	bool Init(int32_t argc, const char* const* _argv, uint32_t width, uint32_t height)
	{
        SN_LOG("Trangle is Initial success (width:%d, height:%d)", width,height);
	}

	void Update()
	{
        SN_LOG("Trangle is Update.");
	}

private:
    
};

SkySnow_DEFINE_APPLICATION_MAIN(
	Triangle
	, "03-Triangles"
	, "Draw Trangle At Window&MacOS."
);
