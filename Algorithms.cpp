#include "Algorithms.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

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
	int* SelectionSort(int* arr, size_t size) {
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
		return arr;
	}
	int* InsertionSort(int* arr, size_t size) {
	// Complexity: O(n^2)

		for (size_t i = 1; i < size; i++) {			// n*
			int key = arr[i];

			// shift everything
			size_t j = i - 1;
			for (; j >= 0 && key < arr[j]; j--)		// n*
				arr[j+1] = arr[j];

			arr[j + 1] = key;
		}
		return arr;
	}
	int* BubbleSort(int* arr, size_t size) {
	// Complexity: O(n^2)

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
	// coz T(8*(rightSize + leftSize) + 3) = T(8*n + 3) = O(n) 

		int i = 0, j = 0;
		int* result = new int[leftSize + rightSize];

		for (size_t k = 0; k < leftSize + rightSize; k++) {
			if ((i != leftSize && j != rightSize) != 0)
				result[k] = left[i] < right[j] ? left[i++] : right[j++];
			else
				result[k] = (i != leftSize) ? left[i++] : right[j++];
		}

		delete left;
		delete right;
		return result;
	}
	int* MergeSort(int* arr, size_t size) {
	// Complexity O(n*log(n)) 
	// coz T(n) = 3 + 2*T(n/2) + n = T(n*log(n) + n) = O(n*log(n))
	// notice: recursion depth is log<2>(n)
		if (size == 1)
			return arr;
		
		int* left = MergeSort(getSubArray(arr, size / 2), size/2);									// T(n/2)*
		int* right = MergeSort(getSubArray(arr + size / 2, size - size/2), size - size / 2);		// T(n/2)*
		
		return merge(left, size/2, right, size - size/2);											// n*
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
	
	// Shtrassen :\
	//template<size_t n>
	//int* getSubMatrix(int m[n][n], int whereTo) {
	//	// 1, 2, 3, 4 left to right, top to bottom
	//	int* result = new int[n / 2][n / 2];
	//	int i, j;
	//	switch (whereTo) {
	//	case 1: {
	//		for (size_t i = 0; i <= n / 2; i++)
	//			for (size_t j = 0; j <= n / 2; j++)
	//				result[i][j] = m[i][j];
	//		break;
	//	}
	//	case 2: {
	//		for (size_t i = n / 2; i <= n; i++)
	//			for (size_t j = 0; j <= n / 2; j++)
	//				result[i - n / 2][j] = m[i][j];
	//		break;
	//	}
	//	case 3: {
	//		for (size_t i = 0; i <= n / 2; i++)
	//			for (size_t j = n / 2; j <= n; j++)
	//				result[i][j - n / 2] = m[i][j];
	//		break;
	//	}
	//	case 4: {
	//		for (size_t i = n / 2; i <= n; i++)
	//			for (size_t j = n / 2; j <= n; j++)
	//				result[i - n / 2][j - n / 2] = m[i][j];
	//		break;
	//	}
	//	default: throw 0;
	//	}
	//	return result;
	//}
	//template<size_t n, size_t m, sze_t k>
	//int* Shtrassen(int left[n][m],  right[m][k]) {
	//	
	//} 
	//template<size_t n>
	//int* Strassen(int left[n][n], right[n][n]) {
	//	if (n <= 6)
	//		return *(left * right);
	//	
	//	int* A = getSubMatrix(left, 1);
	//	int* B = getSubMatrix(left, 2);
	//	int* C = getSubMatrix(left, 3);
	//	int* D = getSubMatrix(left, 4);
	//	int* E = getSubMatrix(right, 1);
	//	int* F = getSubMatrix(right, 2);
	//	int* G = getSubMatrix(right, 3);
	//	int* H = getSubMatrix(right, 4);
	//
	//	int* p1 = A * (F - H); 
	//	int* p2 = H * (A + B);
	//	int* p3 = E * (C + D);
	//	int* p4 = D * (G - E);
	//	int* p5 = (A + D) * (E + H);
	//	int* p6 = (B - D) * (G + H);
	//	int* p7 = (A - C) * (E + F);
	//}	
}