#include "Node.h"

#include <cstdlib>
#include <stdexcept>

inline void releaseList(Node* lst)
{
    while(lst) {
        Node* temp = lst;
        lst = lst->next;
        delete temp;
    }
}

inline Node* generateRandomList(size_t length)
{
    Node* result = nullptr;

    try {
        for(size_t i = 0; i < length; ++i) {
            Node* newNode = new Node();
            newNode->next = result;
            newNode->value = std::rand() % 100;
            result = newNode;
        }
    }
    catch(std::bad_alloc&) {
        releaseList(result);
        throw;
    }

    return result;
}

inline Node* append(Node* head, Node*& tail, Node* toAdd)
{
    if (!head){
        tail = toAdd;
        return tail;
    } else {
        tail->next = toAdd;
        tail = tail->next;
        return head;
    }
}

inline Node* removeConsecutiveDuplicates(Node* lst)
{
    Node *result = nullptr, *tail;

    while (lst){
        if (lst->next && lst->value == lst->next->value){
            while(lst->next && lst->value == lst->next->value){
                Node* toDel = lst;
                lst = toDel->next;
                delete toDel;
            }
            Node* toDel = lst;
            lst = toDel->next;
            delete toDel;
        }
        else {
            result = append(result, tail, lst);
            lst = lst->next;
        }
    }

    if(result) {
        tail->next = nullptr;
    }
    return result;
}

inline Node* mergeLists(Node* lst1, Node* lst2)
{
    // Temporary node, will be discarded later
    // The resultant list will be built after the sentinel
    Node sentinel;

    Node* current = &sentinel;

    // Iterate the two lists and while they are not empty,
    // append nodes to the result in the correct order.
    while(lst1 && lst2) {
        if(lst1->value < lst2->value) {
            current->next = lst1;
            lst1 = lst1->next;
        }
        else {
            current->next = lst2;
            lst2 = lst2->next;
        }

        current = current->next;
    }

    // Append a non-empty list to the end-result
    // (there is at most one such list at this point)
    if(lst1) {
        current->next = lst1;
    }
    else if(lst2) {
        current->next = lst2;
    }

    // Return the result accumulated after the sentinel element
    return sentinel.next;
}
