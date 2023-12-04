#include "catch2/catch_all.hpp"

#include "containers/FixedSizeArray.h"

template <typename T>
void checkWhetherEmpty(FixedSizeArray<T>& arr)
{
  const FixedSizeArray<T>& cref = arr;
  CHECK(arr.size() == 0);
  CHECK(arr.data() == nullptr);
  CHECK(cref.data() == nullptr);
  CHECK(arr.empty());
}

template <typename T>
void checkWhetherNotEmpty(FixedSizeArray<T>& arr, size_t expectedSize)
{
  const FixedSizeArray<int>& cref = arr;
  CHECK(arr.size() == expectedSize);
  CHECK(arr.data() != nullptr);
  CHECK(cref.data() == arr.data());
  CHECK_FALSE(arr.empty());
}


SCENARIO("FixedSizeArray() creates an empty object", "[FixedSizeArray]")
{
  GIVEN("A default-constructed FixedSizeArray object")
  {
    FixedSizeArray<int> arr;

    WHEN("We use its selectors to check its state") {
      THEN("They correctly report an empty state") {
        checkWhetherEmpty(arr);
      }
    }
  }
}

SCENARIO("FixedArraySize(size_t N = 0) constructs an empty object", "[FixedSizeArray]")
{
  GIVEN("A FixedSizeArray object created with zero size")
  {
    FixedSizeArray<int> arr(0);

    WHEN("We use its selectors to check its state") {
      THEN("They correctly report an empty state") {
        checkWhetherEmpty(arr);
      }
    }
  }
}

SCENARIO("FixedArraySize(size_t N > 0) correctly constructs an object with the specified size", "[FixedSizeArray]")
{
  GIVEN("A FixedSizeArray object created with positive size")
  {
    FixedSizeArray<int> arr(5);

    WHEN("We use its selectors to check its state") {
      THEN("They correctly report an empty state") {
        checkWhetherNotEmpty(arr, 5);
      }
    }
  }
}

SCENARIO("FixedSizeArray(size_t N > 0) throws when passed a size that does not fit in memory", "[FixedSizeArray]")
{
  GIVEN("A size, which does not fit in the heap")
  {
	  size_t size = 100'000'000'000;

    WHEN("We call FixedArraySize(size_t) with that size") {
      THEN("a std::bad_alloc exception is thrown") {
	      REQUIRE_THROWS_AS(FixedSizeArray<int>(size), std::bad_alloc);
      }
    }
  }
}

SCENARIO("FixedSizeArray(const FixedSizeArray&) throws when passed a size that does not fit in memory", "[FixedSizeArray]")
{
  //TODO Implement this test

  GIVEN("An array of size, which cannot be replicated, due to a lack of available memory")
  {
    WHEN("We call the copy constructor") {
      THEN("a std::bad_alloc exception is thrown") {
      }
    }
  }
}

SCENARIO("FixedSizeArray::operator[] can be used to access all elements of the array", "[FixedSizeArray]")
{
  GIVEN("An array with a specific size N")
  {
    size_t N = 10;
    FixedSizeArray<size_t> arr(N);

    WHEN("We fill the array with exactly N elements using operator[]")
    {
      for (size_t i = 0; i < N; ++i)
        arr[i] = i;

      THEN("operator[] correctly retrieves the stored values")
      {
        for (size_t i = 0; i < N; ++i)
          REQUIRE(arr[i] == i);
      }

      THEN("operator[] const correctly retrieves the stored values")
      {
        const FixedSizeArray<size_t>& cref = arr;
        for (size_t i = 0; i < N; ++i)
          REQUIRE(cref[i] == i);
      }
    }
  }
}

SCENARIO("FixedSizeArray::at() can be used to access all elements of the array", "[FixedSizeArray]")
{
  GIVEN("An array with a specific size N")
  {
    size_t N = 10;
    FixedSizeArray<size_t> arr(N);

    WHEN("We fill the array with exactly N elements using at()")
    {
      for (size_t i = 0; i < N; ++i)
        arr.at(i) = i;

      THEN("at() correctly retrieves the stored values")
      {
        for (size_t i = 0; i < N; ++i)
          REQUIRE(arr.at(i) == i);
      }

      THEN("at() const correctly retrieves the stored values")
      {
        const FixedSizeArray<size_t>& cref = arr;
        for (size_t i = 0; i < N; ++i)
          REQUIRE(cref.at(i) == i);
      }
    }
  }
}

SCENARIO("FixedSizeArray::at() throws if the index is not valid", "[FixedSizeArray]")
{
  GIVEN("A non-empty array")
  {
    FixedSizeArray<size_t> arr(5);

    WHEN("We try to access an element outside of the bounds of the array") {
      THEN("at() throws an exception") {
        REQUIRE_THROWS_AS(arr.at(arr.size()), std::out_of_range);
      }
      THEN("at() const throws an exception") {
        const FixedSizeArray<size_t>& cref = arr;
        REQUIRE_THROWS_AS(cref.at(arr.size()), std::out_of_range);
      }
    }
  }
}

template <size_t Start = 0, size_t End = 5>
class ArrayOfNumbersFixture
{
  static_assert(Start <= End); // Ensure the user only passes valid data

public:
  const size_t initialSize = End - Start + 1;
  FixedSizeArray<size_t> arr = FixedSizeArray<size_t>(initialSize);
  const FixedSizeArray<size_t>& cref = arr; /// Constant reference to the array

  /// Fill the array with all numbers in [Start, End] in ascending order
  ArrayOfNumbersFixture()
  {
    for (size_t i = 0; i < initialSize; i++)
      arr[i] = Start + i;
  }

  /// Check whether the array contains all numbers in [Start, End] in ascending order
  bool arrayContainsAllNumbersBetween(size_t begin, size_t end) const
  {
    const size_t size = end - begin + 1;

    if (arr.size() != size)
      return false;

    for (size_t i = 0; i < arr.size(); i++) {
      if (arr[i] != i + begin)
        return false;
    }

    return true;
  }

  /// Check whether the array is the same as when the fixture created it
  bool arrayIsSameAsWhenFirstCreated() const
  {
    return arrayContainsAllNumbersBetween(Start, End);
  }
};

SCENARIO("FixedSizeArray::operator== returns true when comparing two empty arrays")
{
  GIVEN("Two empty arrays")
  {
    FixedSizeArray<size_t> arr1;
    FixedSizeArray<size_t> arr2;

    WHEN("We compare the arrays") {
      THEN("operator== returns true") {
        CHECK(arr1 == arr2);
      }
    }
  }
}

SCENARIO("FixedSizeArray::operator== returns true when the contents of two arrays match")
{
  GIVEN("Two non-empty arrays with identical size and contents")
  {
    ArrayOfNumbersFixture fx1;
    ArrayOfNumbersFixture fx2;

    WHEN("We compare the arrays") {
      THEN("operator== returns true") {
        CHECK(fx1.arr == fx2.arr);
      }
    }
  }
}

SCENARIO("FixedSizeArray::operator== returns false when two arrays of the same size have different contents")
{
  GIVEN("Two non-empty arrays with identical size and different contents")
  {
    ArrayOfNumbersFixture fx1;
    ArrayOfNumbersFixture fx2;
    fx2.arr[0] = 1000; // pick a value outside of those stored in the array

    WHEN("We compare the arrays") {
      THEN("operator== returns true") {
        REQUIRE_FALSE(fx1.arr == fx2.arr);
      }
    }
  }
}

SCENARIO("FixedSizeArray::operator== returns false when we compare non-empty arrays of different sizes")
{
  GIVEN("Two arrays of different sizes")
  {
    ArrayOfNumbersFixture<1,5> shorterFx;
    ArrayOfNumbersFixture<1,7> longerFx;

    WHEN("We compare the shorter to the longer") {
      THEN("operator== returns false") {
        REQUIRE_FALSE(shorterFx.arr == longerFx.arr);
      }
    }

    WHEN("We compare the longer to the shorter") {
      THEN("operator== returns false") {
        REQUIRE_FALSE(longerFx.arr == shorterFx.arr);
      }
    }
  }
}

SCENARIO("FixedSizeArray::operator== returns false when we compare an empty array to a non-empty one")
{
  GIVEN("An empty and a non-empty array")
  {
    ArrayOfNumbersFixture nonEmptyFx;
    FixedSizeArray<size_t> empty;


    WHEN("We compare the empty to the non-empty") {
      THEN("operator== returns false") {
        REQUIRE_FALSE(empty == nonEmptyFx.arr);
      }
    }

    WHEN("We compare the non-empty to the empty") {
      THEN("operator== returns false") {
        REQUIRE_FALSE(nonEmptyFx.arr == empty);
      }
    }
  }
}

SCENARIO("FixedSizeArray::fillFrom() does not change the array when copying from an empty one", "[FixedSizeArray]")
{
  GIVEN("A non-empty array")
  {
    ArrayOfNumbersFixture fx;

    WHEN("We we try to fill from an empty array") {
      FixedSizeArray<size_t> empty;
      fx.arr.fillFrom(empty);

      THEN("Then the array remains empty") {
        REQUIRE(fx.arrayIsSameAsWhenFirstCreated());
      }
    }
  }
}

SCENARIO("FixedSizeArray::fillFrom() partially copies the contents of a larger array", "[FixedSizeArray]")
{
  GIVEN("A non-empty array")
  {
    ArrayOfNumbersFixture<1,5> fxShort;

    WHEN("We we try to fill from an array with a greater size and different elements") {
      ArrayOfNumbersFixture<11, 17> fxLong;

      fxShort.arr.fillFrom(fxLong.arr);

      THEN("Then the size of the array remains the same") {
        CHECK(fxShort.arr.size() == 5);
      }
      THEN("The elements from the larger array have been copied correctly") {
        CHECK(fxShort.arrayContainsAllNumbersBetween(11, 15));
      }
    }
  }
}

SCENARIO("FixedSizeArray::fillFrom() copies the element of a shorter array without overwriting the rest of the original contents", "[FixedSizeArray]")
{
  GIVEN("A non-empty array")
  {
    ArrayOfNumbersFixture<1, 5> fxLong;

    WHEN("We we try to fill from an array with a shorter size and different elements") {
      ArrayOfNumbersFixture<11, 13> fxShort;
      fxLong.arr.fillFrom(fxShort.arr);

      THEN("Then the size of the array remains the same") {
        CHECK(fxLong.arr.size() == 5);
      }
      THEN("The elements from the shorter array have been copied correctly") {
        // Create the array {11, 12, 13, 4, 5}
        ArrayOfNumbersFixture<11, 15> fxExpected;
        fxExpected.arr[3] = 4;
        fxExpected.arr[4] = 5;
        // Check whether this is what we got from the fill operation
        CHECK(fxExpected.arr == fxLong.arr);
      }
    }
  }
}

SCENARIO("FixedSizeArray: The contents of two arrays can be swapped", "[FixedSizeArray]")
{
  GIVEN("Two arrays with different dimensions and elements")
  {
    ArrayOfNumbersFixture<1, 5> fxLong;
    ArrayOfNumbersFixture<6, 8> fxShort;

    const size_t* bufferLong = fxLong.arr.data();
    const size_t* bufferShort = fxShort.arr.data();

    WHEN("Their contents are swapped")
    {
      fxLong.arr.swap(fxShort.arr);

      THEN("The sizes are swapped correctly")
      {
        CHECK(fxShort.arr.size() == fxLong.initialSize);
        CHECK(fxLong.arr.size() == fxShort.initialSize);
      }

      THEN("The underlying arrays remain the same and are swapped correctly")
      {
        CHECK(fxShort.arr.data() == bufferLong);
        CHECK(fxLong.arr.data() == bufferShort);
      }

      THEN("The elements of the arrays are preserved")
      {
        CHECK(fxLong.arrayContainsAllNumbersBetween(6, 8));
        CHECK(fxShort.arrayContainsAllNumbersBetween(1, 5));
      }
    }
  }
}

SCENARIO("FixedSizeArray(const FixedSizeArray&) creates an identical copy of an empty array", "[FixedSizeArray]")
{
  GIVEN("An empty array")
  {
    FixedSizeArray<int> empty;

    WHEN("We pass it to the copy constructor")
    {
      FixedSizeArray<int> copy(empty);

      THEN("The copy is also an empty array") {
        checkWhetherEmpty(copy);
      }
    }
  }
}

SCENARIO("FixedSizeArray(const FixedSizeArray&) creates an identical copy of an non-empty array", "[FixedSizeArray]")
{
  GIVEN("A non-empty array")
  {
    ArrayOfNumbersFixture fx;

    WHEN("We pass it to the copy constructor")
    {
      FixedSizeArray<size_t> copy(fx.arr);

      THEN("The target array becomes identical to the source") {
        REQUIRE(fx.arr == copy);
      }
    }
  }
}

SCENARIO("FixesSizeArray::operator= empties an array when assigning from the empty array", "[FixedSizeArray]")
{
  GIVEN("An empty array")
  {
    FixedSizeArray<int> empty;

    WHEN("We copy it into an empty target array")
    {
      FixedSizeArray<int> copy;
      copy = empty;

      THEN("The target remains empty") {
        checkWhetherEmpty(copy);
      }
    }

    WHEN("we copy it into a non-empty array") {
      FixedSizeArray<int> copy(10);
      copy = empty;

      THEN("The target becomes empty") {
        checkWhetherEmpty(copy);
      }
    }
  }
}

SCENARIO("FixesSizeArray::operator= correctly copies a non-empty array", "[FixedSizeArray]")
{
  GIVEN("A non-empty array")
  {
    ArrayOfNumbersFixture<1, 5> fx;

    WHEN("We copy it into an empty target array")
    {
      FixedSizeArray<size_t> copy;
      copy = fx.arr;

      THEN("The target array becomes identical to the source") {
        CHECK(copy == fx.arr);
      }
    }

    WHEN("We copy it into a non-empty target array with different size")
    {
      ArrayOfNumbersFixture<11, 17> fxCopy;
      fxCopy.arr = fx.arr;

      THEN("The target array becomes identical to the source") {
        CHECK(fxCopy.arr == fx.arr);
      }
    }
  }
}

SCENARIO("FixedSizeArray(FixedSizeArray&&) correctly moves the contents of another array", "[FixedSizeArray]")
{
  GIVEN("A non-empty array with a buffer at a given address")
  {
    ArrayOfNumbersFixture fx;
    const size_t* buffer = fx.arr.data();

    WHEN("We we use the move constructor to extract its contents")
    {
      FixedSizeArray<size_t> movedTo(std::move(fx.arr));
      const FixedSizeArray<size_t>& cref = movedTo;

      THEN("The new array points to the same buffer") {
        REQUIRE(movedTo.data() == buffer);
        REQUIRE(cref.data() == buffer);
      }
      THEN("The new array has the same size as the original") {
        REQUIRE(movedTo.size() == fx.initialSize);
      }
      THEN("The old array has an empty state") {
        checkWhetherEmpty(fx.arr);
      }
    }
  }
}

SCENARIO("FixedSizeArray::operator=(FixedSizeArray&&) correctly moves to an empty array", "[FixedSizeArray]")
{
  GIVEN("A non-empty source array with a buffer at a given address")
  {
    ArrayOfNumbersFixture fx;
    const size_t* buffer = fx.arr.data();

    WHEN("We we use move assignment to transfer its contents to an empty target array")
    {
      FixedSizeArray<size_t> movedTo;
      movedTo = std::move(fx.arr);
      const FixedSizeArray<size_t>& cref = movedTo;

      THEN("The target array points to the same buffer") {
        REQUIRE(movedTo.data() == buffer);
        REQUIRE(cref.data() == buffer);
      }
      THEN("The target array has the same size as the original") {
        REQUIRE(movedTo.size() == fx.initialSize);
      }
      THEN("The source array has an empty state") {
        checkWhetherEmpty(fx.arr);
      }
    }
  }
}

SCENARIO("FixedSizeArray::operator=(FixedSizeArray&&) correctly moves to a non-empty array", "[FixedSizeArray]")
{
  GIVEN("A non-empty source array with a buffer at a given address")
  {
    ArrayOfNumbersFixture fx;
    const size_t* buffer = fx.arr.data();

    WHEN("We we use move assignment to transfer its contents to a non-empty target array")
    {
      FixedSizeArray<size_t> movedTo(10);
      movedTo = std::move(fx.arr);
      const FixedSizeArray<size_t>& cref = movedTo;

      THEN("The target array points to the same buffer") {
        REQUIRE(movedTo.data() == buffer);
        REQUIRE(cref.data() == buffer);
      }
      THEN("The target array has the same size as the original") {
        REQUIRE(movedTo.size() == fx.initialSize);
      }
      THEN("The source array has an empty state") {
        checkWhetherEmpty(fx.arr);
      }
    }
  }
}


