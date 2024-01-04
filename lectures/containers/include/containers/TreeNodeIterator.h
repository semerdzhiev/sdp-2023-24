#pragma once

#include "containers/TreeNode.h"

#include <cassert>
#include <stack>
#include <vector>

template <typename T>
class TreeNodeIterator {
public:
    using node_type = TreeNode<T>;

private:
    std::stack<node_type*> backtrack;

private:
    void pushAllTheWayToTheLeft(node_type* startFrom)
    {
        for(; startFrom; startFrom = startFrom->left)
            backtrack.push(startFrom);
    }

public:
    static TreeNodeIterator endIterator()
    {
        return TreeNodeIterator(nullptr);
    }

public:
    TreeNodeIterator(node_type* startFrom)
    {
        pushAllTheWayToTheLeft(startFrom);
    }
    
    bool atEnd() const
    {
        return backtrack.empty();
    }

    node_type& operator*()
    {
        assert( ! atEnd() );
        return *backtrack.top();
    }

    node_type* operator->()
    {
        assert( ! atEnd() );
        return backtrack.top();
    }
    
    void operator++()
    {
        assert( ! atEnd() );
        node_type* p = backtrack.top();
        backtrack.pop();
        pushAllTheWayToTheLeft(p->right);
    }

    bool operator==(const TreeNodeIterator& other) const
    {
        if(atEnd() || other.atEnd())
            return atEnd() == other.atEnd();

        return backtrack.top() == other.backtrack.top();
    }

    bool operator!=(const TreeNodeIterator& other) const
    {
        return ! operator==(other);
    }
};
