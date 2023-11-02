#include "utils/Stopwatch.h"

int main()
{
	const size_t RowsCount = 5'000;
	const size_t ColsCount = 300'000;

	int *parr = new int[RowsCount * ColsCount];

	size_t row, col;
	unsigned long long sum;
	Stopwatch sw;

	//
	// Initialize the elements of the array
	//
	std::cout << "Initializing the elements of the array...";
	sw.start();

	for (row = 0; row < RowsCount; ++row)
		for (col = 0; col < ColsCount; ++col)
			parr[ColsCount * row + col] = static_cast<int>(row);

	sw.stop();
	std::cout << "\n    execution took " << sw << "\n\n";


	//
	// Iterate over the columns and then the rows and then the columns
	//
	std::cout << "Iterating by columns and then rows...";

	sum = 0;
	sw.start();

	for (col = 0; col < ColsCount; ++col)
		for (row = 0; row < RowsCount; ++row)
			sum += parr[ColsCount * row + col];

	sw.stop();
	std::cout << "\n    execution took " << sw << "\n\n";


	//
	// Iterate over the rows and then the columns
	//
	std::cout << "Iterating by rows and then columns...";

	sum = 0;
	sw.start();

	for (row = 0; row < RowsCount; ++row)
		for (col = 0; col < ColsCount; ++col)
			sum += parr[ColsCount * row + col];

	sw.stop();
	std::cout << "\n    execution took " << sw << "\n\n";

	delete[] parr;

	return 0;
}