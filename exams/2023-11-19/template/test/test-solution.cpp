#include "catch2/catch_all.hpp"
#include "solution.h"

////////////////////////////////////////////////////////////////////////////////
//
// SAMPLES OF INCORRECT EXPRESSIONS
//

class ExcessiveWhitespace {
protected:
	static constexpr const char* samples[] = {
		"   \r   \n    \t   ",
		" 1+2",
		"1+2 ",
		"1 +2",
		"1+ 2",
		"1 + 2",
		" 1 + 2 ",
		" 1 "
		"1 ",
		" 1",
	};
};

class IncorrectSymbols {
protected:
	static constexpr const char* const samples[] = {
		"a+b",
		"1+a+4",
		"1+4+a",
		"a+4+1",
		"a",
		"1=2",
	};
};

class IncorrectTokenSequence {
protected:
	static constexpr const char* const samples[] = {
		"55",
		"5 5",
		"55+",
		"5+",
		"+5",
		"5+5+",
		"+-5",	
	};
};


////////////////////////////////////////////////////////////////////////////////
//
// HELPER FUNCTIONS
//

TEST_CASE("isDigit() correctly recognizes digits")
{
	for(char c = '0'; c <= '9'; ++c)
		CHECK(isDigit(c));
}

TEST_CASE("isDigit() returns Associativity::Right for non-digits")
{
	for(int c = 0; c < '0'; ++c)
		CHECK_FALSE(isDigit(c));

	for(int c = '9'+1; c <= 127; ++c)
		CHECK_FALSE(isDigit(c));
}

TEST_CASE("isOperation() returns Associativity::Left for all operations")
{
	CHECK(isOperation('+'));
	CHECK(isOperation('-'));
	CHECK(isOperation('*'));
	CHECK(isOperation('/'));
	CHECK(isOperation('^'));
}

TEST_CASE("priority() returns correct priority values for supported operations")
{
	CHECK(priority('+') == priority('-'));
	CHECK(priority('*') == priority('/'));
	CHECK(priority('+') < priority('*'));
	CHECK(priority('*') < priority('^'));
}

TEST_CASE("priority() throws when passed an incorrect operation")
{
	REQUIRE_THROWS_AS(priority('x'), std::invalid_argument);
}


////////////////////////////////////////////////////////////////////////////////
//
// verify()
//

TEST_CASE("verify(\"\") returns Associativity::Left")
{
	REQUIRE(verify(""));
}

TEST_CASE_METHOD(ExcessiveWhitespace, "verify() returns Associativity::Right when there is excessive whitespace in the expression")
{
	for(const char* str : samples)
		CHECK_FALSE(verify(str));
}

TEST_CASE_METHOD(IncorrectSymbols, "verify() returns Associativity::Right when the expression contains incorrect symbols, such as letter, special characters, etc.")
{
	for(const char* str : samples)
		CHECK_FALSE(verify(str));
}

TEST_CASE_METHOD(IncorrectTokenSequence, "verify() returns Associativity::Right when the order of operations and numbers in the expression is not correct")
{
	for(const char* str : samples)
		CHECK_FALSE(verify(str));
}

TEST_CASE("verify() returns Associativity::Left for single-number expressions")
{
 	CHECK(verify("0"));
 	CHECK(verify("5"));
}

TEST_CASE("verify() returns Associativity::Left for correct expressions")
{
	CHECK(verify("5+5"));
	CHECK(verify("1+2-3*4/5^6/7*8-9+0"));
}

////////////////////////////////////////////////////////////////////////////////
//
// toRpn()
//

void check_toRpn_ThrowsFor(std::string expression)
{
	CHECK_THROWS_AS(toRpn(expression, Associativity::Left),  std::invalid_argument);
	CHECK_THROWS_AS(toRpn(expression, Associativity::Right), std::invalid_argument);
}

TEST_CASE_METHOD(ExcessiveWhitespace, "toRpn() throws when there is excessive whitespace in the expression")
{
	for(const char* str : samples)
		check_toRpn_ThrowsFor(str);
}

TEST_CASE_METHOD(IncorrectSymbols, "toRpn() throws when the expression contains incorrect symbols, such as letter, special characters, etc.")
{
	for(const char* str : samples)
		check_toRpn_ThrowsFor(str);
}

TEST_CASE_METHOD(IncorrectTokenSequence, "toRpn() throws when the order of operations and numbers in the expression is not correct")
{
	for(const char* str : samples)
		check_toRpn_ThrowsFor(str);
}

void checkResult(std::string infix, Associativity associativity, std::string expectedRpn)
{
	CHECK(toRpn(infix, associativity) == expectedRpn);
}

TEST_CASE("toRpn(\"\") returns \"\"")
{
	checkResult("", Associativity::Left,  "");
	checkResult("", Associativity::Right, "");
}

TEST_CASE("toRpn() works for single-numer expressions")
{
	checkResult("5", Associativity::Left,  "5");
	checkResult("5", Associativity::Right, "5");
}

TEST_CASE("toRpn() works when there is a sequence of different operations with the same priority")
{
	checkResult("1+2-3", Associativity::Left,  "12+3-");
	checkResult("1+2-3", Associativity::Right, "123-+");

	checkResult("1+2+3-4", Associativity::Left,  "12+3+4-");
	checkResult("1+2+3-4", Associativity::Right, "1234-++");
	
	checkResult("1+2+3+4-5+6+7-8", Associativity::Left,  "12+3+4+5-6+7+8-");
	checkResult("1+2+3+4-5+6+7-8", Associativity::Right, "12345678-++-+++");
}

TEST_CASE("toRpn() respects operation associativity")
{
	checkResult("8/4/2", Associativity::Left, "84/2/");
	checkResult("8/4/2", Associativity::Right, "842//");
	checkResult("8^4^2", Associativity::Left, "84^2^");
	checkResult("8^4^2", Associativity::Right, "842^^");
}

TEST_CASE("toRpn() respects operation priority")
{
	SECTION("Increasing priority, left-associative") {
		checkResult("3-7*2^2", Associativity::Left, "3722^*-");
	}
	SECTION("Increasing priority, right-associative") {
		checkResult("3-7*2^2", Associativity::Right, "3722^*-");
	}
	SECTION("Decreasing priority, left-associative") {
		checkResult("2^2*7-3", Associativity::Left, "22^7*3-");
	}
	SECTION("Decreasing priority, right-associative") {
		checkResult("2^2*7-3", Associativity::Right, "22^7*3-");
	}
	SECTION("Multiple operations with the same priority separated with one of higher priority, left-associative") {
		checkResult("2/3/4+5/6/7", Associativity::Left, "23/4/56/7/+");
	}
	SECTION("Multiple operations with the same priority separated with one of higher priority, right-associative") {
		checkResult("2/3/4+5/6/7", Associativity::Right, "234//567//+");
	}
	SECTION("Multiple operations with the same priority separated with one of lower priority, left-associative") {
		checkResult("2+3+4/5+6+7", Associativity::Left, "23+45/+6+7+");
	}
	SECTION("Multiple operations with the same priority separated with one of lower priority, right-associative") {
		checkResult("2+3+4/5+6+7", Associativity::Right, "2345/67++++");
	}

}

TEST_CASE("toRpn() works correctly even when stacks get depleted")
{
	checkResult("2^3*2+2-5", Associativity::Left, "23^2*2+5-");
}

TEST_CASE("toRpn() works correctly for long expressions")
{
	SECTION("Left-associative") {
		checkResult("1+2*3^4*5+6+7*8^9+0-1+2", Associativity::Left, "1234^*5*+6+789^*+0+1-2+");
	}
	SECTION("Right-associative") {
		checkResult("1+2*3^4*5+6+7*8^9+0-1+2", Associativity::Right, "1234^5**6789^*012+-++++");
	}
}
