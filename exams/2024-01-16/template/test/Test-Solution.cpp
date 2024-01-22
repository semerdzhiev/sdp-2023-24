#include "catch2/catch_all.hpp"
#include "Solution.h"
#include "SampleTree.h"
#include "Utils.h"

TEMPLATE_TEST_CASE("isBst() correctly detects BST trees", "[solution]", SampleBst1, SampleBst2, SampleBst3)
{
  TestType fx;
  CHECK(isBst(fx.root));
}

TEMPLATE_TEST_CASE("isBst() returns false for non-BST trees", "[solution]", NonBst1, NonBst2, NonBst3, NonBst4)
{
  TestType fx;
  CHECK_FALSE(isBst(fx.root));
}

TEST_CASE("toBalancedTree() returns nullptr for an empty vector", "[solution]")
{
    std::vector<int> empty;
    CHECK(toBalancedTree(empty) == nullptr);
}

TEST_CASE("toBalancedTree() correctly constructs a balanced BST")
{
    std::vector<int> sample{1, 2, 3, 4, 5, 6, 7};

    TreeNode* result = toBalancedTree(sample);

    CHECK(Utils::isWeightBalanced(result)); // The new tree is weight balanced
    CHECK(isBst(result)); // The new tree is a BST
    CHECK(Utils::toSet(result) == std::set<int>(sample.begin(), sample.end())); // The new tree contains the necessary elements

    Utils::release(result);
}

TEST_CASE("remove() returns nullptr for the empty tree", "[solution]")
{
    TreeNode* result = remove(nullptr, 0);
    CHECK(result == nullptr);
}

TEST_CASE("remove() returns the same tree when removing a non-existing element", "[solution]")
{
    SampleBst1 bst;
    int nonExistingElement = *bst.elements.begin() - 1;

    bst.root = remove(bst.root, nonExistingElement);

    CHECK(isBst(bst.root));
    CHECK(Utils::toSet(bst.root) == bst.elements);
}

TEST_CASE("remove() correctly removes the root node", "[solution]")
{
    SampleBst1 bst;
    int valueToRemove = bst.root->value;

    bst.root = remove(bst.root, valueToRemove);
    bst.elements.erase(valueToRemove);

    CHECK(isBst(bst.root));
    CHECK(Utils::toSet(bst.root) == bst.elements);
}

TEST_CASE("remove() correctly removes a leaf node", "[solution]")
{
    SampleBst1 bst;
    int valueToRemove = bst.g->value;

    bst.root = remove(bst.root, valueToRemove);
    bst.elements.erase(valueToRemove);

    CHECK(isBst(bst.root));
    CHECK(Utils::toSet(bst.root) == bst.elements);
}

TEST_CASE("remove() correctly removes a node with one child", "[solution]")
{
    SampleBst1 bst;
    int valueToRemove = bst.d->value;

    bst.root = remove(bst.root, valueToRemove);
    bst.elements.erase(valueToRemove);

    CHECK(isBst(bst.root));
    CHECK(Utils::toSet(bst.root) == bst.elements);
}

TEST_CASE("remove() correctly removes a node with two children", "[solution]")
{
    SampleBst1 bst;
    int valueToRemove = bst.b->value;

    bst.root = remove(bst.root, valueToRemove);
    bst.elements.erase(valueToRemove);

    CHECK(isBst(bst.root));
    CHECK(Utils::toSet(bst.root) == bst.elements);
}

TEST_CASE("removeAll() returns an empty vector when subtracting the empty tree from another empty tree", "[solution]")
{
    CHECK(removeAll(nullptr, nullptr) == std::vector<int>());
}

TEST_CASE("removeAll() returns nullptr when subtracting two trees with the same elements", "[solution]")
{
    SampleBst1 bst1;
    SampleBst2 bst2;
    CHECK(removeAll(bst1.root, bst2.root) == std::vector<int>());
}

TEST_CASE("removeAll() returns nullptr when subtracting a non-empty tree from the empty tree", "[solution]")
{
    SampleBst1 bst;
    CHECK(removeAll(nullptr, bst.root) == std::vector<int>());
}

TEST_CASE("removeAll() returns the same elements when subtracting the empty tree from a non-empty tree", "[solution]")
{
    SampleBst1 bst;
    std::vector<int> expected(bst.elements.begin(), bst.elements.end());
    CHECK(removeAll(bst.root, nullptr) == expected);
}

TEST_CASE("removeAll() correctly subtracts two non-empty trees", "[solution]")
{
    SampleBst1 bst1;
    SampleBst3 bst3;
    
    SECTION("Sample BST1 / Sample BST2")
    {
        std::set<int> difference = Utils::setDifference(bst1.elements, bst3.elements);
        std::vector<int> expected(difference.begin(), difference.end());
        CHECK(removeAll(bst1.root, bst3.root) == expected);
    }
    SECTION("Sample BST3 / Sample BST1")
    {
        std::set<int> difference = Utils::setDifference(bst3.elements, bst1.elements);
        std::vector<int> expected(difference.begin(), difference.end());
        CHECK(removeAll(bst3.root, bst1.root) == expected);
    }
}
