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
#include "File.h"
namespace SkySnow
{
	File::File()
	{

	}

	File::File(const string& filePath)
	{

	}

	File::~File()
	{

	}

	Status File::ReadData(const string& filePath, Data* data)
	{
		if (filePath.empty())
			return Status::NotExists;
		FILE* fp = fopen(filePath.c_str(),"rb");

		if (!fp)
			return Status::OpenFailed;
#if defined(_MSC_VER_)
		auto descriptor = _fileno(fp);
#else
		auto descriptor = fileno(fp);
#endif // defined(_MSC_VER_)
		struct stat statBuf;
		if (fstat(descriptor, &statBuf) == -1) {
			fclose(fp);
			return Status::ReadFailed;
		}
		size_t size = statBuf.st_size;
		unsigned char* bytes = (unsigned char*)malloc(sizeof(unsigned char) * (size));
		size_t readsize = fread(bytes,1,size,fp);
		fclose(fp);
		if (readsize < size)
		{
			return Status::ReadFailed;
		}
		data->SetBytes(bytes,size);
		return Status::Ok;
	}
}