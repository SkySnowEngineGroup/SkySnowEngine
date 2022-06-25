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
#include "Object.h"
#include <string>
#include "Data.h"
using namespace std;
namespace SkySnow
{

	enum Status
	{
		Ok = 0,
		NotExists = 1,
		OpenFailed = 2,
		ReadFailed = 3,
		NotInit	  = 4,
		ToolLarge = 5,
		ObtainSizeFailed = 6,
	};
	class File : public Object
	{
		SkySnow_Object(File, Object);
	public:
		File();
		//½ûÖ¹ÒþÊ½×ª»»
		explicit File(const string& filePath);

		~File();
	public:
		Status ReadData(const string& filePath,Data* data);

	private:
		const string m_FilePath;
	};
}