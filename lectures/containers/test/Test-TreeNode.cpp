#include "catch2/catch_all.hpp"
#include "containers/TreeNode.h"
#include "utils/MockingObjects.h"

// A template test-case. It will run with all specified types.
// They will be available inside the test body as `TestType`. 
TEST_CASE("TreeNode::TreeNode() constructs a leaf node with a default constructed data member", "[tree]")
{
	TreeNode<ConstructorSpy> n;

	CHECK(n.data.constructedBy == ConstructorSpy::ConstructorType::Default);
	CHECK(n.left == nullptr);
	CHECK(n.right == nullptr);
	CHECK(n.isLeaf());
}

TEST_CASE("TreeNode::TreeNode(const T&) constructs a leaf node with the specified value", "[tree]")
{
	int expectedValue = 42;
	TreeNode<int> n(expectedValue);

	CHECK(n.data == expectedValue);
	CHECK(n.left == nullptr);
	CHECK(n.right == nullptr);
	CHECK(n.isLeaf());
}

TEST_CASE("TreeNode::TreeNode(T, TreeNode*, TreeNode*) constructs a node with the specified value and successors", "[tree]")
{
	// Arrange
	const int someRandomValue = 123;
	TreeNode<int> left, right;
	
	// Act
	TreeNode<int> n(someRandomValue, &left, &right);

	// Assert
	CHECK(n.data == someRandomValue);
	CHECK(n.left == &left);
	CHECK(n.right == &right);
	CHECK_FALSE(n.isLeaf());
}

TEST_CASE("TreeNode::isLeaf() returns true for leaf nodes", "[tree]")
{
	TreeNode<int> n;
	CHECK(n.isLeaf());
}

TEST_CASE("TreeNode::isLeaf() returns false for non-leaf nodes", "[tree]")
{
	TreeNode<int> left, right;

	SECTION("Node with a single successor on the left") {
		CHECK_FALSE(TreeNode<int>(42, &left, nullptr).isLeaf());
	}
	SECTION("Node with a single successor on the right") {
		CHECK_FALSE(TreeNode<int>(42, nullptr, &right).isLeaf());
	}
	SECTION("Node with two successors") {
		CHECK_FALSE(TreeNode<int>(42, &left, &right).isLeaf());
	}
}

TEST_CASE("TreeNode::hasLeftSuccessor() return true when a node has a left successor", "[tree]")
{
	TreeNode<int> left;
	TreeNode<int> node(42, &left, nullptr);

	SECTION("For nodes with only a left successor"){
		CHECK(node.hasLeftSuccessor());
	}
	SECTION("For nodes with both successors") {
		TreeNode<int> right;
		node.right = &right;
		CHECK(node.hasLeftSuccessor());
	}
}

TEST_CASE("TreeNode::hasLeftSuccessor() return false when a node DOES NOT have a left successor", "[tree]")
{
	TreeNode<int> node;

	SECTION("For leaf nodes") {
		CHECK_FALSE(node.hasLeftSuccessor());
	}
	SECTION("For nodes with only a right successor") {
		TreeNode<int> right;
		node.right = &right;
		CHECK_FALSE(node.hasLeftSuccessor());
	}	
}

TEST_CASE("TreeNode::hasRightSuccessor() return true when a node has a right successor", "[tree]")
{
	TreeNode<int> right;
	TreeNode<int> node(42, nullptr, &right);

	SECTION("For nodes with only a right successor"){
		CHECK(node.hasRightSuccessor());
	}
	SECTION("For nodes with both successors") {
		TreeNode<int> left;
		node.left = &left;
		CHECK(node.hasRightSuccessor());
	}
}

TEST_CASE("TreeNode::hasRightSuccessor() return false when a node DOES NOT have a right successor", "[tree]")
{
	TreeNode<int> node;

	SECTION("For leaf nodes") {
		REQUIRE_FALSE(node.hasRightSuccessor());
	}
	SECTION("For nodes with only a left successor") {
		TreeNode<int> left;
		node.left = &left;
		REQUIRE_FALSE(node.hasRightSuccessor());
	}	
}

TEST_CASE("TreeNode::whichSuccessorWouldStore() returns the correct successor", "[tree]")
{
	int rootValue = 5;

	TreeNode<int> left(rootValue - 10);
	TreeNode<int> right(rootValue + 10);
	TreeNode<int> root(rootValue, &left, &right);

	CHECK(root.whichSuccessorWouldStore(rootValue - 1) == &left);
	CHECK(root.whichSuccessorWouldStore(rootValue) == &right);
	CHECK(root.whichSuccessorWouldStore(rootValue + 1) == &right);
}

TEST_CASE("TreeNode::detachSuccessors() sets both successor pointers to null", "[tree]")
{
	TreeNode<int> left;
	TreeNode<int> right;
	TreeNode<int> node(42, &left, &right);

	node.detachSuccessors();

	CHECK(node.left == nullptr);
	CHECK(node.right == nullptr);
}