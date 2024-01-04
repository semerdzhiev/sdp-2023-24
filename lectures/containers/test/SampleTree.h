#pragma once
#include "containers/TreeNode.h"
#include <array>

//
// Sample tree
//
// The values are picked in such way, as to have a difference of at least 2
// between a node and all other nodes in its left or right subtrees.
// This is used by tests that need to generate values to insert in the tree
// at appropriate positions.
//
//    A:50
//   /   \
//  /     \
// B:-3    C:70
//  \     / \
//  D:30 /   \
//      E:60 F:90
//           /
//         G:80
//
class SampleTree
{
public:
	using value_type = int;

	TreeNode<int> g = TreeNode<int>(80);
	TreeNode<int> e = TreeNode<int>(60);
	TreeNode<int> d = TreeNode<int>(30);
	TreeNode<int> f = TreeNode<int>(90, &g, nullptr);
	TreeNode<int> c = TreeNode<int>(70, &e, &f);
	TreeNode<int> b = TreeNode<int>(-3, nullptr, &d);
	TreeNode<int> a = TreeNode<int>(50, &b, &c);
	
	TreeNode<int>& root = a;
	TreeNode<int>* rootptr = &a;

	const int valueNotInTheTree = 1'000'000;

	std::array<int,7> values{-3, 30, 50, 60, 70, 80, 90};
};