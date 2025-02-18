#include "PmergeMe.hpp"
PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	(void)copy;
}

PmergeMe::~PmergeMe(){}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
	(void)rhs;
	return *this;
}
///////////////

void insertInOrder(std::deque<int> &main, int value) //trie dichotomique
{
	std::deque<int>::iterator it = std::lower_bound(main.begin(), main.end(), value);
	main.insert(it, value);
}

void insertInOrder(std::vector<int> &main, int value) //trie dichotomique
{
	std::vector<int>::iterator it = std::lower_bound(main.begin(), main.end(), value);
	main.insert(it, value);
}

// int jacobsthalNumber(int k)
// {
// 	return (pow(2, k+1) + pow(-1, k))/3;
// }

std::deque<int> generateJacobsthalIndicesDeque(int size) {
	std::deque<int> indices;
	int j1 = 0, j2 = 1;
	while (j2 < size) {
		indices.push_back(j2);
		int next = j2 + 2 * j1;
		j1 = j2;
		j2 = next;
	}
	return indices;
}

std::vector<int> generateJacobsthalIndicesVector(int size) {
	std::vector<int> indices;
	int j1 = 0, j2 = 1;
	while (j2 < size) {
		indices.push_back(j2);
		int next = j2 + 2 * j1;
		j1 = j2;
		j2 = next;
	}
	return indices;
}

void makePairs(std::deque<int> &deque, std::deque<std::pair<int, int> > &pairs, int &odd)
{
	if (deque.size() % 2 != 0)
		odd = deque.end()[-1];
	for (size_t i = 0; i < deque.size(); i += 2)
	{
		if (i + 1 >= deque.size())
			break;
		if (deque[i] > deque[i + 1])
			pairs.push_back(std::make_pair(deque[i + 1], deque[i]));
		else
			pairs.push_back(std::make_pair(deque[i], deque[i + 1]));
	}
}

void makePairs(std::vector<int> &vector, std::vector<std::pair<int, int> > &pairs, int &odd)
{
	if (vector.size() % 2 != 0)
		odd = vector.end()[-1];
	for (size_t i = 0; i < vector.size(); i += 2)
	{
		if (i + 1 >= vector.size())
			break;
		if (vector[i] > vector[i + 1])
			pairs.push_back(std::make_pair(vector[i + 1], vector[i]));
		else
			pairs.push_back(std::make_pair(vector[i], vector[i + 1]));
	}
}

void splitPairs(std::deque<std::pair<int, int> > &pairs, std::deque<int> &main, std::deque<int> &pend, int odd)
{
	main.clear();
	pend.clear();
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		main.push_back(pairs[i].second);
		pend.push_back(pairs[i].first);
	}
	if (odd != -1)
		pend.push_back(odd);
}

void splitPairs(std::vector<std::pair<int, int> > &pairs, std::vector<int> &main, std::vector<int> &pend, int odd)
{
	main.clear();
	pend.clear();
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		main.push_back(pairs[i].second);
		pend.push_back(pairs[i].first);
	}
	if (odd != -1)
		pend.push_back(odd);
}

void insertPend(std::deque<int> &main, std::deque<int> &pend)
{
	std::deque<int> jacobsthalIndices = generateJacobsthalIndicesDeque(pend.size());
	std::deque<bool> inserted(pend.size(), false);

	for (size_t i = 0; i < jacobsthalIndices.size(); ++i)
	{
		if (inserted[jacobsthalIndices[i]])
			continue;
		insertInOrder(main, pend[jacobsthalIndices[i]]);
		inserted[jacobsthalIndices[i]] = true;
		int pendSize = pend.size();
		if (jacobsthalIndices[i] + 1 < pendSize && !inserted[jacobsthalIndices[i] + 1])
		{
			insertInOrder(main, pend[jacobsthalIndices[i] + 1]);
			inserted[jacobsthalIndices[i] + 1] = true;
		}
	}

	for (size_t i = 0; i < pend.size(); ++i)
	{
		if (!inserted[i])
			insertInOrder(main, pend[i]);
	}
}

void insertPend(std::vector<int> &main, std::vector<int> &pend)
{
	std::vector<int> jacobsthalIndices = generateJacobsthalIndicesVector(pend.size());
	std::vector<bool> inserted(pend.size(), false);

	for (size_t i = 0; i < jacobsthalIndices.size(); ++i)
	{
		if (inserted[jacobsthalIndices[i]])
			continue;
		insertInOrder(main, pend[jacobsthalIndices[i]]);
		inserted[jacobsthalIndices[i]] = true;
		int pendSize = pend.size();
		if (jacobsthalIndices[i] + 1 < pendSize && !inserted[jacobsthalIndices[i] + 1])
		{
			insertInOrder(main, pend[jacobsthalIndices[i] + 1]);
			inserted[jacobsthalIndices[i] + 1] = true;
		}
	}

	for (size_t i = 0; i < pend.size(); ++i)
	{
		if (!inserted[i])
			insertInOrder(main, pend[i]);
	}
}

void recSortMain(std::deque<int> &main)
{
	if (main.size() <= 1) return;

	int odd = -1;
	std::deque<std::pair<int, int> > pairs;
	std::deque<int> pend;

	makePairs(main, pairs, odd);
	splitPairs(pairs, main, pend, odd);
	recSortMain(main);
	insertPend(main, pend);
}

void recSortMain(std::vector<int> &main)
{
	if (main.size() <= 1) return;

	int odd = -1;
	std::vector<std::pair<int, int> > pairs;
	std::vector<int> pend;

	makePairs(main, pairs, odd);
	splitPairs(pairs, main, pend, odd);
	recSortMain(main);
	insertPend(main, pend);
}

double PmergeMe::sortDeque(std::deque<int> &deque)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::deque<int> main, pend;
	std::deque<std::pair<int, int> > pairs;
	int odd = -1;
	makePairs(deque, pairs, odd);
	if (odd != -1)
		pend.push_back(odd);
	splitPairs(pairs, main, pend, odd);
	recSortMain(main);
	insertPend(main, pend);
	gettimeofday(&end, NULL);
	deque = main;
	return end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;

}

double PmergeMe::sortVector(std::vector<int> &vector)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::vector<int> main, pend;
	std::vector<std::pair<int, int> > pairs;
	int odd = -1;
	makePairs(vector, pairs, odd);
	if (odd != -1)
		pend.push_back(odd);
	splitPairs(pairs, main, pend, odd);
	recSortMain(main);
	insertPend(main, pend);
	gettimeofday(&end, NULL);
	vector = main;
	return end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;

}