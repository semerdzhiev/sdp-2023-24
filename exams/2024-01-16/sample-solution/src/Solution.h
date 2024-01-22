#include "TreeNode.h"
#include "Utils.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>


inline bool isBst(const TreeNode* root, int min, int max)
{
  if (root == nullptr)
    return true;

  if (root->value < min || root->value > max)
    return false;

  return
    isBst(root->left, min, root->value - 1) &&
    isBst(root->right, root->value + 1, max);
}

inline bool isBst(const TreeNode* root) {
  return isBst(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

//----------------------------------------------------------------------

inline TreeNode* toBalancedTree(const std::vector<int>& data, size_t begin, size_t end)
{
  if(begin >= end)
    return nullptr;

  size_t mid = begin + (end - begin - 1) / 2;

  TreeNode* node = new TreeNode(data[mid]);

  try {
    node->left = toBalancedTree(data, begin, mid);
    node->right = toBalancedTree(data, mid+1, end);
  }
  catch(...) {
    Utils::release(node->left);
    delete node;
    throw;
  }

  return node;
}

inline TreeNode* toBalancedTree(const std::vector<int>& data)
{
  return toBalancedTree(data, 0, data.size());
}

//----------------------------------------------------------------------

inline TreeNode* leftmost(TreeNode* node)
{
  while (node && node->left)
    node = node->left;

  return node;
}

inline TreeNode* remove(TreeNode* root, int value)
{
  TreeNode** ppNode = &root;
  
  // Locate the parent of the parent to remove
  while(*ppNode) {
    if(value < (*ppNode)->value)
      ppNode = &(*ppNode)->left;
    else if((*ppNode)->value < value)
      ppNode = &(*ppNode)->right;
    else
      break;
  }

  // If the node is not found, return the original tree
  if(*ppNode == nullptr)
    return root;

  // If the node has one child, replace it with the child
  if ((*ppNode)->left == nullptr) {
    TreeNode* temp = *ppNode;
    *ppNode = (*ppNode)->right;
    delete temp;
  }
  else if ((*ppNode)->right == nullptr) {
    TreeNode* temp = *ppNode;
    *ppNode = (*ppNode)->left;
    delete temp;
  }
  // If the node has two children, replace it with the leftmost node of the right subtree
  else {
    TreeNode* candidate = leftmost((*ppNode)->right);
    (*ppNode)->value = candidate->value;
    (*ppNode)->right = remove((*ppNode)->right, candidate->value);
  }

  return root;
}

//----------------------------------------------------------------------

class Iterator {
private:
    std::stack<const TreeNode*> backtrack;

private:
  void pushAllTheWayToTheLeft(const TreeNode* startFrom)
  {
    for(; startFrom; startFrom = startFrom->left)
      backtrack.push(startFrom);
  }

public:
  Iterator(const TreeNode* startFrom)
  {
    pushAllTheWayToTheLeft(startFrom);
  }
    
  bool endReached() const
  {
    return backtrack.empty();
  }

  int current() const
  {
    assert( ! endReached() );
    return backtrack.top()->value;
  }

  void moveOn()
  {
    assert( ! endReached() );
    const TreeNode* p = backtrack.top();
    backtrack.pop();
    pushAllTheWayToTheLeft(p->right);
  }
};

inline std::vector<int> removeAll(const TreeNode* from, const TreeNode* what)
{
  Iterator itFrom(from), itWhat(what);

  std::vector<int> result;

  while( ! itFrom.endReached() && ! itWhat.endReached()) {
    if(itFrom.current() < itWhat.current()) {
      result.push_back(itFrom.current());
      itFrom.moveOn();
    }
    else if(itFrom.current() > itWhat.current()) {
      itWhat.moveOn();
    }
    else {
      itFrom.moveOn();
      itWhat.moveOn();
    }
  }

  while( ! itFrom.endReached()) {
    result.push_back(itFrom.current());
    itFrom.moveOn();
  }

  return result;
}
