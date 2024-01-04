#pragma once

template <typename ElementType>
class ListNode {
public:
    ListNode* next = nullptr;
    ElementType value = ElementType();

    ListNode() = default;

    ListNode(ElementType value, ListNode* next = nullptr)
        : value(value), next(next)
    {
        // Nothing to do here        
    }

    bool hasNext()
    {
        return next != nullptr;
    }
};