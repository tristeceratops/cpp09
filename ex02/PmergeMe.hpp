#pragma once

#include <string>
#include <vector>
#include <deque>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>

class PmergeMe
{
	private:		
		std::vector<int> _vector;
		std::vector<int> _vector2;
		std::deque<int> _deque;
		std::deque<int> _deque2;
	public:
		PmergeMe();
		PmergeMe(const std::vector<int> &vector);
		PmergeMe(const std::vector<int> &vector, const std::deque<int> &deque);
		PmergeMe(const std::deque<int> &deque);
		PmergeMe(const PmergeMe &copy);

		~PmergeMe();

		PmergeMe &operator=(const PmergeMe &rhs);

		void setVector(const std::vector<int> &list);
		void setDeque(const std::deque<int> &list);

		void merge();
};	
