#include "DataStructures.cpp"
#include "Algorithms.h"
#include <iostream>
#include <fstream>
#include "Tests.h"

void main() {
	polygon::RunGraphTests();
	polygon::RunSortTests();
	polygon::RunRedBlackTreeTests();
	polygon::RunCountInversionsTests();
	std::cout << "Fine, All works properly. Press any key to continue...";
}