#include "catch2/catch_all.hpp"
#include "simulator-lib/bar-simulator.h"


///////////////////////////////////////////////////////////////////////////////
//
// Edge cases
//

TEST_CASE("empty simulation")
{
	std::stringstream empty { "0 0 0" };
	std::stringstream output;
	simulate_bar(empty, output);
	REQUIRE(output.str() == "");
}

TEST_CASE("no students")
{
	std::stringstream empty { "1 1 0" };
	std::stringstream output;
	simulate_bar(empty, output);
	REQUIRE(output.str() == "");
}

TEST_CASE("no space in bar")
{
	std::stringstream empty { "0 1 1\n17 0 Fraud 3" };
	std::stringstream output;
	REQUIRE_THROWS_AS(simulate_bar(empty, output), std::runtime_error);
}


///////////////////////////////////////////////////////////////////////////////
//
// Evaluation of correct expressions
//

TEST_CASE("Simple simulation - one student")
{
	std::stringstream empty { "1 1 1\n17 0 Fraud 3" };
	std::stringstream output;
	simulate_bar(empty, output);
	REQUIRE(output.str() == "0 17 enter\n3 17 exit\n");
}

TEST_CASE("Simple simulation - one group")
{
	std::stringstream empty {
    "1 1 2\n"
    "100 0 Fraud 5\n"
    "200 0 Fraud 5\n" };
    const std::string expected =
    "0 100 enter\n"
    "5 100 exit\n"
    "5 200 enter\n"
    "10 200 exit\n";

	std::stringstream output;
	simulate_bar(empty, output);
	REQUIRE(output.str() == expected);
}

TEST_CASE("More complex simulation")
{
	std::stringstream empty {
    "3 2 10\n"
    "220 0 Fraud 10\n"
    "221 1 Fraud 9\n"
    "222 2 Fraud 8\n"
    "320 2 Subjectivistics 10\n"
    "410 2 Micromanagement 10\n"
    "321 3 Subjectivistics 5\n"
    "411 3 Micromanagement 10\n"
    "322 4 Subjectivistics 10\n"
    "323 4 Subjectivistics 10\n"
    "510 5 International Schemes 3\n"};
    const std::string expected =
    "0 220 enter\n"
    "1 221 enter\n"
    "2 222 enter\n"
    "10 220 exit\n"
    "10 221 exit\n"
    "10 222 exit\n"
    "10 320 enter\n"
    "10 321 enter\n"
    "10 510 enter\n"
    "13 510 exit\n"
    "15 321 exit\n"
    "15 410 enter\n"
    "15 411 enter\n"
    "20 320 exit\n"
    "25 410 exit\n"
    "25 411 exit\n"
    "25 322 enter\n"
    "25 323 enter\n"
    "35 322 exit\n"
    "35 323 exit\n";

	std::stringstream output;
	simulate_bar(empty, output);
	REQUIRE(output.str() == expected);
}
