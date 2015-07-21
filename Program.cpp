#include "DataStructures.cpp"
#include "Algorithms.h"
#include <iostream>
#include "Tests.h"
#include <fstream>
#include <string>
#include <assert.h>
#include <vector>
using namespace std;


void main() {
	polygon::RunRedBlackTreeTests();
	polygon::RunSortTests();
	polygon::RunCountInversionsTests();

	std::cout << "Fine, All works properly. Press any key to continue...";
}
