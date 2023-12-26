#include "catch2/catch_all.hpp"
#include "IntegerSet.h"

#include <limits>
#include <stdexcept>

//------------------------------------------------------------------------------
// Sample sets fixture

class SampleSets {
protected:
  IntegerSet sample1;
  IntegerSet sample2;
public:
  SampleSets()
  {
    std::istringstream i1("5 10 20 30 40 50");
    sample1.deserialize(i1);

    std::istringstream i2("9 5 10 15 25 35 40 45 50 55");
    sample2.deserialize(i2);
  }

  IntegerSet expectedUnion()
  {
	std::istringstream input("11 5 10 15 20 25 30 35 40 45 50 55");
	IntegerSet result;
	result.deserialize(input);
	return result;
  }

  IntegerSet expectedIntersection()
  {
	std::istringstream input("3 10 40 50");
	IntegerSet result;
	result.deserialize(input);
	return result;
  }
};

//------------------------------------------------------------------------------
// Constructors, destructor, operator=

TEST_CASE("IntegerSet::IntegerSet() constructs a set of size 0")
{
  CHECK(IntegerSet().size() == 0);
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::IntegerSet(const IntegerSet&) creates a copy equal to the original in terms of equals()")
{
  IntegerSet copy(sample1);
  CHECK(copy.equals(sample1));
  CHECK(sample1.equals(copy));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::operator=(const IntegerSet&) creates a copy equal to the original in terms of equals()")
{
  IntegerSet copy;
  copy = sample1;
  CHECK(copy.equals(sample1));
  CHECK(sample1.equals(copy));
}

//------------------------------------------------------------------------------
// Serialization/deserialization

TEST_CASE("IntegerSet::deserialize() and serialize() successfully read and write the empty set")
{
	std::istringstream input("0");
	std::ostringstream output;
	IntegerSet set;
	set.deserialize(input);
	CHECK(set.size() == 0);
	set.serialize(output);
	CHECK(output.str() == "0");
}

TEST_CASE("IntegerSet::deserialize() does not alter the rest of the contents of the stream for an empty set")
{
	std::istringstream input("0 -1 hello");
	IntegerSet set;
	set.deserialize(input);

	int n;
	std::string s;
	input >> n >> s;
	CHECK(n == -1);
	CHECK(s == "hello");
}

TEST_CASE("IntegerSet::deserialize() and serialize() successfully read and write a non-empty set")
{
	std::string representation = "3 10 20 30";
	std::istringstream input(representation);
	std::ostringstream output;
	IntegerSet set;
	set.deserialize(input);
	CHECK(set.size() == 3);
	set.serialize(output);
	CHECK(output.str() == representation);
}

TEST_CASE("IntegerSet::deserialize() does not alter the rest of the contents of the stream for a non-empty set")
{
	std::istringstream input("3 10 20 30 -1 hello");
	IntegerSet set;
	set.deserialize(input);

	int n;
	std::string s;
	input >> n >> s;
	CHECK(n == -1);
	CHECK(s == "hello");
}

TEST_CASE("IntegerSet::deserialize() throws when the sequence of elements is not ascending strictly")
{
	std::istringstream input("3 10 30 20");
	IntegerSet set;

	CHECK_THROWS_AS(set.deserialize(input), std::runtime_error);
}

TEST_CASE("IntegerSet::deserialize() throws when the sequence of elements contains the same number twice")
{
	std::istringstream input("4 10 20 20 30");
	IntegerSet set;

	CHECK_THROWS_AS(set.deserialize(input), std::runtime_error);
}

TEST_CASE("IntegerSet::deserialize() throws when there are less numbers in the sequence than the specified number of elements")
{
	std::istringstream input("3 10 20");
	IntegerSet set;
	CHECK_THROWS_AS(set.deserialize(input), std::runtime_error);
}

TEST_CASE("IntegerSet::deserialize() throws when there is a non-integer in the sequence")
{
	std::istringstream input("3 10 abc 20");
	IntegerSet set;
	CHECK_THROWS_AS(set.deserialize(input), std::runtime_error);
}

//------------------------------------------------------------------------------
// Equality

TEST_CASE("IntegerSet::equals() Two empty sets are equal")
{
	CHECK(IntegerSet().equals(IntegerSet()));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::equals() The empty set is NOT equal to a non-empty set")
{
	SECTION("The empty set is the first argument") {
		CHECK_FALSE(IntegerSet().equals(sample1));
	}
	SECTION("The empty set is the second argument") {
		CHECK_FALSE(sample1.equals(IntegerSet()));
	}
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::equals() Two different sets are NOT equal")
{
	CHECK_FALSE(sample1.equals(sample2));
	CHECK_FALSE(sample2.equals(sample1));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::equals() Two sets comprising of the same elements are equal")
{
	IntegerSet copy = sample1;
	CHECK(copy.equals(sample1));
	CHECK(sample1.equals(copy));
}

//------------------------------------------------------------------------------
// contains

TEST_CASE("IntegerSet::contains() The empty set does not contain nothing")
{
	CHECK_FALSE(IntegerSet().contains(0));
	CHECK_FALSE(IntegerSet().contains(-1));
	CHECK_FALSE(IntegerSet().contains(1));
	CHECK_FALSE(IntegerSet().contains(std::numeric_limits<int>::min()));
	CHECK_FALSE(IntegerSet().contains(std::numeric_limits<int>::max()));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::contains() returns true for all elements contained in the set")
{
	CHECK(sample1.contains(10));
	CHECK(sample1.contains(20));
	CHECK(sample1.contains(30));
	CHECK(sample1.contains(40));
	CHECK(sample1.contains(50));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::contains() returns false for elements not in the set")
{
	CHECK_FALSE(sample1.contains(0));
	CHECK_FALSE(sample1.contains(35));
	CHECK_FALSE(IntegerSet().contains(std::numeric_limits<int>::min()));
	CHECK_FALSE(IntegerSet().contains(std::numeric_limits<int>::max()));
}

//------------------------------------------------------------------------------
// Subset

TEST_CASE("IntegerSet::subsetOf() The empty set is a subset of itself")
{
	CHECK(IntegerSet().subsetOf(IntegerSet()));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::subsetOf() The empty set is a subset of  every non-empty set")
{
	CHECK(IntegerSet().subsetOf(sample1));
	CHECK(IntegerSet().subsetOf(sample2));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::subsetOf() A non-empty set is NOT a subset of the empty set")
{
	CHECK_FALSE(sample1.subsetOf(IntegerSet()));
	CHECK_FALSE(sample2.subsetOf(IntegerSet()));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::subsetOf() Every set is a subset of itself")
{
	CHECK(sample1.subsetOf(sample1));
	CHECK(sample2.subsetOf(sample2));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::subsetOf() Evert set is a subset of itself")
{
	CHECK(sample1.subsetOf(sample1));
	CHECK(sample2.subsetOf(sample2));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::subsetOf() recognizes proper subsets")
{
	CHECK(expectedIntersection().subsetOf(sample1));
	CHECK(expectedIntersection().subsetOf(sample2));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::subsetOf() returns false when a set is not a subset of another")
{
	CHECK_FALSE(sample2.subsetOf(sample1));
}

//------------------------------------------------------------------------------
// Union

TEST_CASE_METHOD(SampleSets, "IntegerSet::getUnion() The empty set acts as a neutral element")
{
  IntegerSet empty;

  SECTION("When two empty sets are united") {
    CHECK(empty.getUnion(empty).equals(empty));
  }
  SECTION("When the empty set is the first argument") {
    CHECK(empty.getUnion(sample1).equals(sample1));
  }
  SECTION("When two empty set is the second argument") {
    CHECK(sample1.getUnion(empty).equals(sample1));
  }
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::getUnion() When a set is united with itself, the result is the same set")
{
	CHECK(sample1.getUnion(sample1).equals(sample1));
	CHECK(sample2.getUnion(sample2).equals(sample2));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::getUnion() A union of two sets is computed correctly")
{
	CHECK(sample1.getUnion(sample2).equals(expectedUnion()));
	CHECK(sample2.getUnion(sample1).equals(expectedUnion()));
}

//------------------------------------------------------------------------------
// Intersection

TEST_CASE_METHOD(SampleSets, "IntegerSet::getIntersection() The empty set acts as an absorbing element")
{
  IntegerSet empty;

  SECTION("When two empty sets are united") {
    CHECK(empty.getIntersection(empty).equals(empty));
  }
  SECTION("When the empty set is the first argument") {
    CHECK(empty.getIntersection(sample1).equals(empty));
  }
  SECTION("When two empty set is the second argument") {
    CHECK(sample1.getIntersection(empty).equals(empty));
  }
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::getIntersection() When a set is intersected with itself, the result is the same set")
{
	CHECK(sample1.getIntersection(sample1).equals(sample1));
	CHECK(sample2.getIntersection(sample2).equals(sample2));
}

TEST_CASE_METHOD(SampleSets, "IntegerSet::getIntersection() An intersection of two sets is computed correctly")
{
	CHECK(sample1.getIntersection(sample2).equals(expectedIntersection()));
	CHECK(sample2.getIntersection(sample1).equals(expectedIntersection()));
}
