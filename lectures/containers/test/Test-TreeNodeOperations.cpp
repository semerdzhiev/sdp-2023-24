#include "catch2/catch_all.hpp"
#include "containers/TreeNodeOperations.h"
#include "SampleTree.h"

using TreeOperationTypes = std::tuple<
	IterativeNodeOperations<int>,
	RecursiveNodeOperations<int>
>;

using NodeType = TreeNode<int>;

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::sameTrees() returns true for two empty trees",
	"[tree]",
	TreeOperationTypes)
{
	CHECK(TestType::sameTrees(nullptr, nullptr));
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::sameTrees() returns false when comparing an empty and a non-empty tree",
	"[tree]",
	TreeOperationTypes)
{
	TreeNode<int> n;
	SECTION("Left is non-empty, right is empty") {
		CHECK_FALSE(TestType::sameTrees(&n, nullptr));
	}
	SECTION("Left is empty, right is non-empty") {
		CHECK_FALSE(TestType::sameTrees(nullptr, &n));
	}
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::sameTrees() returns true when comparing equivalent trees",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree t1, t2;
	CHECK(TestType::sameTrees(t1.rootptr, t2.rootptr));
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::sameTrees() returns false when comparing different trees",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree t1, t2;

	int value = t1.g.data - 1; // A value which is slightly less than that of G, so that it should be placed to its left
	TreeNode<int> x(value); // Create a new node to store the value
	t2.g.left = &x; // Attach the new node to the left of G

	CHECK_FALSE(TestType::sameTrees(t1.rootptr, t2.rootptr));
}

template <typename T>
inline bool areSameObject(const T& a, const T&b)
{
	return &a == &b;
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::findPointerTo() returns nullptr when searching in an empty tree",
	"[tree]",
	TreeOperationTypes)
{
	TreeNode<int>* rootptr = nullptr;
	CHECK( areSameObject(rootptr, TestType::findPointerTo(0, rootptr)) );
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::findPointerTo() returns the correct starting pointer when searching in a single-node tree",
	"[tree]",
	TreeOperationTypes)
{
	int someRandomValue = 42; // A random value
	TreeNode<int> node(someRandomValue);
	TreeNode<int>* rootptr = &node;

	CHECK( areSameObject(rootptr, TestType::findPointerTo(someRandomValue, rootptr)) );
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::findPointerTo() locates the pointer to a node with specific value in the tree.",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree t;

	CHECK( areSameObject(t.rootptr, TestType::findPointerTo(t.a.data, t.rootptr)));
	CHECK( areSameObject(t.a.left,  TestType::findPointerTo(t.b.data, t.rootptr)));
	CHECK( areSameObject(t.a.right, TestType::findPointerTo(t.c.data, t.rootptr)));
	CHECK( areSameObject(t.b.right, TestType::findPointerTo(t.d.data, t.rootptr)));
	CHECK( areSameObject(t.c.left,  TestType::findPointerTo(t.e.data, t.rootptr)));
	CHECK( areSameObject(t.c.right, TestType::findPointerTo(t.f.data, t.rootptr)));
	CHECK( areSameObject(t.f.left,  TestType::findPointerTo(t.g.data, t.rootptr)));
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::findPointerTo() returns the correct position where a node should be inserted when it is not present in the tree",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree t;

	// Values are being inserted around each node which has one or more missing successors.
	// The values being inserted are ±1 from the value stored in the respective node.
	// Thus they should be attached exactly under the said node, to the left or to the right.
	CHECK( areSameObject(t.b.left,  TestType::findPointerTo(t.b.data-1, t.rootptr)));
	CHECK( areSameObject(t.d.left,  TestType::findPointerTo(t.d.data-1, t.rootptr)));
	CHECK( areSameObject(t.d.right, TestType::findPointerTo(t.d.data+1, t.rootptr)));
	CHECK( areSameObject(t.e.left,  TestType::findPointerTo(t.e.data-1, t.rootptr)));
	CHECK( areSameObject(t.e.right, TestType::findPointerTo(t.e.data+1, t.rootptr)));
	CHECK( areSameObject(t.f.right, TestType::findPointerTo(t.f.data+1, t.rootptr)));
	CHECK( areSameObject(t.g.left,  TestType::findPointerTo(t.g.data-1, t.rootptr)));
	CHECK( areSameObject(t.g.right, TestType::findPointerTo(t.g.data+1, t.rootptr)));
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::insert() correctly inserts into an empty tree",
	"[tree]",
	TreeOperationTypes)
{
	TreeNode<int>* rootptr = nullptr;
	TreeNode<int> node;

	TestType::insert(rootptr, node);

	CHECK(rootptr == &node);
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::insert() correctly inserts into a non-empty tree",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree t;
	SampleTree expected;

	SECTION("Left neighbour of D") {
		TreeNode<int> node(t.d.data-1);
		expected.d.left = &node;

		TestType::insert(t.rootptr, node);

		CHECK(t.d.left == &node); // Check whether is is exactly the same node that is attached
		CHECK(TestType::sameTrees(t.rootptr, expected.rootptr)); // Check that the tree structure remains the same
	}
	SECTION("Right neighbour of F") {
		TreeNode<int> node(t.f.data+1);
		expected.f.right = &node;

		TestType::insert(t.rootptr, node);

		CHECK(t.f.right == &node); // Check whether is is exactly the same node that is attached
		CHECK(TestType::sameTrees(t.rootptr, expected.rootptr)); // Check that the tree structure remains the same
	}

	//TODO More sections are needed to cover the additional cases
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::findPointerToLargest() returns the root pointer for an empty tree",
	"[tree]",
	TreeOperationTypes)
{
	TreeNode<int>* rootptr = nullptr;
	CHECK( areSameObject(rootptr, TestType::findPointerToLargest(rootptr)) );
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::findPointerToLargest() returns the root pointer for a single-node tree",
	"[tree]",
	TreeOperationTypes)
{
	TreeNode<int> node;
	TreeNode<int>* rootptr = &node;
	CHECK( areSameObject(rootptr, TestType::findPointerToLargest(rootptr)) );
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::findPointerToLargest() correctly locates the largest element",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree t;
	CHECK( areSameObject(t.c.right, TestType::findPointerToLargest(t.rootptr)) );
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::extract() does nothing and returns nullptr for an empty tree",
	"[tree]",
	TreeOperationTypes)
{
	int someRandomValue = 0;
	TreeNode<int>* rootptr = nullptr;
	TreeNode<int>* result = TestType::extract(rootptr, someRandomValue);

	CHECK(rootptr == nullptr);
	CHECK(result == nullptr);
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::extract() results in an empty tree when removing the only element from a single-node tree",
	"[tree]",
	TreeOperationTypes)
{
	const int someRandomValue = 42;
	TreeNode<int> node(someRandomValue);
	TreeNode<int> *rootptr = &node;

	TreeNode<int>* extracted = TestType::extract(rootptr, someRandomValue);

	CHECK(extracted == &node);
	CHECK(rootptr == nullptr);
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::extract() does not alter the tree when the value is not present in it",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree t;
	SampleTree expected;

	TreeNode<int>* extracted = TestType::extract(t.rootptr, t.valueNotInTheTree);

	CHECK(extracted == nullptr);
	CHECK(TestType::sameTrees(expected.rootptr, t.rootptr));
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::extract() correctly extracts nodes and leaves the tree with the expected structure",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree t;
	SampleTree expected;

	SECTION("Removing the root") {
		expected.rootptr = &expected.d;
		expected.d.left = &expected.b;
		expected.d.right = &expected.c;
		expected.b.right = nullptr;

		TreeNode<int>* extracted = TestType::extract(t.rootptr, t.a.data);
		
		REQUIRE(areSameObject(*extracted, t.a)); // The correct node is extracted
		CHECK(extracted->left == nullptr);     // The left pointer of the extracted node has been set to null
		CHECK(extracted->right == nullptr);    // The right pointer of the extracted node has been set to null
		CHECK(areSameObject(*t.rootptr, t.d)); // The correct node has been promoted to root
		CHECK(areSameObject(*t.d.left,  t.b)); // The left pointer of the promoted node is correct
		CHECK(areSameObject(*t.d.right, t.c)); // The right pointer of the promoted node is correct
		CHECK(TestType::sameTrees(expected.rootptr, t.rootptr)); // The structure of the tree is as expected
	}
	SECTION("Removing a leaf") {
		expected.f.left = nullptr;

		TreeNode<int>* extracted = TestType::extract(t.rootptr, t.g.data);
		
		REQUIRE(areSameObject(*extracted, t.g)); // The correct node is extracted
		CHECK(extracted->left == nullptr);     // The left pointer of the extracted node has been set to null
		CHECK(extracted->right == nullptr);    // The right pointer of the extracted node has been set to null
		CHECK(areSameObject(*t.rootptr, t.a)); // The root remains the same
		CHECK(t.f.left == nullptr); // The old parent of the extracted node has its successor pointer set to null
		CHECK(TestType::sameTrees(expected.rootptr, t.rootptr)); // The structure of the tree is as expected
	}
	SECTION("Removing a node in the middle") {
		expected.a.right = &expected.e;
		expected.e.right = &expected.f;
		
		TreeNode<int>* extracted = TestType::extract(t.rootptr, t.c.data);
		
		REQUIRE(areSameObject(*extracted, t.c)); // The correct node is extracted
		CHECK(extracted->left == nullptr);     // The left pointer of the extracted node has been set to null
		CHECK(extracted->right == nullptr);    // The right pointer of the extracted node has been set to null
		CHECK(areSameObject(*t.rootptr, t.a)); // The root remains the same
		CHECK(areSameObject(*t.a.right, t.e)); // check that the correct node is promoted in the place of the extracted one
		CHECK(t.e.left == nullptr);            // The left pointer of the promoted element is correct
		CHECK(areSameObject(*t.e.right, t.f)); // The right pointer of the promoted element is correct
		CHECK(TestType::sameTrees(expected.rootptr, t.rootptr)); // The structure of the tree is as expected
	}

	//TODO More sections are needed to cover additional cases
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::release() does not throw on nullptr",
	"[tree]",
	TreeOperationTypes)
{
	DebugAllocator<TreeNode<int>> allocator;
	TreeNode<int>* rootptr = nullptr;

	CHECK_NOTHROW(TestType::release(rootptr, allocator));
	CHECK(allocator.activeAllocationsCount() == 0);
	CHECK(allocator.totalAllocationsCount() == 0);
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::release() correctly releases memory",
	"[tree]",
	TreeOperationTypes)
{
	DebugAllocator<TreeNode<int>> allocator;
	
	//
	// Builds a tree of the following type:
	//
	//      *
	//     / \
	//    *   *
	//   /     \
	//  *       *
	//
	TreeNode<int>* rootptr = allocator.buy();
	rootptr->left = allocator.buy();
	rootptr->right = allocator.buy();
	rootptr->left->left = allocator.buy();
	rootptr->right->right = allocator.buy();

	size_t totalElements = 5;

	CHECK(allocator.activeAllocationsCount() == totalElements);
	CHECK(allocator.totalAllocationsCount() == totalElements);

	TestType::release(rootptr, allocator);

	CHECK(allocator.activeAllocationsCount() == 0); // All nodes have been released
	CHECK(allocator.totalAllocationsCount() == totalElements); // No new allocations were made
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::clone() returns nullptr for an empty tree and no allocations are made",
	"[tree]",
	TreeOperationTypes)
{
	DebugAllocator<TreeNode<int>> allocator;
	TreeNode<int>* rootptr = TestType::clone(nullptr, allocator);

	CHECK(rootptr == nullptr);
	CHECK(allocator.activeAllocationsCount() == 0);
	CHECK(allocator.totalAllocationsCount() == 0);
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::clone() correctly clones a tree and makes only the necessary number of allocations",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree tree;
	DebugAllocator<TreeNode<int>> allocator;
	TreeNode<int>* cloned = TestType::clone(tree.rootptr, allocator);

	CHECK(TestType::sameTrees(cloned, tree.rootptr));
	CHECK(allocator.activeAllocationsCount() == tree.values.size());
	CHECK(allocator.totalAllocationsCount() == tree.values.size());
}

TEMPLATE_LIST_TEST_CASE(
	"TreeOperation::clone() does not leak memory when copying fails",
	"[tree]",
	TreeOperationTypes)
{
	SampleTree tree;
	size_t failAfter = tree.values.size() - 1; // Fail after copying all but the last element
	DebugAllocator<TreeNode<int>> allocator(failAfter); 
	TreeNode<int>* cloned = nullptr;

	CHECK_THROWS_AS(cloned = TestType::clone(tree.rootptr, allocator), std::bad_alloc);
	CHECK(allocator.activeAllocationsCount() == 0);
	CHECK(allocator.totalAllocationsCount() == failAfter);
}