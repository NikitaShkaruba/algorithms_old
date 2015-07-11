#include "Algorithms.h"
#include <algorithm>
#include <cstdlib>
#include <time.h>


namespace algo {
	// Divide and Conquer paradigm
	int* SelectionSort(int* arr, size_t size) {
		// Complexity O(n^2)

		for (size_t i = 0; i < size; i++) {		// n*
			int* max = &arr[i];

			// find the smallest
			for (size_t j = i; j < size; j++)	// n*
				if (arr[j] > *max)
					max = &arr[j];

			// put into beginning
			swap(*max, arr[i]);
		}
		return arr;
	}
	int* InsertionSort(int* arr, size_t size) {
		// Complexity O(n^2)

		for (size_t i = 1; i < size; i++) {			// n*
			int key = arr[i];

			// shift everything
			size_t j = i - 1;
			for (; j >= 0 && key > arr[j]; j--)		// n*
				arr[i] = arr[i + 1];


			arr[i + 1] = key; // i+1 for canceling lastiteration
		}
		return arr;
	}
	int* BubbleSort(int* arr, size_t size) {
		// Complexity O(n^2)

		for (size_t i = 0; i < size; i++) {				// n*
			//get rid of a big one
			for (size_t j = 0; j < size - i - 1; j++)	// n*
				if (arr[j] > arr[j + 1])
					swap(arr[j], arr[j + 1]);
		} 
		return arr;
	}
	
	int* merge(int* left, size_t leftSize, int* right, size_t rightSize) {
		// Complexity: O(n)
		// 
		// Explanation:
		// T(8*(rightSize + leftSize) + 3) = T(8*n + 3) = O(n) 

		int i = 0, j = 0;
		int* result = new int[leftSize + rightSize];

		for (size_t k = 0; k < rightSize + leftSize; k++) {
			if (rightSize & leftSize != 0)
				result[k] = left[i] < right[j] ? left[i++] : right[j++];
			else
				result[k] = (i != rightSize) ? left[i++] : right[j++];
		}

		delete[] left;
		delete[] right;
		return result;
	}
	int* MergeSort(int* arr, size_t size) {
		// Complexity O(n*log(n)) 
		// 
		// Explanation:
		// T(n) = 3 + 2*T(n/2) + n = T(n*log(n) + n) = O(n*log(n))
		// coz recursion depth is log<2>(n)

		if (size == 1)
			return arr;

		int leftSize = size / 2;
		int* left = MergeSort(getSubArray(arr, 0, size / 2 - 1), leftSize);			// T(n/2)
		
		int rightSize = size - leftSize;
		int* right = MergeSort(getSubArray(arr, size / 2, size - 1), rightSize);	// T(n/2)

		return merge(left, leftSize, right, rightSize);								// n*
	}

	int* invMerge(int* left, size_t leftSize, int* right, size_t rightSize, int& counter) { 
		// Raw
		
		int i = 0, j = 0;
		int* result = new int[leftSize + rightSize];

		for (size_t k = 0; k < rightSize + leftSize; k++) {
			if (rightSize & leftSize != 0)
				if (left[i] > right[j]) {
					counter++;
					result[k] = right[j++];
				} else
					result[k] = left[i++];
			else {
				if (j == rightSize) {
					counter++;
					result[k] = left[i++];
				} else
					result[k] = right[j++];
			}
		}

		delete left;
		delete right;
		return result;
	}
	int* CountInversionsSort(int * arr, size_t size, int & counter) {
		// Raw
		
		if (size == 1)
			return arr;

		int leftSize = size / 2;
		int* left = getSubArray(arr, 0, size / 2 - 1);
		CountInversionsSort(left, leftSize, counter);

		int rightSize = size - leftSize;
		int* right = getSubArray(arr, size / 2, size - 1);
		CountInversionsSort(right, leftSize, counter);

		return invMerge(left, leftSize, right, rightSize, counter);
	}
	int CountInversions(int * arr, size_t size) {
		// Raw
		
		int counter = 0;
		int* buffer = new int[size];
		std::copy(arr, &arr[size], buffer);
		
		CountInversionsSort(buffer, size, counter);
		
		delete buffer;
		return counter;
	}
	
	// some useful common stuff
	template<typename T> void swap(T& a, T& b) {
		T buf(a);
		a = b;
		b = buf;
	}
	int* GenerateRandomArray(size_t size) {
		srand(time(0));

		int* arr = new int[size];
		for (size_t i = 0; i < size; i++)
			arr[i] = rand();

		return arr;
	}
	int* getSubArray(int const * arr, size_t begin, size_t end) {
		int* result = new int[end - begin + 1];

		for (size_t i = begin; i < end; i++)
			result[end - begin] = arr[i];

		return result;
	}
	bool isSorted(int* arr, size_t size) {
		for (size_t i = 0; i < size; i++)
			if (arr[i] < arr[i - 1])
				return false;
		return true;
	}
}