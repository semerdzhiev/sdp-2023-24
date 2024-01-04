#include "catch2/catch_all.hpp"

#include "triangle/Triangle.h"

TEST_CASE("Triangle::perimeter() returns correct values", "[triangle]")
{
    CHECK(Triangle(1, 2, 3).perimeter() == 6);
}

TEST_CASE("Triangle::Triangle(int, int, int) Sides cannot be negative", "[triangle]")
{
    REQUIRE_THROWS_AS(Triangle(-1, 2, 3), std::invalid_argument);
    REQUIRE_THROWS_AS(Triangle(1, -2, 3), std::invalid_argument);
    REQUIRE_THROWS_AS(Triangle(1, 2, -3), std::invalid_argument);
}

TEST_CASE("Triangle::Triangle(int, int, int Sides cannot be zero", "[triangle]")
{
    REQUIRE_THROWS_AS(Triangle(0, 2, 3), std::invalid_argument);
    REQUIRE_THROWS_AS(Triangle(1, 0, 3), std::invalid_argument);
    REQUIRE_THROWS_AS(Triangle(1, 2, 0), std::invalid_argument);
}

TEST_CASE("Triangle::operator==() compares correctly", "[triangle]")
{
    CHECK(Triangle(1, 2, 3) == Triangle(1, 2, 3));
    CHECK(Triangle(1, 2, 3) == Triangle(1, 3, 2));
    CHECK(Triangle(1, 2, 3) == Triangle(2, 1, 3));
    CHECK(Triangle(1, 2, 3) == Triangle(2, 3, 1));
    CHECK(Triangle(1, 2, 3) == Triangle(3, 1, 2));
    CHECK(Triangle(1, 2, 3) == Triangle(3, 2, 1));
}

TEST_CASE("Triangle::Triangle(const Triangle&) correctly copies a triangle", "[triangle]")
{
    Triangle t(1, 2, 3);
    Triangle copy(t);
    bool check = copy == t;
    CHECK((copy == t));
}

TEST_CASE("Triangle::operator=() correctly copies a triangle", "[triangle]")
{
    Triangle t(1, 2, 3);
    Triangle copy(5,6,7);
    copy = t;
    CHECK((copy == t));
}

