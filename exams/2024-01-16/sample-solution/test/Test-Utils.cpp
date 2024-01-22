#include "catch2/catch_all.hpp"
#include "Utils.h"
#include "SampleTree.h"

TEST_CASE("Utils::size() returns 0 for the empty tree", "[utils]")
{
  CHECK(Utils::size(nullptr) == 0);
}

TEMPLATE_TEST_CASE(
  "Utils::size() correctly calculates the number of elements in a non-empty tree",
  "[utils]",
  SampleBst1, SampleBst2, SampleBst3, NonBst1, NonBst2, NonBst3, NonBst4)
{
  TestType fx;
  CHECK(Utils::size(fx.root) == fx.elements.size());
}

TEMPLATE_TEST_CASE(
  "Utils::isWeightBalanced() recognizes weight balanced trees",
  "[utils]",
  SampleBst2, SampleBst3, NonBst2, NonBst3, NonBst4)
{
  TestType fx;
  CHECK(Utils::isWeightBalanced(fx.root));
}

TEMPLATE_TEST_CASE(
  "Utils::isWeightBalanced() recognizes non-weight balanced trees",
  "[utils]",
  SampleBst1, NonBst1)
{
  TestType fx;
  CHECK_FALSE(Utils::isWeightBalanced(fx.root));
}

TEST_CASE("Utils::toSet() returns an empty set for the empty tree", "[utils]")
{
  CHECK(Utils::toSet(nullptr) == std::set<int>());
}

TEMPLATE_TEST_CASE(
  "Utils::toSet() returns the correct set of elements",
  "[utils]",
  SampleBst1, SampleBst2, SampleBst3)
{
  TestType fx;
  CHECK(Utils::toSet(fx.root) == fx.elements);
}

TEST_CASE("Utils::setDifference() returns an empty set for empty sets", "[utils]")
{
  CHECK(Utils::setDifference(std::set<int>(), std::set<int>()) == std::set<int>());
}

TEST_CASE("Utils::setDifference() returns the correct set difference", "[utils]")
{
  std::set<int> a{1,2,3,4,5};
  std::set<int> b{2,4,6};
  std::set<int> expected{1,3,5};
  CHECK(Utils::setDifference(a, b) == expected);
}
