#pragma once
class TreeNode {
public:
    int value = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode() = default;

    TreeNode(int value)
        : value(value)
    {        
    }

    TreeNode(int value, TreeNode* left, TreeNode* right)
        : value(value), left(left), right(right)
    {
    }

    bool isLeaf() const noexcept
    {
        return left == nullptr && right == nullptr;
    }

    bool hasLeftSuccessor() const noexcept
    {
        return left != nullptr;
    }

    bool hasRightSuccessor() const noexcept
    {
        return right != nullptr;
    }
};