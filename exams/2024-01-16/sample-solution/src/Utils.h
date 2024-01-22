#pragma once

#include "TreeNode.h"

#include <algorithm>
#include <iterator>
#include <set>
#include <stack>

class Utils {
public:

  ///
  /// Releases the memory allocated for the tree with the given root
  ///
  static void release(TreeNode* root)
  {
    if(root) {
      release(root->left);
      release(root->right);
      delete root;
    }
  }

  ///
  /// Returns the number of nodes in the tree with the given root
  ///
  static int size(TreeNode* root)
  {
    return (root == nullptr) ? 0 : 1 + size(root->left) + size(root->right);
  }

  ///
  /// Checks if the tree with the given root is a BST
  ///  
  static bool isWeightBalanced(TreeNode* root)
  {
    if( ! root)
      return true;

    return
      std::abs(size(root->left) - size(root->right)) <= 1 &&
      isWeightBalanced(root->left) &&
      isWeightBalanced(root->right);
  }

  ///
  /// Returns the set of values in the tree with the given root
  ///
  static std::set<int> toSet(TreeNode* root)
  {
    std::set<int> result;

    if(root)
    {
      std::stack<TreeNode*> nodes;
      nodes.push(root);

      while( ! nodes.empty()) {
        TreeNode* node = nodes.top();
        nodes.pop();
        result.insert(node->value);

        if(node->left)
          nodes.push(node->left);
        if(node->right)
          nodes.push(node->right);

      }
    }
    
    return result;
  }

  ///
  /// Calculates the set difference between two sets of integers
  ///
  static std::set<int> setDifference(const std::set<int>& a, const std::set<int>& b)
  {
    std::set<int> result;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
  }
};
