#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	//std::cout << "PmergeMe constructor has been called." << std::endl;
}

PmergeMe::~PmergeMe()
{
	//std::cout << "PmergeMe destructor has been called." << std::endl;
}

void PmergeMe::sort(char **sequence)
{
	sortVector(sequence);
}

void PmergeMe::sortVector(char **sequence)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> startParse = std::chrono::high_resolution_clock::now();
	std::vector<int>* vSequence = parseToVector(sequence);
	std::chrono::time_point<std::chrono::high_resolution_clock> endParse = std::chrono::high_resolution_clock::now();

	if (vSequence == nullptr)
	{
		return;
	}

	std::cout << "Before: ";
	printVector(*vSequence);

	std::chrono::time_point<std::chrono::high_resolution_clock> startSort = std::chrono::high_resolution_clock::now();
	fordJohnsonSort(*vSequence);
	std::chrono::time_point<std::chrono::high_resolution_clock> endSort = std::chrono::high_resolution_clock::now();

	std::cout << "After: ";
	printVector(*vSequence);

	std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endParse - startParse + endSort - startSort);
	std::cout << "Time to process a range of " << vSequence->size() << " elements with std::vector: " << (double)duration.count() / 1000 << " us" << std::endl;

}

void PmergeMe::fordJohnsonSort(std::vector<int>& vec) 
{
	int n = vec.size();
	if (n <= 1) return;

	std::vector<std::pair<int, int>> pairs;

	for (int i = 0; i < n - 1; i += 2) 
	{
		if (vec[i] > vec[i + 1]) 
		{
			pairs.push_back({vec[i + 1], vec[i]});
		} 
		else 
		{
			pairs.push_back({vec[i], vec[i + 1]});
		}
	}

	int straggler = (n % 2 == 1) ? vec[n - 1] : -1;

	std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {return p1.second < p2.second;});

	std::vector<int> sortedVector;
	for (std::pair<int,int>& p : pairs) 
	{
		sortedVector.push_back(p.second);
	}

	for (std::pair<int,int>& p : pairs) 
	{
		binaryInsertion(sortedVector, p.first);
	}

	if (straggler != -1) 
	{
		binaryInsertion(sortedVector, straggler);
	}

	for (int i = 0; i < n; i++) 
	{
		vec[i] = sortedVector[i];
	}
}

void PmergeMe::binaryInsertion(std::vector<int>& sortedVector, int element) 
{
	int left = 0, right = sortedVector.size() - 1;
	while (left <= right) 
	{
		int mid = (left + right) / 2;
		if (sortedVector[mid] > element) 
		{
			right = mid - 1;
		} 
		else 
		{
			left = mid + 1;
		}
	}
	sortedVector.insert(sortedVector.begin() + left, element);
}

std::vector<int>* PmergeMe::parseToVector(char** sequence)
{
	std::vector<int>* vSequence = new std::vector<int>;

	while (*sequence != nullptr)
	{
		try
		{
			std::string number(*sequence);
			int n = stoi(number);
			if (n < 0)
			{
				delete vSequence;
				std::cerr << "Error: Not a positive number." << std::endl;
				return nullptr;
			}
			vSequence->push_back(n);
		}
		catch(const std::exception& e)
		{
			delete vSequence;
			std::cerr << "Error: Not an integer." << std::endl;
			return nullptr;
		}
		sequence++;
	}

	return vSequence;
}

void PmergeMe::printVector(std::vector<int>& sequence)
{
	for (std::vector<int>::iterator it = sequence.begin(); it != sequence.end(); ++it) 
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
