#include <iostream>
#include <string>
#include <vector>
#include "PmergeMe.hpp"

bool isPositiveInteger(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; ++i) {
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <positive integers>\n";
		return 1;
	}

	std::vector<int> values;
	for (int i = 1; i < argc; ++i) {
		if (isPositiveInteger(argv[i])) {
			values.push_back(std::atoi(argv[i]));
		} else {
			std::cerr << "Error: '" << argv[i] << "' is not a positive integer.\n";
			return 1;
		}
	}

	PmergeMe sorter(values);
	sorter.merge();
	return 0;
}