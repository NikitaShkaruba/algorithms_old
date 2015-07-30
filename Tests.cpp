#include "DataStructures.h"
#include "Algorithms.h"
#include "Tests.h"
#include <iostream>
#include <cassert> 
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
using namespace algo;

namespace polygon {
	int* GenerateRandomArray(size_t size) {
		int* arr = new int[size];

		for (size_t i = 0; i < size; i++)
			arr[i] = rand();

		return arr;
	}
	void printArray(int* arr, size_t size) {
		std::cout << "Array:" << std::endl;
		for (size_t i = 0; i < size; i++)
			std::cout << i << ") " << arr[i] << std::endl;
	}
	bool isSorted(int* arr, size_t size) {
		for (size_t i = 0; i < size; i++)
			if (arr[i] < arr[i - 1])
				return false;
		return true;
	}
	//Graph getGraph(string filename) {
	//	ifstream input(fileName);
	//	Node* nodes = new Node[200];
	//	Edge* edges = new Edge[200];
	//	size_t i = 0;
	//	string line;
	//
	//	while (getline(input, line)) {
	//		istringstream iss(line);
	//		int i, j;
	//
	//		iss >> i; // first one
	//		while (iss >> j) {
	//			if (!nodes[i-1].isConnected(nodes + j-1)) {
	//				nodes[i-1].attach(nodes + j-1);
	//				// what to do, mate?? I need edges
	//			}
	//		}
	//	}
	//
	//	return Graph(nodes+1, 20);
	//}	
	//int* getArray(string name, size_t size) {
	//	ifstream file(name);
	//	int* arr = new int[size], i = 0;
	//	for(size_t i = 0; i < size; i++)
	//		 file >> arr[i];
	//
	//	file.close();
	//	return arr;
	//}

	void RunSortTests() {
		void(*sorts[])(int*, size_t) = { SelectionSort, InsertionSort, BubbleSort, MergeSort, QuickSort };
		size_t elementsCount = 10;

		for (size_t i = 0; i < 5; i++) {
			for (int j = 0; j < 50; j++) {
				int* arr = GenerateRandomArray(elementsCount);

				sorts[i](arr, elementsCount);
				assert(isSorted(arr, elementsCount));

				delete[] arr;
			}
		}
	}
	void RunCountInversionsTests() {
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
	void RunRedBlackTreeTests() {
		for (size_t i = 0; i < 11; i++) {
			size_t size = 7 + i;
			int* arr = new int[(int)pow(2, size)];
			for (size_t j = 0; j < size; j++)
				arr[j] = rand();
			RedBlackTree tree(arr, size);
			
			tree.inTraversal([](RedBlackTree* node) {
				assert(node->isBinaryTree());
			});
		}
	}
	//void RunGraphTests() {
	//	Graph test = getGraph("Graph.txt");
	//	
	//}
}