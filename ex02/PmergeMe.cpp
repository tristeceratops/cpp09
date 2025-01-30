#include "PmergeMe.hpp"
PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &copy){}

PmergeMe::~PmergeMe(){}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {return *this;}
///////////////
int jacobsthalNumber(int k)
{
	return (pow(2, k+1) + pow(-1, k))/3;
}

std::vector<std::pair<int, int>> createPairs(std::vector<int> &vector)
{
	std::vector<std::pair<int, int>> pairs;
	for (size_t i = 0; i < vector.size(); i += 2)
	{
		if (i + 1 < vector.size())
			pairs.push_back(std::make_pair(vector[i], vector[i + 1]));
		else
			pairs.push_back(std::make_pair(vector[i], -1));
	}
	return pairs;
}

void extractSequence(std::vector<std::pair<int, int>>  &pairs, std::vector<int> &main, std::vector<int> &pend, int &odd)
{
	for (size_t i = 0; i < pairs.size(); i++)
	{
		if (pairs[i].second == -1)
		{
			main.push_back(pairs[i].first);
		}
		else if (pairs[i].first < pairs[i].second)
		{
			main.push_back(pairs[i].first);
			pend.push_back(pairs[i].second);
		}
		else
		{
			main.push_back(pairs[i].second);
			pend.push_back(pairs[i].first);
		}
	}

	odd = -1;
	if (main.size() % 2 != 0)
	{
		odd = main[main.size() - 1];
		main.pop_back();
	}
}

void insertPend(std::vector<int> &main, std::vector<int> &pend)
{
	int jacobN = jacobsthalNumber(0);
	std::vector<bool> inserted(pend.size(), false);

	while ()


}

void insertInOrder(std::vector<int> &main, int value) //trie dichotomique
{
}

double PmergeMe::sortVector(std::vector<int> &vector)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	if (vector.size() <= 1)
	{
		gettimeofday(&end, NULL);
		double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
		return time;
	}

	std::vector<std::pair<int, int>> pairs = createPairs(vector);

	gettimeofday(&end, NULL);
	double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
	return time;
}

// double PmergeMe::sortDeque(std::deque<int> &vector)
// {
// 	struct timeval start, end;
// 	gettimeofday(&start, NULL);
	
// 	//sort deque

// 	gettimeofday(&end, NULL);
// 	double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
// 	return time;
// }
