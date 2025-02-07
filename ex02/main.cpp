#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "PmergeMe.hpp"

bool isPositiveInteger(const char* str)
{
	if (!str || *str == '\0')
		return false;
	for (size_t i = 0; str[i] != '\0'; ++i) {
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}	

int main(int argc, char* argv[])
{
	struct timeval start, end;
	double time_v, time_d;
	gettimeofday(&start, NULL);

	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <positive integers>\n";
		return 1;
	}

	std::vector<int> v_values;
	std::deque<int> d_values;
	for (int i = 1; i < argc; ++i) {
		if (isPositiveInteger(argv[i])) {
			v_values.push_back(std::atoi(argv[i]));
			d_values.push_back(std::atoi(argv[i]));
		} else {
			std::cerr << "Error: '" << argv[i] << "' is not a positive integer.\n";
			return 1;
		}
	}
	std::deque<int> before = d_values;
	gettimeofday(&end, NULL);

	time_v = PmergeMe::sortVector(v_values);
	time_d = PmergeMe::sortDeque(d_values);

	time_v += end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
	time_d += end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
	std::cout << "Before: ";
	for (size_t i = 0; i < before.size(); ++i) {
		std::cout << before[i] << " ";
	}
	std::cout << std::endl << "After: ";
	for (size_t i = 0; i < d_values.size(); ++i) {
		std::cout << d_values[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << v_values.size() << " with std::vector: " << time_v << " seconds\n";
	std::cout << "Time to process a range of " << d_values.size() << " with std::deque: " << time_d << " seconds\n";

	return 0;
}