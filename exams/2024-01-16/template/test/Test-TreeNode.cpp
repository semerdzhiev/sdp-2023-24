#include "catch2/catch_all.hpp"
#include "TreeNode.h"

// A template test-case. It will run with all specified types.
// They will be available inside the test body as `TestType`. 
TEST_CASE("TreeNode::TreeNode() constructs a leaf node with a value of zero", "[tree]")
{
	TreeNode n;
	CHECK(n.value == 0);
	CHECK(n.left == nullptr);
	CHECK(n.right == nullptr);
	CHECK(n.isLeaf());
}

TEST_CASE("TreeNode::TreeNode(const T&) constructs a leaf node with the specified value", "[tree]")
{
	int expectedValue = 42;
	TreeNode n(expectedValue);

	CHECK(n.value == expectedValue);
	CHECK(n.left == nullptr);
	CHECK(n.right == nullptr);
	CHECK(n.isLeaf());
}

TEST_CASE("TreeNode::TreeNode(T, TreeNode*, TreeNode*) constructs a node with the specified value and successors", "[tree]")
{
	// Arrange
	const int someRandomValue = 123;
	TreeNode left, right;
	
	// Act
	TreeNode n(someRandomValue, &left, &right);

	// Assert
	CHECK(n.value == someRandomValue);
	CHECK(n.left == &left);
	CHECK(n.right == &right);
	CHECK_FALSE(n.isLeaf());
}

TEST_CASE("TreeNode::isLeaf() returns false for non-leaf nodes", "[tree]")
{
	TreeNode left, right;

	SECTION("Node with a single successor on the left") {
		CHECK_FALSE(TreeNode(42, &left, nullptr).isLeaf());
	}
	SECTION("Node with a single successor on the right") {
		CHECK_FALSE(TreeNode(42, nullptr, &right).isLeaf());
	}
	SECTION("Node with two successors") {
		CHECK_FALSE(TreeNode(42, &left, &right).isLeaf());
	}
}

TEST_CASE("TreeNode::hasLeftSuccessor() return true when a node has a left successor", "[tree]")
{
	TreeNode left;
	TreeNode node(42, &left, nullptr);

	SECTION("For nodes with only a left successor"){
		CHECK(node.hasLeftSuccessor());
	}
	SECTION("For nodes with both successors") {
		TreeNode right;
		node.right = &right;
		CHECK(node.hasLeftSuccessor());
	}
}

TEST_CASE("TreeNode::hasLeftSuccessor() return false when a node DOES NOT have a left successor", "[tree]")
{
	TreeNode node;

	SECTION("For leaf nodes") {
		CHECK_FALSE(node.hasLeftSuccessor());
	}
	SECTION("For nodes with only a right successor") {
		TreeNode right;
		node.right = &right;
		CHECK_FALSE(node.hasLeftSuccessor());
	}	
}

TEST_CASE("TreeNode::hasRightSuccessor() return true when a node has a right successor", "[tree]")
{
	TreeNode right;
	TreeNode node(42, nullptr, &right);

	SECTION("For nodes with only a right successor"){
		CHECK(node.hasRightSuccessor());
	}
	SECTION("For nodes with both successors") {
		TreeNode left;
		node.left = &left;
		CHECK(node.hasRightSuccessor());
	}
}

TEST_CASE("TreeNode::hasRightSuccessor() return false when a node DOES NOT have a right successor", "[tree]")
{
	TreeNode node;

	SECTION("For leaf nodes") {
		REQUIRE_FALSE(node.hasRightSuccessor());
	}
	SECTION("For nodes with only a left successor") {
		TreeNode left;
		node.left = &left;
		REQUIRE_FALSE(node.hasRightSuccessor());
	}	
}
