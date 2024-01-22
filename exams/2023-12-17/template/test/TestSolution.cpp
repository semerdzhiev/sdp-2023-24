#include "catch2/catch_all.hpp"
#include "Solution.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <set>

// IMPORTANT: Do not modify this file.
// If you need to add your own unit tests,
// place them in `TestAdditional.cpp`.

size_t listLength(const Node* lst)
{
    size_t result = 0;

    while(lst) {
        lst = lst->next;
        ++result;
    }

    return result;
}

std::set<Node*> nodePointers(Node* lst)
{
    std::set<Node*> result;

    while(lst) {
        result.insert(lst);
        lst = lst->next;
    }

    return result;
}

bool isSorted(Node* lst)
{
    while(lst && lst->next) {
        if(lst->value > lst->next->value)
            return false;

        lst = lst->next;
    }

    return true;
}

class SampleList {
public:
    // Construct the list 2 -> 5 -> 1 -> 4 -> 7 -> 3
    Node last   = Node(3);
    Node fifth  = Node(7, &last);
    Node fourth = Node(4, &fifth);
    Node third  = Node(1, &fourth);
    Node second = Node(5, &third);
    Node first  = Node(2, &second);

    std::set<Node*> originalNodes = nodePointers(&first);
};

TEST_CASE("releaseList(nullptr) does not throw", "[solution]")
{
    REQUIRE_NOTHROW(releaseList(nullptr));
}

TEST_CASE("releaseList() does not throw for non-empty lists", "[solution]")
{
    // Arrange
    Node* tail   = new Node(3);
    Node* middle = new Node(2, tail);
    Node* head  = new Node(1, middle);

    // Act, Assert
    REQUIRE_NOTHROW(releaseList(head));
}

TEST_CASE("generateRandomList(0) returns nullptr", "[solution]")
{
    CHECK(generateRandomList(0) == nullptr);
}

TEST_CASE("generateRandomList(N) generates a random list with length of exactly N", "[solution]")
{
    size_t desiredLength = 5;

    Node* lst = generateRandomList(desiredLength);
    
    CHECK(listLength(lst) == desiredLength);

    CHECK_NOTHROW(releaseList(lst));
}

TEST_CASE("removeConsecutiveDuplicates(nullptr) does not throw", "[solution]")
{
    CHECK_NOTHROW(removeConsecutiveDuplicates(nullptr));
}

TEST_CASE("removeConsecutiveDuplicates() removes consecutive duplicates and does not alter the rest of the elements", "[solution]")
{
    // Construct the list 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 3 -> 1 -> 2 -> 1 -> 1
    Node* tail = new Node(1);
    Node* l9   = new Node(1, tail);
    Node* l8   = new Node(2, l9);
    Node* l7   = new Node(1, l8);
    Node* l6   = new Node(3, l7);
    Node* l5   = new Node(2, l6);
    Node* l4   = new Node(2, l5);
    Node* l3   = new Node(2, l4);
    Node* l2   = new Node(2, l3);
    Node* l1   = new Node(1, l2);
    Node* head = new Node(1, l1);

    std::set<Node*> nodesExpectedToRemain;
    nodesExpectedToRemain.insert(l6);
    nodesExpectedToRemain.insert(l7);
    nodesExpectedToRemain.insert(l8);

    int expectedSequence[] = {3, 1, 2};

    CHECK_NOTHROW(head = removeConsecutiveDuplicates(head));

    CHECK(nodesExpectedToRemain == nodePointers(head));

    releaseList(head);
}

class TwoSortedLists {
public:
    // Create the list 1 -> 1-> 2 -> 5 -> 10
    Node a5 = Node(10);
    Node a4 = Node(5, &a5);
    Node a3 = Node(2, &a4);
    Node a2 = Node(1, &a3);
    Node a1 = Node(1, &a2);

    // Create the list -1 -> 1 -> 5
    Node b3 = Node(5);
    Node b2 = Node(1, &b3);
    Node b1 = Node(-1, &b2);

    std::set<Node*> originalNodesOfBothLists;

    TwoSortedLists()
    {
        originalNodesOfBothLists.insert(&a1);
        originalNodesOfBothLists.insert(&a2);
        originalNodesOfBothLists.insert(&a3);
        originalNodesOfBothLists.insert(&a4);
        originalNodesOfBothLists.insert(&a5);

        originalNodesOfBothLists.insert(&b1);
        originalNodesOfBothLists.insert(&b2);
        originalNodesOfBothLists.insert(&b3);
    }
};

TEST_CASE("mergeLists(nullptr, nullptr) returns nullptr", "[solution]")
{
    CHECK(mergeLists(nullptr, nullptr) == nullptr);
}

TEST_CASE_METHOD(TwoSortedLists, "mergeLists(lst, nullptr) results in lst", "[solution]")
{
    Node* headOfSortedList = &a1;
    Node* headOfMergedLists = mergeLists(&a1, nullptr);
    std::set<Node*> originalNodes = nodePointers(&a1);

    SECTION("The head of the list remains the same") {
        CHECK(headOfSortedList == headOfMergedLists);
    }
    SECTION("The list remains sorted") {
        CHECK(isSorted(headOfMergedLists));
    }
    SECTION("The nodes in the list remain the same") {
        CHECK(originalNodes == nodePointers(headOfMergedLists));
    } 
}

TEST_CASE_METHOD(TwoSortedLists, "mergeLists(nullptr, lst) results in lst", "[solution]")
{
    Node* headOfSortedList = &a1;
    Node* headOfMergedLists = mergeLists(nullptr, &a1);
    std::set<Node*> originalNodes = nodePointers(&a1);

    SECTION("The head of the list remains the same") {
        CHECK(headOfSortedList == headOfMergedLists);
    }
    SECTION("The list remains sorted") {
        CHECK(isSorted(headOfMergedLists));
    }
    SECTION("The nodes in the list remain the same") {
        CHECK(originalNodes == nodePointers(headOfMergedLists));
    } 
}

TEST_CASE_METHOD(TwoSortedLists, "mergeLists(a,b) returns a sorted list", "[solution]")
{
    Node* result = mergeLists(&a1, &b1);

    CHECK(isSorted(result));
}

TEST_CASE_METHOD(TwoSortedLists, "mergeLists() keeps all original nodes from the original lists", "[solution]")
{
    Node* result = mergeLists(&a1, &b1);

    CHECK(originalNodesOfBothLists == nodePointers(result));
}
