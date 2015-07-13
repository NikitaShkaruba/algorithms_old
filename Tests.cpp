#include "Algorithms.h"
#include <iostream>
#include <cassert> 
#include <time.h>
#include <string>
#include <fstream>
using namespace algo;

namespace polygon {
	int* GenerateRandomArray(size_t size) {
		srand(time(0));

		int* arr = new int[size];
		for (size_t i = 0; i < size; i++)
			arr[i] = rand();

		return arr;
	}
	void printArray(int* arr, size_t size) {
		for (size_t i = 0; i < size; i++)
			std::cout << i << ") " << arr[i] << std::endl;
	}
	bool isSorted(int* arr, size_t size) {
		for (size_t i = 0; i < size; i++)
			if (arr[i] < arr[i - 1])
				return false;
		return true;
	}

	void RunSortTests() {
		int* (*sorts[])(int*, size_t) = { SelectionSort, InsertionSort, BubbleSort, MergeSort };
		size_t elementsCount = 512;
		
		for (size_t i = 0; i < 4; i++) {
			int* arr = GenerateRandomArray(elementsCount);

			arr = sorts[i](arr, elementsCount);
			assert(isSorted(arr, elementsCount));

			delete[] arr;
		}
	}
	void RunCountInversionsTest() {
		int arr[] { 1, 2, 3, 4, 5 };
		assert(CountInversions(arr, 5) == 0);

		int arr2[] = { 1, 2, 5, 4, 3 }; // 5&4, 5&3, 4&3
		assert(CountInversions(arr2, 5) == 3);

		std::ifstream file("IntegerArray.txt");
		std::string buf;
		int* integers = new int[100000];
		int i = 0;
		while (getline(file, buf))
			integers[i++] = stoi(buf);
		// Stanford homework #1
		assert(CountInversions(integers, 100000) == 2407905288);
		delete integers;
	}
}