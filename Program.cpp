#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "DataStructures.h"
#include "Algorithms.h"
#include "Tests.h"
using namespace std;

void main() {
	//polygon::RunGraphTests();
	polygon::RunSortTests();
	polygon::RunRedBlackTreeTests();
	polygon::RunCountInversionsTests();
	std::cout << "Fine, All works properly. Press any key to continue...";
}