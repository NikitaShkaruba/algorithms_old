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
	void HeapSort(int* arr, size_t size);
	void BucketSort(int* arr, size_t size);
	void CountingSort(int* arr, size_t size);
	void RadixSort(int* arr, size_t size);

	// Selection problems
	int& RanomizedSelect(int* arr, size_t size, size_t k);
	int& DeterminedSelect(int* arr, size_t size, size_t k);

	// Count inversions problem
	unsigned long CountInversions(int* arr, size_t size);

	// Closest pair problem
	point* GetClosestPair(point arr[], size_t size);

	// Graph problems
	// Graph KargerMinCut(Graph graph);
}
