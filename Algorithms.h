#pragma once
#include <algorithm>
typedef std::pair<int, int> point;

namespace algo {
	// Divide and Conquer
	void SelectionSort(int* arr, size_t size);
	void InsertionSort(int* arr, size_t size);
	void BubbleSort(int* arr, size_t size);
	void MergeSort(int* arr, size_t size);
	void QuickSort(int* arr, size_t size);

	unsigned long CountInversions(int* arr, size_t size);
	point* GetClosestPair(point arr[], size_t size);
}
