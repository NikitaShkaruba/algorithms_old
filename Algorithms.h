#pragma once

namespace algo {
	// Divide and Conquer
	int* SelectionSort(int* arr, size_t size);
	int* InsertionSort(int* arr, size_t size);
	int* BubbleSort(int* arr, size_t size);
	int* MergeSort(int* arr, size_t size);
	unsigned long CountInversions(int* arr, size_t size);
	point* GetClosestPair(point arr[], size_t size);
}
