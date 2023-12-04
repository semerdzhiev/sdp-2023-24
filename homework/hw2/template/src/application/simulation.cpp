#include "simulator-lib/bar-simulator.h"

int main()
{
	// Try to simulate the student bar system
	try {
		simulate_bar(std::cin, std::cout);
	}
	catch(const incorrect_simulation& e) {
		std::cout << "Some of the simulation states are wrong or invalid: " << e.what() << "\n";
		return 1;
	}
	catch(const std::exception& e) {
		std::cout << "Failed to simulate the student bad: " << e.what() << "\n";
		return 2;
	}
}
