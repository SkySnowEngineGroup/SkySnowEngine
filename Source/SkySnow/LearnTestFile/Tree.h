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
#include <cstring>
#include <iostream>
#include <memory>
#include "LogAssert.h"
namespace SkySnowLearning
{
#define Equal(a,b) (_stricmp((a),(b)) == 0)
	struct TreeNode
	{
		int m_Data;
		struct TreeNode* m_Left;
		struct TreeNode* m_Right;
	};
	class BinaryTree
	{
	public:
		BinaryTree()
			: m_Root(nullptr)
		{
		}

		~BinaryTree()
		{

		}
		
		void BuildTree()
		{
			//char preStr[] = "1,2,#,3";
			//SN_LOG("Binary Build Tree Init:%s \n", preStr);
			//PreTypeCreateTree(m_Root,preStr);

			//std::string str = "1,2,3,#";
			//SN_LOG("orgin: %s\n", str.c_str());
			//int index = 0, lastIndex = 0;
			//while (true) {
			//	auto iter = std::find_if(str.begin() + index, str.end(), [](char c)->bool {
			//		return c == ',';
			//		}
			//	);
			//	if (iter != str.end()) {
			//		int _index = index;
			//		index = std::distance(str.begin(), iter) + 1;
			//		std::string sub = str.substr(index);
			//		std::string lastSub = str.substr(lastIndex, index - 1);
			//		lastIndex = _index;
			//		SN_LOG("Binary Build Tree current:%s ,sub:%s index:%d\n", lastSub.c_str(), sub.c_str(), index);
			//	}
			//	else {
			//		break;
			//	}
			//}

			
		}
	private:

		void PreTypeCreateTree(TreeNode* root,char* nodeStr)
		{
			char* delim = ",";
			char* token = std::strtok(nodeStr, delim);
			char* endflag = "#";
			SN_LOG("PreTypeCreateTree nodeStr:%s token:%s\n", nodeStr ,token);
			if (Equal(token, endflag))
			{
				root = nullptr;
				SN_LOG("Learning endflag \n");
			}
			else
			{
				root = new TreeNode();
				root->m_Data = (int)token;
				token = std::strtok(NULL, nodeStr);
				SN_LOG("Create Left Node:%s\n",token);
				PreTypeCreateTree(root->m_Left, token);
				token = std::strtok(NULL, nodeStr);
				SN_LOG("Create Right Node:%s\n", token);
				PreTypeCreateTree(root->m_Right, token);
			}
		}

	private:
		TreeNode* m_Root;
	};
}
