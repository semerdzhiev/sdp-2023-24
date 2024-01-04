#include "catch2/catch_all.hpp"

#include "containers/HashTable.h"

using HashTypes = std::tuple<
	VectorOfUnorderedElements<int>,
	VectorWithBinarySearch<int>,
    SeparateChainingHash<int>
>;


TEMPLATE_LIST_TEST_CASE(
	"Hash::Hash() creates a hash of size 0",
	"[hash]",
	HashTypes)
{
    TestType empty;
	CHECK(empty.size() == 0);
}

TEMPLATE_LIST_TEST_CASE(
	"Hash::contains() returns correct values for a non-empty hash",
	"[hash]",
	HashTypes)
{
    // Arrange
    std::array<int, 8> sample{-20, -5, 10, 42, 108, 1000, 10000, 100000};
    
    std::array<int,5> notIncluded{
        std::numeric_limits<int>::min(),
        -1,
        0,
        1,
        std::numeric_limits<int>::max()
    };

    TestType hash;

    for(int value : sample)
        hash.insert(value);
    
    // Act, Assert
    for(int value : sample)
        CHECK(hash.contains(value));

    for(int value : notIncluded)
        CHECK_FALSE(hash.contains(value));
}

TEMPLATE_LIST_TEST_CASE(
	"Hash::size() returns correct values",
	"[hash]",
	HashTypes)
{
    int size = 10;
    
    TestType hash;
    CHECK(hash.size() == 0);

    for(int i = 1; i <= size; ++i) {
        hash.insert(i);
        CHECK(hash.size() == i);
    }
}