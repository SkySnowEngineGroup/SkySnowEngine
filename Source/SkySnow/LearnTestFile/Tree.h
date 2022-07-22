//
// Copyright(c) 2020 - 2022 the SkySnowEngine project.
// Open source is written by sunguoqiang(SunGQ1987),wangcan(crygl),
//							 liuqian(SkySnow),zhangshuangxue(Calence)
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
#include <vector>
#include <list>
#include "LogAssert.h"
using namespace std;
namespace SkySnowLearning
{
	struct TreeNode
	{
		TreeNode()
			: m_Data(0)
			, m_Left(nullptr)
			, m_Right(nullptr)
		{
		}
		TreeNode(int val)
			: m_Data(val)
			, m_Left(nullptr)
			, m_Right(nullptr)
		{
		}
		TreeNode(int val,TreeNode* left,TreeNode* right)
			: m_Data(val)
			, m_Left(left)
			, m_Right(right)
		{
		}
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

		void VisitTree()
		{
			vector<int> vec = { 1,2,3,NULL,NULL,4,5 };
			TreeNode* root = PreTypeCreateTree(vec, 0);
			SN_LOG("Binary Pre Visit Tree: Root Left Right.");
			PreOrder(root);
			SN_LOG("Binary Mid Visit Tree: Left Root Right.");
			MidOrder(root);
			SN_LOG("Binary Pos Visit Tree: Left Right Root.");
			PosOrder(root);
			SN_LOG("Binary Level Visit Tree: ");
			LevelOrder(root);
		}

		void TwoTreeEqual()
		{
			vector<int> vec1 = { 1,2,3,NULL,NULL,4,5 };
			TreeNode* tree_1 = PreTypeCreateTree(vec1, 0);

			vector<int> vec2 = { 1,2,3,6,NULL,4,5};
			TreeNode* tree_2 = PreTypeCreateTree(vec2, 0);
			
			bool equal_1 = isEqual(tree_1, tree_1);
			bool equal_2 =isEqual(tree_1, tree_2);
			SN_LOG("First Equal is:%d Seconed:%d",equal_1, equal_2);
		}

		void ReverTree()
		{
			vector<int> vec1 = { 1,2,3,NULL,NULL,4,5 };
			TreeNode* tree_1 = PreTypeCreateTree(vec1, 0);
			ReverTreeNode(tree_1);

			PreOrder(tree_1);
			LevelOrder(tree_1);
		}

	private:
		TreeNode* ReverTreeNode(TreeNode* root)
		{
			if (root == nullptr)
				return nullptr;
			ReverTreeNode(root->m_Left);
			ReverTreeNode(root->m_Right);

			TreeNode* temp = root->m_Left;
			root->m_Left = root->m_Right;
			root->m_Right = temp;
			return root;
		}
		bool isEqual(TreeNode* lhs, TreeNode* rhs)
		{
			if (lhs == nullptr && rhs == nullptr)
				return true;
			if ((lhs == nullptr && rhs != nullptr) || (lhs != nullptr && rhs == nullptr))
				return false;
			if (lhs->m_Data != rhs->m_Data)
				return false;
			return isEqual(lhs->m_Left, rhs->m_Left) && isEqual(lhs->m_Right, rhs->m_Right);
		}
		int GetBinaryTreeDepth(TreeNode* root)
		{
			if (root == nullptr)
				return 0;
			int lDepth = GetBinaryTreeDepth(root->m_Left);
			int rDepth = GetBinaryTreeDepth(root->m_Right);

			return (lDepth > rDepth ? lDepth : rDepth) + 1;
		}
		void PreOrder(TreeNode* root)
		{
			if (root == nullptr)
			{
				SN_LOG("NULL");
				return;
			}
				
			SN_LOG("%d", root->m_Data);
			PreOrder(root->m_Left);
			PreOrder(root->m_Right);
		}
		void MidOrder(TreeNode* root)
		{
			if (root == nullptr)
			{
				SN_LOG("NULL");
				return;
			}
			MidOrder(root->m_Left);
			SN_LOG("%d",root->m_Data);
			MidOrder(root->m_Right);
		}
		void PosOrder(TreeNode* root)
		{
			if (root == nullptr)
			{
				SN_LOG("NULL");
				return;
			}
			PosOrder(root->m_Left);
			PosOrder(root->m_Right);
			SN_LOG("%d", root->m_Data);
		}
		void LevelOrder(TreeNode* root)
		{
			//使用队列
			list<TreeNode*> t;
			vector<int> levelNode;
			vector<vector<int>> result;
			if (root != nullptr)
			{
				t.push_back(root);
			}
			while (t.size() > 0)
			{
				levelNode.clear();
				int levelNodeCount = t.size();
				for (int i = 0;i < levelNodeCount;i ++)
				{
					TreeNode* cur = t.front();
					t.pop_front();
					levelNode.push_back(cur ? cur->m_Data : NULL);
					if (cur == nullptr)
					{
						continue;
					}
					t.push_back(cur->m_Left? cur->m_Left : nullptr);
					t.push_back(cur->m_Right? cur->m_Right : nullptr);
				}
				result.push_back(levelNode);

				bool isAllNull = true;
				list<TreeNode*>::iterator iter;
				for (iter = t.begin(); iter != t.end();iter++)
				{
					if (*iter != nullptr)
					{
						isAllNull = false;
					}
				}
				if (isAllNull) break;
			}
			//打印二叉树层次遍历
			for (int i = 0; i < result.size(); i ++)
			{
				levelNode = result[i];
				for (int j = 0; j < levelNode.size(); j ++)
				{
					if (levelNode[j] == NULL)
					{
						printf("NULL ");
					}
					else
					{
						printf("%d ", levelNode[j]);
					}
					
				}
				printf("\n");
			}
		}

		TreeNode* PreTypeCreateTree(const vector<int>& vec,int index)
		{
			TreeNode* root = nullptr;
			//SN_LOG("PreType Build Tree out index:%d\n", index);
			if (index < vec.size() && vec[index] != NULL)
			{
				root = new TreeNode(vec[index]);
				//SN_LOG("PreType Build Tree left 2 * index + 1:%d\n", 2 * index + 1);
				root->m_Left = PreTypeCreateTree(vec, 2 * index + 1);
				//SN_LOG("PreType Build Tree right 2 * index + 1:%d\n", 2 * index + 2);
				root->m_Right = PreTypeCreateTree(vec, 2 * index + 2);
			}
			return root;
		}

	private:
		TreeNode* m_Root;
	};
}
