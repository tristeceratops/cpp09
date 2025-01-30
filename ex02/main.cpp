#include <iostream>
#include <string>
#include <vector>
#include <deque>
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
	struct timeval start, end;
	gettimeofday(&start, NULL);

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <positive integers>\n";
		return 1;
	}

	std::vector<int> v_values;
	// std::deque<int> d_values;
	for (int i = 1; i < argc; ++i) {
		if (isPositiveInteger(argv[i])) {
			v_values.push_back(std::atoi(argv[i]));
			// d_values.push_back(std::atoi(argv[i]));
		} else {
			std::cerr << "Error: '" << argv[i] << "' is not a positive integer.\n";
			return 1;
		}
	}
	std::vector<int> before = v_values;
	gettimeofday(&end, NULL);
	double timeVector = PmergeMe::sortVector(v_values);
	// double timeDeque = PmergeMe::sortDeque(d_values);

	//add timeVector with diff end and start
	//add timeDeque with diff end and start
	//print timeVector and timeDeque

	double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
	timeVector += time;
	// timeDeque += time;

	return 0;
}