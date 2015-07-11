#include "Algorithms.h"
#include <algorithm>
#include <iostream>
#include <cassert> 
#include <cmath>

void main() {
	int* (*sorts[])(int*, size_t) = { algo::SelectionSort, algo::InsertionSort, algo::BubbleSort, algo::MergeSort };
	for (size_t i = 0; i < 4; i++) {
		size_t elementsCount = 512;
		int* arr = algo::GenerateRandomArray(elementsCount);

		assert(algo::isSorted(sorts[i](arr, elementsCount), elementsCount));
		delete[] arr;
	}
	std::cout << "Fine, All works properly. Press any key to continue...";
}