#include "DataStructures.cpp"
#include "Algorithms.h"
#include <iostream>
#include <fstream>
#include "Tests.h"
using namespace std;

int* getArray(string name, size_t size) {
	ifstream file(name);
	int* arr = new int[size], i = 0;
	for(size_t i = 0; i < size; i++)
		 file >> arr[i];
	
	file.close();
	return arr;
}
void getGraph(string name) {
	ifstream input(name);

}
void main() {

	polygon::RunSortTests();
	polygon::RunRedBlackTreeTests();
	polygon::RunCountInversionsTests();
	std::cout << "Fine, All works properly. Press any key to continue...";
}