#pragma once

#include <string>
#include <vector>
#include <deque>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <cmath>

class PmergeMe
{
	private:		
		PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe &operator=(const PmergeMe &rhs);
	public:

		~PmergeMe();
		static double sortVector(std::vector<int> &vector);
		static double sortDeque(std::deque<int> &vector);
};
