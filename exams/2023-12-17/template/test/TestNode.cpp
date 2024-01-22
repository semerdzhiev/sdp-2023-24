#include "catch2/catch_all.hpp"
#include "Node.h"

TEST_CASE("Default constructed node has value of 0 and no successor", "[Node]")
{
	Node empty;
	CHECK(empty.value == 0);
	CHECK(empty.next == nullptr);
}

TEST_CASE("Node constructed with specific arguments correctly retains those values", "[Node]")
{
	int value = 42;
	Node tail;

	Node sample(value, &tail);

	CHECK(sample.value == value);
	CHECK(sample.next == &tail);
}
