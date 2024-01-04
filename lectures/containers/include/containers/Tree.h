#pragma once

#include "utils/Allocator.h"
#include "containers/TreeNodeIterator.h"
#include "containers/TreeNodeOperations.h"

template <typename T>
using SimpleNodeAllocator = SimpleAllocator<TreeNode<T>>;

template <typename T>
using DebugNodeAllocator = DebugAllocator<TreeNode<T>>;

template <
    typename ElementType,
    typename AllocatorType = SimpleNodeAllocator<ElementType>,
    typename NodeOperations = RecursiveNodeOperations<ElementType>
    >
class BinarySearchTree {
public:
    using node_type = TreeNode<ElementType>;
    using value_type = ElementType;
    using allocator_type = AllocatorType;

private:
    node_type* m_rootptr = nullptr;
    size_t m_size = 0;
    allocator_type m_allocator;

public:
    class Iterator {
        TreeNodeIterator<value_type> it;

    public:
        Iterator(node_type* startFrom)
            : it(startFrom)
        {            
        }

        value_type& operator*()
        {
            return it->data;
        }

        value_type* operator->()
        {
            return &it->data;
        }

        void operator++()
        {
            ++it;
        }

        bool operator==(const Iterator& other)
        {
            return it == other.it;
        }

        bool operator!=(const Iterator& other)
        {
            return it != other.it;
        }
    };

public:
    BinarySearchTree() = default;

    ~BinarySearchTree()
    {
        clear();
    }

    BinarySearchTree(const BinarySearchTree& other)
    {
        m_rootptr = NodeOperations::clone(other.m_rootptr, m_allocator);
        m_size = other.m_size;
    }

    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
        if(this != &other) {
            clear();
            m_rootptr = NodeOperations::clone(other.m_rootptr, m_allocator);
            m_size = other.m_size;
        }
        return *this;
    }

    void clear()
    {
        NodeOperations::release(m_rootptr, m_allocator);
        m_rootptr = nullptr;
        m_size = 0;
    }

    size_t size() const noexcept
    {
        return m_size;
    }

    bool empty() const noexcept
    {
        return m_size == 0;
    }

    allocator_type& allocator()
    {
        return m_allocator;
    }

    const allocator_type& allocator() const
    {
        return m_allocator;
    }

    bool contains(const value_type& value)
    {
        return NodeOperations::findPointerTo(value, m_rootptr) != nullptr;
    }

    void insert(const value_type& value)
    {
        node_type* ptr = m_allocator.buy();
        ptr->data = value;

        NodeOperations::insert(m_rootptr, *ptr);
        ++m_size;
    }

    void erase(const value_type& value)
    {
        node_type* extracted = NodeOperations::extract(m_rootptr, value);
        
        if(extracted != nullptr) {
            --m_size;
            m_allocator.release(extracted);
        }
    }

    bool operator==(const BinarySearchTree& other) const
    {
        return NodeOperations::sameTrees(this->m_rootptr, other.m_rootptr);
    }

    Iterator beginIterator()
    {
        return Iterator(m_rootptr);
    }

    Iterator endIterator()
    {
        return Iterator(nullptr);
    }
};