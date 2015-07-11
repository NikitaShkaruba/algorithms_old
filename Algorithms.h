#pragma once

namespace algo {
	// some useful common stuff
	template<typename T> void swap(T& a, T& b);
	int* GenerateRandomArray(size_t size);
	int* getSubArray(int const * arr, size_t begin, size_t end);
	bool isSorted(int* arr, size_t size);

	// Divide and Conquer
	int* SelectionSort(int* arr, size_t size);
	int* InsertionSort(int* arr, size_t size);
	int* BubbleSort(int* arr, size_t size);
	int* MergeSort(int* arr, size_t size);
	int CountInversions(int* arr, size_t size);
}