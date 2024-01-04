#include "catch2/catch_all.hpp"
#include "utils/MockingObjects.h"

TEST_CASE("ConstructorSpy correctly reports each constructor type")
{
    SECTION("Default constructor") {
        ConstructorSpy obj;
        CHECK(obj.constructedBy == ConstructorSpy::ConstructorType::Default);
    }
    SECTION("Copy constructor") {
        ConstructorSpy original;
        ConstructorSpy copy(original);
        CHECK(copy.constructedBy == ConstructorSpy::ConstructorType::Copy);
    }
    SECTION("Move constructor") {
        ConstructorSpy original;
        ConstructorSpy moved(std::move(original));
        CHECK(moved.constructedBy == ConstructorSpy::ConstructorType::Move);
    }
}