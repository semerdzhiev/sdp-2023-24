#pragma once

class Node {
public:
    int value;  // Value stored in the node
    Node* next; // Pointer to next element or nullptr if this is the last node

    Node(int value = 0, Node* next = nullptr)
      : value(value), next(next)
    {
      // Nothing to do here
    }
};
