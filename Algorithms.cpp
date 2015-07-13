#include "Algorithms.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

namespace algo {
	// some useful common stuff
	template<typename T> void swap(T& a, T& b) {
	// Complexity: O(1)
		T buf(a);
		a = b;
		b = buf;
	}
	template<typename T> T* getSubArray(T* arr, size_t count) {
	// Complexity: O(1)
	// coz T(n) = O(count) = O(1)
		T* result = new T[count];

		for (size_t i = 0; i < count; i++)		// count*
			result[i] = arr[i];

		return result;
	}

	// Divide and Conquer paradigm
	void SelectionSort(int* arr, size_t size) {
	// Complexity: O(n^2)

		for (size_t i = 0; i < size; i++) {		// n*
			int* min = &arr[i];

			// find the smallest
			for (size_t j = i; j < size; j++)	// n*
				if (arr[j] < *min)
					min = &arr[j];

			// put into beginning
			swap(*min, arr[i]);
		}
	}
	void InsertionSort(int* arr, size_t size) {
	// Complexity: O(n^2)

		for (size_t i = 1; i < size; i++) {			// n*
			int key = arr[i];

			// shift everything
			size_t j = i - 1;
			for (; j >= 0 && key < arr[j]; j--)		// n*
				arr[j+1] = arr[j];

			arr[j + 1] = key;
		}
	}
	void BubbleSort(int* arr, size_t size) {
	// Complexity: O(n^2)

		for (size_t i = 0; i < size; i++) {				// n*
			//get rid of a big one
			for (size_t j = 0; j < size - i - 1; j++)	// n*
				if (arr[j] > arr[j + 1])
					swap(arr[j], arr[j + 1]);
		}
	}
	void MergeSort(int* arr, size_t size) {
	// Complexity O(n*log(n)) 
	// coz T(n) = 3 + 2*T(n/2) + n = T(n*log(n) + n) = O(n*log(n))
	// notice: recursion depth is log<2>(n)
		if (size == 1)
			return;

		MergeSort(arr, size/2);						// T(n/2)*
		MergeSort(arr + size/2, size - size/2);		// T(n/2)*

		int l = 0, r = size/2;	// left and right indexes respectivelly
		int* buf = getSubArray(arr, size);

		for (size_t i = 0; i < size; i++) {			// O(n)
			if (l != size/2 && r != size)
				arr[i] = buf[l] < buf[r] ? buf[l++] : buf[r++];
			else
				arr[i] = (l != size/2) ? buf[l++] : buf[r++];
		}
		delete[] buf;
	}
	void QuickSort(int* arr, size_t size) {
		if (size <= 1)
			return;

		srand(time(0));
		int key = rand() % size, l = 0, r = size - 1;
		int* buf = getSubArray(arr, size);
		for (size_t i = 0; i < size; i++) {
			if (buf[i] > buf[key])
				arr[r--] = buf[i];
			if (buf[i] < buf[key])
				arr[l++] = buf[i];
		}
		arr[l] = buf[key];
		delete buf;

		QuickSort(arr, l);
		QuickSort(arr + l + 1, size - l - 1);
	}

	int* invMerge(int* left, size_t leftSize, int* right, size_t rightSize, size_t& counter) { 
	// Complexity: O(n) 
	// coz: T(n) = O(leftSize + rightSize) = O(n)
		int i = 0, j = 0;
		int* result = new int[leftSize + rightSize];

		for (size_t k = 0; k < rightSize + leftSize; k++) {		// n*
			if (i != leftSize && j != rightSize)
				if (left[i] > right[j]) {
					counter += leftSize - i;
					result[k] = right[j++];
				} else
					result[k] = left[i++];
			else {
				if (j == rightSize) {
					result[k] = left[i++];
				} else
					result[k] = right[j++];
			}
		}

		delete left;
		delete right;
		return result;
	}
	int* CountInversionsSort(int* arr, size_t size, size_t& counter) {
	// Complexity: O(n*log(n))
	// coz T(n) = 3 + 2*T(n/2) + n = T(n*log(n) + n) = O(n*log(n))
	// notice: recursion depth is log<2>(n)
		if (size == 1)
			return arr;

		int leftSize = size / 2;
		int* left = CountInversionsSort(getSubArray(arr, leftSize), leftSize, counter);					// T(n/2)

		int rightSize = size - leftSize;
		int* right = CountInversionsSort(getSubArray(arr + leftSize, rightSize), rightSize, counter);	// T(n/2)

		return invMerge(left, leftSize, right, rightSize, counter);										//n
	}
	unsigned long CountInversions(int * arr, size_t size) {
	// Just nahdy enter point for user. Look up inside CountInversionsSort(...) which place is down below
		size_t counter = 0;
		int* buffer = new int[size];
		std::copy(arr, &arr[size], buffer);
		
		CountInversionsSort(buffer, size, counter);
		
		delete buffer;
		return counter;
	}
	
	// optimize this later ^)
	typedef std::pair<int, int> point;
	int getDistance(point left, point right) {
		return std::abs(std::sqrt(std::pow(left.first, 2) + std::pow(left.second, 2)) - std::sqrt(std::pow(right.first, 2) + std::pow(right.second, 2)));
	}
	int getDistance(point points[2]) {
		return getDistance(points[0], points[1]);
	}
	point* GetClosestSplitPair(point xSorted[], point ySorted[], size_t size, size_t delta) {
		int best = delta, count = 0, separator = xSorted[size / 2].first;
		point* filtered = new point[size]/*!!!*/, *bestPair = new point[2];
		
		for (size_t i = 0; i < size; i++)									// O(n)
			if (separator - delta < ySorted[i].first < separator + delta)
				filtered[count++] = ySorted[i];

		for (size_t i = 1; i < count - 1; i++)								// O(n)
			for (size_t j = 1;  j < (count - i < 7 )? 7 : count; j++)
				if (getDistance(filtered[i], filtered[j]) < best) {
					best = getDistance(filtered[i], filtered[j]);
					bestPair[0] = filtered[i];
					bestPair[1] = filtered[j];
				}
		return bestPair;
		// linear comparison
	}
	bool xComparator(point a, point b) {
		return (a.first < b.first);
	}
	bool yComparator(point a, point b) {
		return (a.second < b.second);
	}
	point* GetClosestPair(point xSorted[], point ySorted[], size_t size) {
		if (size <= 2)
			return xSorted;
		
		// case 1
		point* Lx = getSubArray(xSorted, size / 2),	*Ly = getSubArray(ySorted, size / 2);					// 2*O(n)
		point* Lresult = GetClosestPair(Lx, Ly, size / 2);
		// case 2
		point* Rx = getSubArray(xSorted, size - size / 2), *Ry = getSubArray(ySorted, size - size / 2);		// 2*O(n)
		point* Rresult = GetClosestPair(Rx, Ry, size - size / 2);
		// case 3
		int delta = (getDistance(Lresult) < getDistance(Rresult))? getDistance(Lresult) : getDistance(Rresult); // O(n)
		point* Cresult = GetClosestSplitPair(xSorted, ySorted, size, delta);

		return (Cresult != NULL) ? Cresult : (getDistance(Lresult) < getDistance(Rresult))? Lresult : Rresult;
	}
	point* GetClosestPair(point arr[], size_t size) {
		// Complexity: n*log(n)
		point* X = new point[size];
		std::copy(arr, &arr[size], X);
		point* Y = new point[size];
		std::copy(arr, &arr[size], Y);

		std::sort(X, &X[size], xComparator);
		std::sort(Y, &Y[size], yComparator);

		point* result = GetClosestPair(X, Y, size);
		for (size_t i = 0; i < size; i++) {
			if (arr[i].first == result[i].first && arr[i].second == result[i].second) {
				delete X;
				delete Y;
				delete result;
				return &arr[i];
			}
		}
		return NULL;
	}	
}