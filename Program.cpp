#include "Algorithms.h"
#include "DataStructures.h"
#include <iostream>
#include "Tests.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void main() {
	polygon::RunSortTests();
	polygon::RunCountInversionsTest();
	
	std::cout << "Fine, All works properly. Press any key to continue...";
}