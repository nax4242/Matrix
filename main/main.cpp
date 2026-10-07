#include "vector.h"
#include <iostream>
#include <vector>

int main() {
	std::vector<int> stdvec(10);
	
	int val = 1;

	for (auto it = stdvec.begin(); it != stdvec.end(); it++) {
		*it = val++;
	}

	for (auto it = stdvec.begin(); it != stdvec.end(); it++) {
		std::cout << *it << std::endl;
	}


	return 0;
}