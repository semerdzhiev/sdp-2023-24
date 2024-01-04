#include "containers/HashTable.h"
#include "utils/Stopwatch.h"

#include <iostream>
#include <cassert>
#include <unordered_set>

template <typename HashType>
void run(int sampleSize, int hits, int misses)
{
	Stopwatch sw;
	HashType hash;

	// STEP 1: fill with elements
	std::cout << "fill...";
	sw.start();
	
	for (int i = 0; i < sampleSize; i++)
		hash.insert(i);	
	
	sw.stop();
	std::cout << sw;

	// STEP 2: reverse fill with elements
	HashType hash2;
	std::cout << " | reverse fill...";
	sw.start();
	
	for (int i = sampleSize - 1; i >= 0; i--)
		hash2.insert(i);	
	
	sw.stop();
	std::cout << sw;

	// STEP 3: search (successful hits)
	std::cout << " | hits...";
	sw.start();

	for (int i = 0; i < hits; i++)
		assert(hash.contains(i % sampleSize));
	
	sw.stop();
	std::cout << sw;


	// STEP 4: search (misses)
	std::cout << " | misses...";
	sw.start();

	int limit = sampleSize + misses;
	for (int i = sampleSize; i < limit; i++)
		assert( ! hash.contains(i));
	
	sw.stop();
	std::cout << sw;

	std::cout << " | load factor " << hash.load_factor();
}

template <typename HashType>
void benchmark(const char* name, size_t runs, int sampleSize, int hits, int misses)
{
	std::cout << name << std::endl;
	std::cout << "  Filling with " << sampleSize << " element(s), " << hits << " hit(s), " << misses << " miss(es)\n";

	for (size_t i = 0; i < runs; i++)
	{
		std::cout << "    " << i << ": ";
		run<HashType>(sampleSize, hits, misses);
		std::cout << std::endl;
	}	
}

void separator()
{
	std::cout << "\n-------------------------------\n\n";
}

int main()
{
	size_t attempts = 3;

	benchmark<VectorOfUnorderedElements<int>>("std::vector (unordered, linear search)", attempts,  10'000,  10'000,  10'000);
	benchmark<VectorOfUnorderedElements<int>>("std::vector (unordered, linear search)", attempts,  30'000,  30'000,  30'000);
	benchmark<VectorOfUnorderedElements<int>>("std::vector (unordered, linear search)", attempts,  60'000,  60'000,  60'000);
	benchmark<VectorOfUnorderedElements<int>>("std::vector (unordered, linear search)", attempts,  90'000,  90'000,  90'000);
	benchmark<VectorOfUnorderedElements<int>>("std::vector (unordered, linear search)", attempts, 200'000, 100'000, 100'000);

	separator();

	benchmark<VectorWithBinarySearch<int>>("std::vector (sorted, binary search)", attempts,  10'000,  10'000,  10'000);
	benchmark<VectorWithBinarySearch<int>>("std::vector (sorted, binary search)", attempts,  30'000,  30'000,  30'000);
	benchmark<VectorWithBinarySearch<int>>("std::vector (sorted, binary search)", attempts,  60'000,  60'000,  60'000);
	benchmark<VectorWithBinarySearch<int>>("std::vector (sorted, binary search)", attempts,  90'000,  90'000,  90'000);
	benchmark<VectorWithBinarySearch<int>>("std::vector (sorted, binary search)", attempts, 200'000, 100'000, 100'000);

	separator();

	benchmark<SeparateChainingHash<int>>("Separate chaining hash table", attempts,    10'000,    10'000,    10'000);
	benchmark<SeparateChainingHash<int>>("Separate chaining hash table", attempts,    30'000,    30'000,    30'000);
	benchmark<SeparateChainingHash<int>>("Separate chaining hash table", attempts,    60'000,    60'000,    60'000);
	benchmark<SeparateChainingHash<int>>("Separate chaining hash table", attempts,    90'000,    90'000,    90'000);
	benchmark<SeparateChainingHash<int>>("Separate chaining hash table", attempts,   200'000,   100'000,   100'000);
	benchmark<SeparateChainingHash<int>>("Separate chaining hash table", attempts, 1'000'000, 1'000'000, 1'000'000);

	separator();

	benchmark<std::unordered_set<int>>("std::unordered_set", attempts,    10'000,    10'000,    10'000);
	benchmark<std::unordered_set<int>>("std::unordered_set", attempts,    30'000,    30'000,    30'000);
	benchmark<std::unordered_set<int>>("std::unordered_set", attempts,    60'000,    60'000,    60'000);
	benchmark<std::unordered_set<int>>("std::unordered_set", attempts,    90'000,    90'000,    90'000);
	benchmark<std::unordered_set<int>>("std::unordered_set", attempts,   200'000,   100'000,   100'000);
	benchmark<std::unordered_set<int>>("std::unordered_set", attempts, 1'000'000, 1'000'000, 1'000'000);	
}