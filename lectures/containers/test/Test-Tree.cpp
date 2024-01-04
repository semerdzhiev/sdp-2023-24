#include "catch2/catch_all.hpp"
#include "containers/Tree.h"

using DebugBst = BinarySearchTree<int, DebugNodeAllocator<int>>;

TEST_CASE("BinarySearchTree::BinarySearchTree() constructs an empty tree", "[tree]")
{
    DebugBst bst;
    CHECK(bst.empty());
    CHECK(bst.size() == 0);
}

TEST_CASE("BinarySearchTree::clear() correctly releases all allocated memory and sets the state to empty")
{
    // Arrange
    const int size = 5;
    DebugBst bst;

    for(int i = 0; i < size; ++i)
        bst.insert(i);

    REQUIRE(bst.size() == size);
    REQUIRE_FALSE(bst.empty());

    // Act
    bst.clear();

    // Assert
    CHECK(bst.size() == 0);
    CHECK(bst.empty());
    CHECK(bst.allocator().activeAllocationsCount() == 0);    
}

TEST_CASE("BinarySearchTree::insert() increases the size of the tree when new elements are added", "[tree]")
{
    const int count = 5;
    DebugBst bst;

    for(int i = 1; i <= count; ++i) {
        bst.insert(i);
        CHECK(bst.size() == i);
    }
}

TEST_CASE("BinarySearchTree::insert() increases the size of the tree when duplicate elements are added", "[tree]")
{
    const int count = 5;
    DebugBst bst;

    for(int i = 1; i <= count; ++i) {
        bst.insert(i);
        bst.insert(i);
        CHECK(bst.size() == i*2);
    }
}

TEST_CASE("BinarySearchTree::insert() results in exactly one new allocation", "[tree]")
{
    const int count = 5;
    DebugBst bst;

    for(int i = 1; i <= count; ++i) {
        bst.insert(i);
        CHECK(bst.allocator().activeAllocationsCount() == i);
    }
}

class SampleBst {
public:
    
    std::vector<int> values{10, 20, 30, 40, 50};
    DebugBst bst;

    SampleBst()
    {
        for(size_t i = 0; i < values.size(); ++i)
            bst.insert(values[i]);
    }
};

TEST_CASE("BinarySearchTree::contains() correctly finds elements inserted in the tree with insert()", "[tree]")
{
    SampleBst sample;

    for(size_t i = 0; i < sample.values.size(); ++i)
        CHECK(sample.bst.contains(sample.values[i]));
}

TEST_CASE("BinarySearchTree::erase() correctly removes elements and releases memory", "[tree]")
{
    SampleBst sample;

    REQUIRE(sample.values.size() == sample.bst.allocator().activeAllocationsCount());
    REQUIRE(sample.values.size() == sample.bst.allocator().totalAllocationsCount());

    for(int i = (int)sample.values.size()-1; i >= 0; --i) {
        sample.bst.erase(sample.values[i]);
        CHECK(sample.bst.allocator().activeAllocationsCount() == i); // The number of allocated nodes decreases
        CHECK(sample.bst.allocator().totalAllocationsCount() == sample.values.size()); // No new allocations are made

        // All other elements are still in the tree
        for(int j = 0; j < i; ++j)
            CHECK(sample.bst.contains(sample.values[j]));
    }
}

TEST_CASE("BinarySearchTree::operator==() recognizes identical trees")
{
    SECTION("Two empty trees are equal") {
        CHECK(DebugBst() == DebugBst());
    }
    SECTION("Two non-empty trees having the same contents and structure are equal") {
        SampleBst sampleA, sampleB;
        CHECK(sampleA.bst == sampleB.bst);
    }
}

TEST_CASE("BinarySearchTree::operator==() recognizes different trees")
{
    SampleBst sample;

    SECTION("A non-empty tree is NOT equal to an empty one") {
        CHECK_FALSE(sample.bst == DebugBst());
    }
    SECTION("An empty tree is NOT equal to a non-empty one") {
        CHECK_FALSE(DebugBst() == sample.bst);
    }
    SECTION("Two non-empty trees having different contents are NOT equal") {
        SampleBst other;
        other.bst.erase(other.values[0]);
        CHECK_FALSE(sample.bst == other.bst);
    }
    SECTION("Two non-empty trees with identical contents but different structure are NOT equal") {
        DebugBst bst2;
        // Fill the values in reverse order
        for(int i = (int)sample.values.size()-1; i >= 0; --i)
            bst2.insert(sample.values[i]);
        CHECK_FALSE(sample.bst == bst2);
    }
}

TEST_CASE("BinarySearchTree::BinarySearchTree(const BinarySearchTree&) correctly copies a tree", "[tree]")
{
    SampleBst sample;
    DebugBst copy(sample.bst);

    CHECK(copy == sample.bst);    
    CHECK(copy.allocator().activeAllocationsCount() == sample.values.size());
    CHECK(copy.allocator().totalAllocationsCount() == sample.values.size());
}

TEST_CASE("BinarySearchTree::operator=(const BinarySearchTree&) correctly copies a tree", "[tree]")
{
    SampleBst sample;
    DebugBst copy;
    copy = sample.bst;

    CHECK(copy == sample.bst);    
    CHECK(copy.allocator().activeAllocationsCount() == sample.values.size());
    CHECK(copy.allocator().totalAllocationsCount() == sample.values.size());
}

TEST_CASE("BinarySearchTree::operator=(const BinarySearchTree&) does NOT leak memory when copying fails", "[tree]")
{
    SampleBst sample;
    DebugBst copy;
    size_t failAfter = sample.values.size() - 1; // Fail after copying all but the last element
    copy.allocator().failAfter(failAfter); 
    
    CHECK_THROWS_AS(copy = sample.bst, std::bad_alloc);
    CHECK(copy.allocator().activeAllocationsCount() == 0);
    CHECK(copy.allocator().totalAllocationsCount() == failAfter);
}

TEST_CASE("BinarySearchTree::Iterator can be used to iterate all values stored in a tree", "[tree]")
{
    SampleBst sample;
    auto vit = sample.values.begin();

    for(auto it = sample.bst.beginIterator(); it != sample.bst.endIterator(); ++it) {
        CHECK(*it == *vit);
        ++vit;
    }

    CHECK(vit == sample.values.end()); // Ensure there are no more values in the tree
}