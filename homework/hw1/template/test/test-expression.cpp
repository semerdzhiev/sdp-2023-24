#include "catch2/catch_all.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "expression-lib/expression.h"


///////////////////////////////////////////////////////////////////////////////
//
// Edge cases
//

// Ensures (with REQUIRE) that an expression evaluates to a given value
void requireExpressionEvaluatesTo(const char* expression, std::istream& ops, double expectedValue)
{
	double result = evaluate(expression, ops);
 	REQUIRE_THAT(result, Catch::Matchers::WithinRel(expectedValue, 0.001));	
}

// Ensures (with REQUIRE) that evaluate correctly detects the expression as incorrect.
void requireIncorrectExpressionDetection(const char* expression, std::istream& ops)
{
	REQUIRE_THROWS_AS(evaluate(expression, ops), incorrect_expression);
}

TEST_CASE("evaluate("") returns 0")
{
	std::stringstream empty;
	requireExpressionEvaluatesTo("", empty, 0.0);
}

TEST_CASE("evaluate(\"   \") returns 0")
{
	std::stringstream empty;
	requireExpressionEvaluatesTo("   ", empty, 0.0);
}


TEST_CASE("evaluate(nullptr) throws")
{
	std::stringstream empty;
	requireIncorrectExpressionDetection(nullptr, empty);
}

TEST_CASE("evaluate(\"N\") returns N") {
	std::stringstream empty;
	requireExpressionEvaluatesTo("42", empty, 42);
}

///////////////////////////////////////////////////////////////////////////////
//
// Detection of incorrect expressions
//

TEST_CASE("evaluate() identifies incorrect expressions: basic cases")
{
	std::stringstream ops("a + 10 L");

	SECTION("Space between a unary minus and a number: as first token") {
		requireIncorrectExpressionDetection("- 51 a 52 a 53", ops);
	}
	SECTION("Space between a unary minus and a number: as last token") {
		requireIncorrectExpressionDetection("51 a 52 a - 53", ops);
	}
	SECTION("Space between a unary minus and a number: in the middle") {
		requireIncorrectExpressionDetection("51 a - 52 a 53", ops);
	}
	SECTION("Minus as an operation") {
		requireIncorrectExpressionDetection("52 - 53", ops);
	}
	SECTION("An operation that is not present in the input file: as first operation") {
		requireIncorrectExpressionDetection("6 b 2 a 5", ops);
	}
	SECTION("An operation that is not present in the input file: as last operation") {
		requireIncorrectExpressionDetection("1 a 2 b 3", ops);
	}
	SECTION("Two consecutive operations") {
		requireIncorrectExpressionDetection("1 a a 2", ops);
	}
	SECTION("Expression starting with operation") {
		requireIncorrectExpressionDetection("a 1 a 2", ops);
	}
	SECTION("Expression ending with operation") {
		requireIncorrectExpressionDetection("1 a 2 a", ops);
	}
	SECTION("Two consecutive numbers: in the beginning") {
		requireIncorrectExpressionDetection("1 2 a 3", ops);
	}
	SECTION("Two consecutive numbers: in the end") {
		requireIncorrectExpressionDetection("1 a 2 3", ops);
	}
	SECTION("Two consecutive numbers: in the middle") {
		requireIncorrectExpressionDetection("1 a 2 3 a 4", ops);
	}
	SECTION("Only numbers") {
		requireIncorrectExpressionDetection("1 2 3", ops);
	}
	SECTION("Only operations") {
		requireIncorrectExpressionDetection("a a a", ops);
	}
	SECTION("Incorrect symbol") {
		requireIncorrectExpressionDetection("1 * 2", ops);
	}			
	SECTION("No closing bracket (1)") {
		requireIncorrectExpressionDetection("( 1 a ( 2 a 3 )", ops);
	}
	SECTION("No closing bracket (2)") {
		requireIncorrectExpressionDetection("( ( 1 a 2 ) a 3", ops);
	}
	SECTION("No opening bracket") {
		requireIncorrectExpressionDetection("( 1 a 2 a 3 ) )", ops);
	}
	SECTION("No operation after bracket") {
		requireIncorrectExpressionDetection("( 2 a 6 ) a", ops);
	}
	SECTION("No operation before bracket") {
		requireIncorrectExpressionDetection("a ( 2 a 6 )", ops);
	}
	SECTION("Single operation in brackets") {
		requireIncorrectExpressionDetection("( a )", ops);
	}	
	SECTION("Two brackets") {
		requireIncorrectExpressionDetection("( )", ops);
	}	
	SECTION("Incomplete operation in brackets: on the left") {
		requireIncorrectExpressionDetection("( a 2 a 3 )", ops);
	}	
	SECTION("Incomplete operation in brackets: on the right") {
		requireIncorrectExpressionDetection("( 1 a 2 a )", ops);
	}	
	SECTION("Bracket close to a number: on the left") {
		requireIncorrectExpressionDetection("(1 a 2 )", ops);
	}	
	SECTION("Bracket close to a number: on the right") {
		requireIncorrectExpressionDetection("( 1 a 2)", ops);
	}
	SECTION("Two brackets close together: on the left") {
		requireIncorrectExpressionDetection("(( 1 a 2 ) a 3 )", ops);
	}	
	SECTION("Two brackets close together: on the right") {
		requireIncorrectExpressionDetection("( 1 a ( 2 a 3 ))", ops);
	}	
}

TEST_CASE("evaluate() identifies incorrect expressions: complex cases")
{
	std::stringstream ops(
		"a * 23 R\n"
		"b /  5 R\n"
		"c * 26 R\n"
		"d - 36 L\n"
		"e / 27 R\n"
		"f + 40 R\n"
		"g - 27 R\n"
		"h /  4 R\n"
		"i + 27 R\n"
		"j / 21 R\n"
		"k - 30 L\n"
		"l /  7 R\n"
		"m / 14 L\n"
		"n *  5 R\n"
		"o -  1 L\n"
		"p *  6 R\n"
		"q * 23 L\n"
		"r * 21 L\n"
		"s + 27 L\n"
		"t * 35 R\n"
		"u *  2 R\n"
		"v * 33 L\n"
		"w - 13 R\n"
		"x * 26 L\n"
		"y / 40 R\n"
		"z + 10 L"
	);		

	SECTION("Complex expression 1") {
		requireIncorrectExpressionDetection("2 v -1635 m -4748 n -4579 ) s -1018 h -1028 i 3102 h -4097 p -3837 o -151 i ( 783 ) x 3684 p 3649 u ( -693 s ( -4397 m -2902 l ( -3260 x 4690 d 115 x 2069 s -4872 ) u ( -732 i -3342 ) w ( 3895 b 3598 v -928 n 2080 o ( -3508 ) d -3374 ) ) ) ) )", ops);
	}
}


///////////////////////////////////////////////////////////////////////////////
//
// Evaluation of correct expressions
//

TEST_CASE("evaluate() returns correct values: expressions with one operation")
{
	std::stringstream ops("a + 10 L");

	SECTION("Simple addition: positive + positive") {
		requireExpressionEvaluatesTo("2 a 3", ops, 5);
	}
	SECTION("Simple addition: negative + positive") {
		requireExpressionEvaluatesTo("-1 a 2", ops, 1);
	}
	SECTION("Simple addition: positive + negative") {
		requireExpressionEvaluatesTo("2 a -53", ops, -51);
	}
	SECTION("Simple addition: negative + negative") {
		requireExpressionEvaluatesTo("-52 a -53", ops, -105);
	}
	SECTION("Multiple positive numbers") {
		requireExpressionEvaluatesTo("1 a 2 a 3", ops, 6);
	}
	SECTION("Multiple positive numbers and a negative") {
		requireExpressionEvaluatesTo("3 a 5 a -2", ops, 6);
	}
	SECTION("Mixed positive and negative numbers") {
		requireExpressionEvaluatesTo("-51 a -2 a 8 a 20", ops, -25);
	}
	SECTION("Number + expression in brackets") {
		requireExpressionEvaluatesTo("1 a ( 2 a 3 )", ops, 6);
	}
	SECTION("Expression in brackets + number") {
		requireExpressionEvaluatesTo("( 3 a 6 ) a -2", ops, 7);
	}
	SECTION("Negative numbers and brackets") {
		requireExpressionEvaluatesTo("-51 a ( -2 a 8 )", ops, -45);
	}
	SECTION("Single number in brackets") {
		requireExpressionEvaluatesTo("( 42 )", ops, 42);
	}	
	SECTION("Single negative number in bracket") {
		requireExpressionEvaluatesTo("( -42 )", ops, -42);
	}
	SECTION("All numbers in brackets") {
		requireExpressionEvaluatesTo("( 10 ) a ( -20 ) a ( 30 )", ops, 20);
	}		
}

TEST_CASE("evaluate() returns correct values: expressions with two operations")
{
	std::stringstream ops(
		"a + 10 L\n"
		"b - 10 L");

	SECTION("Two operands: positive numbers, using the first operation") {
		requireExpressionEvaluatesTo("2 a 3", ops, 5);
	}
	SECTION("Two operands: positive numbers, using the second operation") {
		requireExpressionEvaluatesTo("2 b 3", ops, -1);
	}
	SECTION("Two operands: negative and positive") {
		requireExpressionEvaluatesTo("-1 a 2", ops, 1);
	}
	SECTION("Two operands: positive and negative") {
		requireExpressionEvaluatesTo("2 b -53", ops, 55);
	}
	SECTION("Two operands: negative and negative") {
		requireExpressionEvaluatesTo("-52 b -53", ops, 1);
	}
	SECTION("Multiple positive numbers") {
		requireExpressionEvaluatesTo("1 a 2 b 3", ops, 0);
	}
	SECTION("Mix of positive and negative numbers") {
		requireExpressionEvaluatesTo("51 a -1 b 8 b 20", ops, 22);
	}
	SECTION("Number and expression in brackets") {
		requireExpressionEvaluatesTo("1 a ( 2 b 3 )", ops, 0);
	}
	SECTION("Expression in brackets and number") {
		requireExpressionEvaluatesTo("( 3 a 6 ) b -2", ops, 11);
	}
	SECTION("Negative numbers and brackets") {
		requireExpressionEvaluatesTo("-51 b ( -2 b 8 )", ops, -41);
	}
}

TEST_CASE("evaluate() handles associativity correctly")
{
	SECTION("Left associativity, single operation") {
		std::stringstream ops("d / 10 L");
		requireExpressionEvaluatesTo("8 d 4 d 2", ops, 1);
	}
	SECTION("Right associativity, single operation") {
		std::stringstream ops("d / 10 R");
		requireExpressionEvaluatesTo("8 d 4 d 2", ops, 4);
	}
	SECTION("Left associativity, multiple operations") {
		std::stringstream ops(
			"d / 10 L\n"
			"e / 10 L"
			);
		requireExpressionEvaluatesTo("8 d 4 e 2", ops, 1);
	}
	SECTION("Right associativity, multiple operations") {
		std::stringstream ops(
			"d / 10 R\n"
			"e / 10 R"
			);
		requireExpressionEvaluatesTo("8 d 4 e 2", ops, 4);
	}
}

TEST_CASE("evaluate() returns correct values: operations with different priorities")
{
	std::stringstream ops(
		"a + 10 L\n"
		"m * 20 L");

	SECTION("Higher priority on the right") {
		requireExpressionEvaluatesTo("1 a -2 m 3", ops, -5);
	}
	SECTION("Higher priority on the left") {
		requireExpressionEvaluatesTo("3 m 5 a -2", ops, 13);
	}
	SECTION("Two consecutive higher priorities on the right, left-associative (1)") {
		requireExpressionEvaluatesTo("51 a -1 m 8 m 20", ops, -109);
	}
	SECTION("Two consecutive higher priorities on the right, left-associative (2)") {
		requireExpressionEvaluatesTo("-50 m -1 a 3 m 20", ops, 110);
	}
	SECTION("Brackets to the left of a high-priority operation") {
		requireExpressionEvaluatesTo("3 m ( 5 a -2 )", ops, 9);
	}
	SECTION("Brackets to the right of a high-priority operation") {
		requireExpressionEvaluatesTo("( 5 a -2 ) m 3", ops, 9);
	}
	SECTION("Multiple operations in brackets to the left") {
		requireExpressionEvaluatesTo("( 51 a -1 m 8 ) m 2", ops, 86);
	}
	SECTION("Multiple operations in brackets in the middle") {
		requireExpressionEvaluatesTo("-50 m ( -1 a 3 ) m 2", ops, -200);
	}
	SECTION("Multiple operations in brackets to the right") {
		requireExpressionEvaluatesTo("2 m ( 51 a -1 m 8 )", ops, 86);
	}
}

TEST_CASE("evaluate() returns correct values: complex expressions")
{
	std::stringstream ops(
		"a * 23 R\n"
		"b /  5 R\n"
		"c * 26 R\n"
		"d - 36 L\n"
		"e / 27 R\n"
		"f + 40 R\n"
		"g - 27 R\n"
		"h /  4 R\n"
		"i + 27 R\n"
		"j / 21 R\n"
		"k - 30 L\n"
		"l /  7 R\n"
		"m / 14 L\n"
		"n *  5 R\n"
		"o -  1 L\n"
		"p *  6 R\n"
		"q * 23 L\n"
		"r * 21 L\n"
		"s + 27 L\n"
		"t * 35 R\n"
		"u *  2 R\n"
		"v * 33 L\n"
		"w - 13 R\n"
		"x * 26 L\n"
		"y / 40 R\n"
		"z + 10 L"
	);	

	SECTION("Complex expression 1") {
		requireExpressionEvaluatesTo("4742 t -2847 p ( 623 u -3524 s 2749 v 2082 a -3255 ) k ( -1074 v 1766 g -1177 y -4996 m -3818 r -4029 t ( 2314 y -704 ) v ( 3611 ) m 385 r -1285 c ( 1151 ) e ( 4685 b -647 t -1833 u ( 1355 e 2794 g -1279 ) h ( -346 i -875 f -2037 m ( 3425 y 4402 h -759 ) ) ) )", ops, 1.5659433143311414e+20);
	}
	SECTION("Complex expression 2") {	
		requireExpressionEvaluatesTo("-3599 e ( -4453 u 4245 k 1308 d ( -3023 l -4060 ) j -792 i ( 2059 g ( 3075 b 4170 u ( 236 v 1381 z -353 o 4961 j ( 166 h ( -4394 ) x ( 1306 c ( -1952 v -746 z 2735 n ( 644 ) m ( -3965 i ( -231 s -3861 x ( -1424 a -3623 k 765 a ( 589 z ( -1575 f ( -4292 g 2176 h ( -2333 e -4596 ) l 4061 ) d ( -972 r ( -4484 p 3774 a 4052 c -3722 u 1241 j ( -2279 p ( 394 h 4245 u 1603 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) )", ops, -65.6993606761429);
	}
	SECTION("Complex expression 3") {
		requireExpressionEvaluatesTo("4316 q 3315 k ( 463 v -62 u ( 3067 z ( 1396 c -960 h -3212 w ( 2528 ) p 1025 ) e ( -4415 l ( -4984 j ( 1030 ) q ( 860 g ( -2448 r -535 ) ) ) ) ) )", ops, 380000566971.9764);
	}
	SECTION("Complex expression 4") {
		requireExpressionEvaluatesTo("-1934 z 328 h -3665 e 958 u -902 m 2358 g 3145 u 4795 f ( -1970 b -2037 s 1844 ) d ( 2532 i ( 2070 t -2134 ) p -1400 ) v -955 o ( 2212 p ( 228 y 1654 r ( -4443 ) ) )", ops, 2839982747557677.0);
	}
	SECTION("Complex expression 5") {
 		requireExpressionEvaluatesTo("4457 d 4439 d ( -2771 e ( 3761 f -534 v 92 c 35 s ( -3054 n -7 ) r ( 2465 ) d 1736 ) a ( -4512 r ( 1471 ) r ( 361 q ( 3776 h -3270 h 4770 u 2853 l 454 r -212 d -464 v ( -2836 n 3101 u ( -173 y -1375 w ( -1780 m 1866 o -4443 ) i ( 1230 s 924 ) j -2730 k -2693 d 1712 e ( -2651 u 3977 a -4064 p 3823 ) b 3189 c -2261 n -3957 p 3591 ) ) ) ) ) )", ops, 18.0);
	}
	SECTION("Complex expression 6") {
		requireExpressionEvaluatesTo("302 q -3056 c ( -4263 y ( -4359 e -4496 w -1376 h ( 60 l -4530 ) a 1185 ) q 353 t -1819 f -4418 c 1917 r -3060 n ( -4500 u -1816 b -2336 q ( 3453 u ( -3046 s ( 4685 ) o 4116 v ( -2753 h 539 w ( 925 n -2446 h -1978 x ( 140 a 2845 ) o -429 u ( -956 ) a ( 3828 ) e ( 662 k 3560 m ( -4625 g 2946 u 4731 ) t 2993 m 1173 ) ) ) ) ) ) )", ops, 3.5801124752000896e+17);
	}
	SECTION("Complex expression 7") {
		requireExpressionEvaluatesTo("-2497 o ( -3245 l -4461 ) y 4226 e ( -1338 ) z -35 h -3504 w ( -4432 h 2041 a ( 3817 ) p ( -2143 z -2588 h 1704 ) z ( -1314 k ( 2738 g 1968 r 120 e 4889 x ( -4233 j ( -4894 u ( 554 i 4381 c -1319 c ( -1530 ) m 3947 ) ) ) ) ) )", ops, -2497.00998858451);
	}
	SECTION("Complex expression 8") {
		requireExpressionEvaluatesTo("-989 n ( 4599 m -1638 ) v ( -3610 k -196 ) p ( -3898 c -3082 ) v -1413 y -1106 v 4934 m -875 k ( -2173 l ( -2871 x -1238 j ( -3189 c 3294 p ( -2533 h -1755 ) w 4008 s -4419 m -62 ) q 3373 e -955 v 3397 b ( -2800 ) ) )", ops, -7472020485696.734);
	}
	SECTION("Complex expression 9") {
		requireExpressionEvaluatesTo("-4421 h -4412 o -2986 r ( -4862 h 424 g ( 2002 n -4805 z -70 f ( -2322 ) g 4003 b 677 f ( -4748 k ( -1712 c 1651 ) w ( -1897 h ( 974 h 3022 ) r ( 2833 y -3199 ) i -4902 x -980 i ( 3013 o ( -916 ) ) ) ) ) )", ops, -33609.65337078997);
	}
	SECTION("Complex expression 10") {
 		requireExpressionEvaluatesTo("4590 f ( 3355 r -2838 ) n 782 w 2226 p 414 r -3472 f -2625 i 1600 a ( -563 d 2724 t ( 3686 g ( 3275 e ( 2828 e ( -2698 f ( 1633 m ( -2254 e 4199 e 2262 z ( -2015 ) t ( 2180 w ( -4294 u 1912 f -3849 v -1771 l ( -2485 i ( -639 y ( -922 ) g ( -302 w -663 h 1196 u -1386 a ( -4544 p 799 g 1689 w 3830 u 3959 q 1009 ) k ( 1751 ) n -3744 d ( 2153 ) ) ) ) ) ) ) ) ) ) ) ) )", ops, 5.7274537382215336e+23);
	}
	SECTION("Complex expression 11") {
		requireExpressionEvaluatesTo("-4509 m ( 2845 k ( -3199 f ( 220 k ( 4655 y ( -1725 n -4705 e 3472 c ( 2621 u ( -4497 j ( 2252 n ( 2776 z ( -1974 t ( 4331 q ( 3376 ) u 4701 h ( 3807 ) i -2382 w ( 2049 ) r 3262 b ( 3862 d -4108 ) d ( -2843 s -3014 ) t 2296 e ( 3015 ) t -527 k -1254 ) l 795 ) c 1836 m -4486 y -4743 ) i ( 2552 k -4123 j 4876 k ( -1834 p ( 4440 e -3871 l ( 2684 s 2018 o 4257 ) a ( 1284 a -1631 w 2192 ) ) ) ) ) ) ) ) ) ) ) )", ops, -0.011772237251169);
	}
	SECTION("Complex expression 12") {
		requireExpressionEvaluatesTo("1255 s -3170 m 3532 y ( -107 ) j -145 h ( 4877 ) j ( 2423 v ( -3721 b ( -450 o -4754 x ( -3967 ) m -3880 z 2289 ) m ( -1980 ) e 2740 a ( -4332 n 2753 ) d 46 w 4634 ) f ( -1599 e 3745 l ( 4454 t -1251 c -4787 j -3305 q ( -3022 ) s 2560 ) ) )", ops, -3355.760561136443);
	}
	SECTION("Complex expression 13") {
		requireExpressionEvaluatesTo("-996 t ( -2733 b 1166 q -689 ) m ( -93 o ( -2157 n ( 767 d ( -362 z 3869 ) i ( 3697 ) e 182 ) m ( 3410 f -1630 ) f ( -1508 w ( -2089 r ( 2478 ) r ( 2348 o -1368 k ( 2258 s ( 1167 b -3498 ) ) ) ) ) ) )", ops, 0.036433278277033);
	}
}