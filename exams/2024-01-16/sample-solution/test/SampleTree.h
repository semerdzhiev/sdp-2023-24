#pragma once

#include "TreeNode.h"

//
// Sample BST tree (1)
//
//      A:7
//     /   \
//    /     \
//   B:3    C:9
//  /  \    /
// D:1 E:4 F:8
//  \
//  G:2
//
class SampleBst1
{
public:
	TreeNode* g = new TreeNode(2);
	TreeNode* f = new TreeNode(8);
	TreeNode* e = new TreeNode(4);
	TreeNode* d = new TreeNode(1, nullptr, g);
	TreeNode* c = new TreeNode(9, f, nullptr);
	TreeNode* b = new TreeNode(3, d, e);
	TreeNode* a = new TreeNode(7, b, c);
	
	TreeNode*& root = a;
	std::set<int> elements{1,2,3,4,7,8,9};

	~SampleBst1()
	{
		Utils::release(root);
	}
};

//
// Sample BST tree (2)
//
//      A:4
//     /   \
//    /     \
//   B:2    C:8
//  /  \    /  \
// D:1 E:3 F:7 G:9
//  
class SampleBst2
{
public:
	TreeNode g = TreeNode(9);
	TreeNode f = TreeNode(7);
	TreeNode e = TreeNode(3);
	TreeNode d = TreeNode(1);
	TreeNode c = TreeNode(8, &f, &g);
	TreeNode b = TreeNode(2, &d, &e);
	TreeNode a = TreeNode(4, &b, &c);
	
	TreeNode* root = &a;
	std::set<int> elements{1,2,3,4,7,8,9};
};

//
// Sample BST tree (3)
//
//      A:4
//     /   \
//    /     \
//   B:1    C:8
//  /       /
// D:0     E:7
//
//  
class SampleBst3
{
public:
	TreeNode e = TreeNode(7);
    TreeNode d = TreeNode(0);
	TreeNode c = TreeNode(8, &e, nullptr);
	TreeNode b = TreeNode(1, &d, nullptr);
	TreeNode a = TreeNode(4, &b, &c);
	
	TreeNode* root = &a;
	std::set<int> elements{0, 1, 4, 7, 8};
};

//
// Sample non-BST tree (1)
//
//      A:7
//     /   \
//    /     \
//   B:3    C:9
//  /  \    /
// D:1 E:9 F:8
//  \
//  G:2
//
class NonBst1
{
public:
	TreeNode g = TreeNode(2);
	TreeNode f = TreeNode(8);
	TreeNode e = TreeNode(9);
	TreeNode d = TreeNode(1, nullptr, &g);
	TreeNode c = TreeNode(9, &f, nullptr);
	TreeNode b = TreeNode(3, &d, &e);
	TreeNode a = TreeNode(7, &b, &c);
	
	TreeNode* root = &a;
	std::vector<int> elements{1,2,3,7,8,9,9};
};

//
// Sample non-BST tree (2)
//
//      A:7
//     /   \
//    /     \
//   B:3    C:9
//  /      /  \
// D:1   E:2  F:10
//
class NonBst2
{
public:
	TreeNode f = TreeNode(10);
	TreeNode e = TreeNode(2);
	TreeNode d = TreeNode(1);
	TreeNode c = TreeNode(9, &e, &f);
	TreeNode b = TreeNode(3, &d, nullptr);
	TreeNode a = TreeNode(7, &b, &c);
	
	TreeNode* root = &a;
	std::vector<int> elements{1,2,3,7,9,10};
};


//
// Sample non-BST tree (3)
//
//      A:7
//     /   \
//    /     \
//   B:7    C:9
//
class NonBst3
{
public:
	TreeNode c = TreeNode(9);
	TreeNode b = TreeNode(7);
	TreeNode a = TreeNode(7, &b, &c);
	
	TreeNode* root = &a;
	std::vector<int> elements{7,7,9};
};

//
// Sample non-BST tree (3)
//
//      A:7
//     /   \
//    /     \
//   B:3    C:7
//
class NonBst4
{
public:
	TreeNode c = TreeNode(7);
	TreeNode b = TreeNode(3);
	TreeNode a = TreeNode(7, &b, &c);
	
	TreeNode* root = &a;
	std::vector<int> elements{3,7,7};
};
