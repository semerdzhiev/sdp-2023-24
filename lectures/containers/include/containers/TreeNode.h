#pragma once

template <typename T>
class TreeNode {
public:
    T data = T();
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode()
    {        
    }

    TreeNode(const T& data)
        : data(data)
    {        
    }

    TreeNode(const T& data, TreeNode* left, TreeNode* right)
        : data(data), left(left), right(right)
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

    ///
    /// Returns a reference to the successor pointer to which `value` belongs
    ///
    /// If `value` is less than the value stored in this node,
    /// then the function returns a reference to the `left` data member.
    /// Otherwise it returns a reference to `right`.
    ///
    TreeNode*& whichSuccessorWouldStore(const T& value)
    {
        return (value < data) ? left : right;
    }

    /// Set both successor pointers to null, effectively making this node a leaf
    void detachSuccessors()
    {
        left = nullptr;
        right = nullptr;
    }
};