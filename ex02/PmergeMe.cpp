#include "PmergeMe.hpp"

void merge(std::vector<int>& arr, int start, int mid, int end)
{
	std::vector<int> temp(end - start + 1);
	int i = start, j = mid + 1, k = 0;

	while (i <= mid && j <= end)
	{
		if (arr[i] <= arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}

	while (i <= mid)
		temp[k++] = arr[i++];

	while (j <= end)
		temp[k++] = arr[j++];

	for (int i = start; i <= end; i++)
		arr[i] = temp[i - start];
}

void sortVectorRecursive(std::vector<int> &vector, int start, int end)
{
	if (start >= end)
		return;

	int mid = start + (end - start) / 2;

	sortVectorRecursive(vector, start, mid);
	sortVectorRecursive(vector, mid + 1, end);

	merge(vector, start, mid, end);
}

void sortVector(std::vector<int> &vector)
{
	sortVectorRecursive(vector, 0, vector.size() - 1);
}

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const std::vector<int> &vector): _vector(vector), _vector2(vector) {}

PmergeMe::PmergeMe(const std::vector<int> &vector, const std::deque<int> &deque)
: _vector(vector), _vector2(vector), _deque(deque), _deque2(deque) {}

PmergeMe::PmergeMe(const std::deque<int> &deque): _deque(deque), _deque2(deque) {}

PmergeMe::PmergeMe(const PmergeMe &copy)
: _vector(copy._vector), _vector2(copy._vector2), _deque(copy._deque), _deque2(copy._deque2) {}

PmergeMe::~PmergeMe(){}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	if (this != &rhs)
	{
		_vector = rhs._vector;
		_deque = rhs._deque;
		_vector2 = rhs._vector2;
		_deque2 = rhs._deque2;
	}
	return *this;
}

void PmergeMe::setVector(const std::vector<int> &vector)
{
	_vector = vector;
}

void PmergeMe::setDeque(const std::deque<int> &deque)
{
	_deque = deque;
}

void PmergeMe::merge()
{
	if (_vector.empty() || _deque.empty())
		return;
	
	sortVector(_vector);

	std::cout << "Before: ";
	for (size_t i = 0; i < _vector2.size(); ++i)
		std::cout << _vector2[i] << " ";
	std::cout << std::endl;

	std::cout << "After: ";
	for (size_t i = 0; i < _vector.size(); ++i)
		std::cout << _vector[i] << " ";
	std::cout << std::endl;
}

// void sortDeque(std::deque<int> &deque)
// {
// 	//sort deque
// }