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
#include <unordered_map>
#include <vector>
#include "LogAssert.h"
using namespace std;
namespace SkySnow
{
	struct SNode
	{
		SNode(int v = -1,SNode* n = nullptr)
			: value(v)
			, next(n)
		{
		}
		int value;
		SNode* next;
	};
	//Two Num Sum
	class DSA
	{
	public:
		DSA() {}

		~DSA() {}

		void TestTwoNumSum()
		{
			vector<int> testNum = { 2,3,5,7,11 };
			vector<int> result = TwoNumSum(testNum, 9);
			if (result.size() != 0)
			{
				SN_LOG("Array Sum Num ID FirstID:%d TwoID:%d", result[0], result[1]);
			}
		}

		void TestBigNumSum()
		{
			vector<int> right = {1,2,3,4};
			vector<int> left = { 4,3,2,1};
			SNode* sn = BuildList(right);
			PrintNodeList(sn);
			SNode* rn = BuildList(left);
			PrintNodeList(rn);
			SNode* resn = BigNumSum(sn,rn);
			PrintNodeList(resn);
		}
	private:
		vector<int> TwoNumSum(const vector<int>& num, int target)
		{
			unordered_map<int, int> map_f;
			for (int i = 0; i < num.size(); i++)
			{
				if (map_f.find(target - num[i]) != map_f.end())
				{
					return { map_f[target - num[i]], i };
				}
				map_f[num[i]] = i;
			}
			return {};
		}

		void PrintNodeList(SNode* root)
		{
			SNode* temp = root;
			while (temp)
			{
				SN_LOG(" %d",temp->value);
				temp = temp->next;
			}
		}

		SNode* BuildList(const vector<int>& nums)
		{
			SNode* head = new SNode(nums[0]);
			SNode* root = head;
			for (int i = 1; i < nums.size(); i ++)
			{
				SNode* temp = new SNode(nums[i]);
				head->next = temp;
				head = temp;
			}
			return root;
		}
		SNode* BigNumSum(SNode* left, SNode* right)
		{
			SNode* head = new SNode();
			int carry = 0;
			SNode* curr = head;
			while (left != nullptr || right != nullptr)
			{
				int lv = left != nullptr ? left->value : 0;
				int rv = right != nullptr ? right->value : 0;

				int sum = lv + rv + carry;
				carry = sum / 10;
				sum = sum % 10;

				SNode* temp = new SNode(sum);
				curr->next = temp;
				curr = temp;

				left = left ? left->next : nullptr;
				right = right ? right->next : nullptr;
			}
			if (carry == 1)
			{
				curr->next = new SNode(carry);
			}
			return head->next;
		}

	};
}
