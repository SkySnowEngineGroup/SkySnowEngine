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
#include <vector>
#include "LogAssert.h"
using namespace std;
namespace SkySnowLearning
{
	static void QuickSort(int numsArr[],int left,int right)
	{
		if (left >= right)
		{
			return;
		}

		int i = left;
		int j = right;
		int piove = numsArr[i];
		while (i < j)
		{
			while (i < j && numsArr[j] >= piove)
			{
				j--;
			}
			if (i < j)
			{
				numsArr[i] = numsArr[j];
			}
			while (i < j && numsArr[i] <= piove)
			{
				i++;
			}
			if (i < j)
			{
				numsArr[j] = numsArr[i];
			}
			if (i >= j)
			{
				numsArr[i] = piove;
			}
		}
		QuickSort(numsArr,left,j - 1);
		QuickSort(numsArr, j + 1, right);
	}

	static void TestQS()
	{
		int count = 5;
		int array[] = {3,4,2,5,7};
		QuickSort(array,0,4);
		for (int i = 0; i < count;i ++)
		{
			SN_LOG(" %d",array[i]);
		}
	}
}
