#include "catch2/catch_all.hpp"

#include "containers/ListNode.h"
#include "utils/MockingObjects.h"

TEST_CASE("ListNode::ListNode() constructs a node with no successor and a default-constructed value", "[list]")
{
	ListNode<ConstructorSpy> empty;

	CHECK(empty.next == nullptr);
	CHECK(empty.value.constructedBy == ConstructorSpy::ConstructorType::Default);
}

TEST_CASE("ListNode::ListNode(v) correctly initializes an object", "[list]")
{
	int value = 42;

	ListNode<int> n(value);

	CHECK(n.value == value);
	CHECK(n.next == nullptr);
}

TEST_CASE("ListNode::ListNode(v, n) correctly initializes an object", "[list]")
{
	int value = 42;
	ListNode<int> tail;

	ListNode<int> n(value, &tail);

	CHECK(n.value == value);
	CHECK(n.next == &tail);
}

TEST_CASE("ListNode::hasNext() returns false for nodes that have no successors", "[list]")
{
	ListNode<int> n;
	CHECK_FALSE(n.hasNext());
}

TEST_CASE("Node::hasNext() returns true for nodes that have successors", "[list]")
{
	ListNode<int> tail;
	ListNode<int> n(42, &tail);
	CHECK(n.hasNext());
}
