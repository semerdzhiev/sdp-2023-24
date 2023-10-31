#include <iostream>
#include <fstream>
#include <filesystem>

#include "expression-lib/expression.h"

namespace fs = std::filesystem;

void displayUsage(const char* executablePath)
{
	try {
		fs::path ep(executablePath);
		
		std::cout
			<< "Usage:\n\t"
			<< ep.filename()
			<< " <expression> <op-file>\n";
	}
	catch (...) {
		std::cout << "Cannot parse executable path from argv[0]\n";
	}
}

int main(int argc, char* argv[])
{
	// Check if the necessary number of arguments has been passed
	if (argc != 3) {
		displayUsage(argv[0]);
		return 1;
	}

	// Try to open the input file for reading
	std::ifstream ops(argv[2]);

	if( ! ops) {
		std::cout << "Cannot open \"" << argv[2] <<"\" for reading!\n";
		return 2;
	}

	// Display some info on what is being processed
	std::cout << "Expression is \"" << argv[1] << "\"\n";
	std::cout << "Operations file is \"" << argv[2] << "\"\n";

	// Try to evaluate the expression
	try {
		double result = evaluate(argv[1], ops);
		std::cout << "Calculated value is " << result << "\n";
	}
	catch(incorrect_expression& e) {
		std::cout << "The provided expression is incorrect: " << e.what() << "\n";
		return 3;
	}
	catch(std::exception& e) {
		std::cout << "Cannot evaluate expression: " << e.what() << "\n";
		return 4;
	}
}