#include "catch2/catch_all.hpp"
#include "utils/Allocator.h"
#include "utils/MockingObjects.h"

TEMPLATE_TEST_CASE(
    "Allocator::buy correctly forwards its arguments",
    "[allocator]",
    SimpleAllocator<SingleNonCopiableParameterDummy>,
    DebugAllocator<SingleNonCopiableParameterDummy>)
{
    TestType allocator;
    SingleNonCopiableParameterDummy* result = allocator.buy(NonCopiableDummy());
    allocator.release(result);
}

TEST_CASE("DebugAllocator allocates and releases correctly", "[allocator]")
{
    DebugAllocator<int> allocator;
    std::vector<int*> allocations;
    const int count = 5;

    CHECK(allocator.activeAllocationsCount() == 0);

    for(int i = 1; i <= count; ++i) {
        allocations.push_back(allocator.buy());
        CHECK(allocator.activeAllocationsCount() == i);
        CHECK(allocator.totalAllocationsCount() == i);
    }

    for(int i = count-1; i >= 0; --i) {
        CHECK_NOTHROW(allocator.release(allocations[i]));
        CHECK(allocator.activeAllocationsCount() == i); // The number of active allocations decreases        
        CHECK(allocator.totalAllocationsCount() == count); // No new allocations are made
    }
}

TEST_CASE("DebugAllocator::buy() fails after the specified number of allocations", "[allocator]")
{
    size_t failAfter = 3;
    DebugAllocator<int> allocator(3);

    // The first `failAfter` allocations should succeed
    int* ptr = nullptr;

    for(size_t i = 0; i < failAfter; ++i) {
        REQUIRE_NOTHROW(ptr = allocator.buy());
        allocator.release(ptr);
    }

    // The `failAfter + 1` allocation should fail with a std::bad_alloc
    REQUIRE_THROWS_AS(allocator.buy(), std::bad_alloc);
}

TEST_CASE("DebugAllocator::release() throws when trying to release a pointer not allocated by it", "[allocator]")
{
    DebugAllocator<int> da;
    int* ptr = new int;
    CHECK_THROWS_AS(da.release(ptr), std::invalid_argument);
    delete ptr;
}

TEST_CASE("DebugAllocator::release() does nothing when releasing null", "[allocator]")
{
    DebugAllocator<int> da;
    int* ptr = da.buy();

    CHECK_NOTHROW(da.release(nullptr));
    
    CHECK(da.activeAllocationsCount() == 1);
    CHECK_NOTHROW(da.release(ptr));
}

TEST_CASE("DebugAllocator::failAfter() can be used to set the failAfter counter", "[allocator]")
{
    int failAfter = 3;
    int* ptr;

    SECTION("To set the value for a debug allocator created with no failAfter counter") {
        DebugAllocator<int> allocator;
        allocator.failAfter(3);

        for(size_t i = 0; i < failAfter; ++i) {
            REQUIRE_NOTHROW(ptr = allocator.buy());
            allocator.release(ptr);
        }

        REQUIRE_THROWS_AS(allocator.buy(), std::bad_alloc);
    }
    SECTION("To alter the value for an allocator with an already set failAfter counter") {
        DebugAllocator<int> allocator(failAfter * 2);
        allocator.failAfter(3);

        for(size_t i = 0; i < failAfter; ++i) {
            REQUIRE_NOTHROW(ptr = allocator.buy());
            allocator.release(ptr);
        }

        REQUIRE_THROWS_AS(allocator.buy(), std::bad_alloc);
    }
}
