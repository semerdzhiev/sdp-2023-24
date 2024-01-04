#include "catch2/catch_all.hpp"
#include "containers/TreeNodeIterator.h"
#include "SampleTree.h"


TEST_CASE("TreeNodeIterator::NodeIterator(nullptr) creates an iterator that has reached the end", "[tree]")
{
    TreeNodeIterator<int> it(nullptr);
    CHECK(it.atEnd());
}

TEST_CASE("TreeNodeIterator walks the tree in the correct order and returns correct values", "[tree]")
{
    SampleTree tree;
    TreeNodeIterator<SampleTree::value_type> it(tree.rootptr);
    TreeNodeIterator<SampleTree::value_type> end = TreeNodeIterator<SampleTree::value_type>::endIterator();

    int i = 0;

    // Values are retrieved in the correct order
    for(; it != end; ++it,++i) {
        CHECK(it->data == tree.values[i]);
        CHECK((*it).data == tree.values[i]);
        CHECK_FALSE(it.atEnd());
    }

    CHECK(i == tree.values.size()); // All elements have been visited
}

template <typename IteratorType>
void checkIteratorsCompareTheSame(const IteratorType& a, const IteratorType& b) {
    CHECK(a == b);
    CHECK(b == a);
    CHECK_FALSE(a != b);
    CHECK_FALSE(b != a);
}

template <typename IteratorType>
void checkIteratorsCompareDifferent(const IteratorType& a, const IteratorType& b) {
    bool check = a == b; 
    CHECK_FALSE(a == b);
    CHECK_FALSE(b == a);
    CHECK(a != b);
    CHECK(b != a);
}


TEST_CASE("TreeNodeIterator end iterators are equal", "[tree]")
{
    TreeNodeIterator<SampleTree::value_type> end1 = TreeNodeIterator<SampleTree::value_type>::endIterator();
    TreeNodeIterator<SampleTree::value_type> end2 = TreeNodeIterator<SampleTree::value_type>::endIterator();
    checkIteratorsCompareTheSame(end1, end2);
}

TEST_CASE("TreeNodeIterator objects pointing at the same node are equal", "[tree]")
{
    SampleTree tree;
    TreeNodeIterator<SampleTree::value_type> it1(tree.rootptr);
    TreeNodeIterator<SampleTree::value_type> it2(tree.rootptr);
    TreeNodeIterator<SampleTree::value_type> end = TreeNodeIterator<SampleTree::value_type>::endIterator();

    for(; it1 != end; ++it1,++it2)
        checkIteratorsCompareTheSame(it1, it2);

    checkIteratorsCompareTheSame(it1, it2);
    checkIteratorsCompareTheSame(it1, end);
}

TEST_CASE("TreeNodeIterator objects pointing at different nodes are NOT equal", "[tree]")
{
    SampleTree tree;
    TreeNodeIterator<SampleTree::value_type> end = TreeNodeIterator<SampleTree::value_type>::endIterator();

    SECTION("An end iterator and an iterator to a node") {
        TreeNodeIterator<SampleTree::value_type> end = TreeNodeIterator<SampleTree::value_type>::endIterator();
        TreeNodeIterator<SampleTree::value_type> it(tree.rootptr);
        checkIteratorsCompareDifferent(it, end);
    }
    SECTION("Two iterators pointing at different nodes") {
        TreeNodeIterator<SampleTree::value_type> it1(&tree.b);
        TreeNodeIterator<SampleTree::value_type> it2(&tree.d);
        checkIteratorsCompareDifferent(it1, it2);
    }
}