#include "Algorithms.h"
#include "DataStructures.cpp"
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
	int& getMax(int* arr, size_t size) {
		int max = arr[0];
		for (size_t i = 1; i < size; i++)
			if (arr[i] > max)
				max = arr[i];
		return max;
	}

	// Sorts
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
		if (size == 1)
			return;

		MergeSort(arr, size/2);				
		MergeSort(arr + size/2, size - size/2);

		int l = 0, r = size/2;	// left and right indexes respectively
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
		// Complexity T(n) = O(n*log(n))
		if (size <= 1)
			return;

		// amazing not naive partition implementation
		int key = rand() % size, i = 1; // i points on pivot element 
		swap(arr[0], arr[key]);			
		for (size_t j = 1; j < size; j++) { // j points on unsorted element
			if (arr[j] < arr[0])
				swap(arr[i++], arr[j]);
		}
		swap(arr[0], arr[i-1]);

		QuickSort(arr, i-1);
		QuickSort(arr + i, size - i);
	}
	void HeapSort(int* arr, size_t size) {
		Heap heap(arr, size);
		for(size_t i = 0; i < size; i++)
			arr[i] = heap.pop();
	}
	void BucketSort(int* arr, size_t size) {
		int max = getMax(arr, size);
		List<int>* buckets = new List<int>[(int)log10(max)];
		
		for(size_t i = 0; i < size; i++)
			buckets[(int)log10(arr[i])].insert(arr[i]);
		for(size_t i = 0; i < (int)log10(max); i++) {
			MergeSort(buckets[i].getArray(), buckets[i].getSize());
			for(size_t j = 0; j < buckets[i].getSize(); j++)
				arr[i] = buckets[i][j];
		}
	}
	void CountingSort(int* arr, size_t size) {
		int* count = new int[sizeof(int)];
		for(size_t i = 0; i < size; i++)
			count[arr[i]]++;

		for(size_t i = 0, j = 0; j < size; i++) {
			if (count[i] != 0) {
				arr[j++] = i;
				count[i]--;
			}
		}
	}
	void RadixSort(int* arr, size_t size) {
		int max = getMax(arr, size);
		int* output = new int[size];
		for (size_t exp = 0; max/exp > 0; exp *= 10) {
			int i, count[10] = {0};
			for (i = 0; i < size; i++)
				count[(arr[i] / exp) % 10]++;
			for (i = 1; i < 10; i++)
				count[i] += count[i - 1];
			
			for (i = size - 1; i >= 0; i--) {
				output[count[(arr[i] / exp) % 10] - 1] = arr[i];
				count[(arr[i] / exp) % 10]--;
			}
			for (i = 0; i < size; i++)
				arr[i] = output[i];
		}
		delete output;
	}

	// Selection problems
	int& RanomizedSelect(int* arr, size_t size, size_t k) {
		// Complexity O(n) 
		// It's a little messy to write it in c++, so give here only COPIES of the array real
		if (size == 1)
			return arr[0];

		int key = rand() % size, i = 1; // i points on pivot element 
		swap(arr[0], arr[key]);			
		for (size_t j = 1; j < size; j++) { // j points on unsorted element
			if (arr[j] < arr[0])
				swap(arr[i++], arr[j]);
		}
		swap(arr[0], arr[i-1]);

		if (k < i)
			return RanomizedSelect(arr, i-1, k);  
		if (k > i)
			return RanomizedSelect(arr + i, size - i, k - i);
		if (i == k)
			return arr[i];
	}
	int& DeterminedSelect(int* arr, size_t size, size_t k) {
		// Complexity O(n) 
		// It's a little messy to write it in c++, so give here only COPIES of the array real
		if (size == 1)
			return arr[0];
		
		int* buf = new int[size];
		int* medians = new int[size/5];
		for(size_t i = 0; i < size; size++) {
			buf[i] = arr[i];
			if (i % 5 == 0) {
				MergeSort(arr + i, 5);
				medians[i/5] = arr[i + 2];
			}
		}
		int key = DeterminedSelect(medians, size/5, size/10);
		delete buf;
		delete medians;
		int i = 1; // i points on pivot element 
		
		swap(arr[0], arr[key]);			
		for (size_t j = 1; j < size; j++) { // j points on unsorted element
			if (arr[j] < arr[0])
				swap(arr[i++], arr[j]);
		}
		swap(arr[0], arr[i-1]);

		if (k < i)
			return RanomizedSelect(arr, i-1, k);  
		if (k > i)
			return RanomizedSelect(arr + i, size - i, k - i);
		if (i == k)
			return arr[i];
	}
	
	// Count Inversions problem
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
	// Just handy enter point for user. Look up inside CountInversionsSort(...) which place is down below
		size_t counter = 0;
		int* buffer = new int[size];
		std::copy(arr, &arr[size], buffer);
		
		CountInversionsSort(buffer, size, counter);
		
		delete buffer;
		return counter;
	}
	
	// Get closest pair problem
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

		std::sort(X, &X[size], [](point a, point b) { return a.first < b.first; });
		std::sort(Y, &Y[size], [](point a, point b) { return a.second < b.second; });

		point* result = GetClosestPair(X, Y, size);
		for (size_t i = 0; i < size; i++) {
			if (arr[i].first == result[i].first && arr[i].second == result[i].second) {
				delete X;
				delete Y;
				delete result;
				return &arr[i];
			}
		}
		return nullptr;
	}

	// Graph problems
	Graph KargerMinCut(Graph graph) {
		// Complexity: O(m*n^2)
		size_t n = graph.getEdgesCount();
		Graph best(graph);

		for (size_t i = 0; i < pow(n, 2)*log(n); i++) { //
			Graph copy = graph;
			Edge* edges = copy.getEdges();

			while (copy.getNodesCount() != 2) {
				size_t i = rand() / copy.getEdgesCount();
				Edge* chosen = edges + i;

				chosen->fuse();
				for(auto i = edges)
			}

			if (copy.getEdgesCount() < best.getEdgesCount()) {
			}
		}
		return best;
	}
}