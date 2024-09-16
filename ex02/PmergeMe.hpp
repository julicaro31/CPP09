#ifndef __PMERGE_ME_H__
#define __PMERGE_ME_H__

#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>

class PmergeMe
{
    public:

		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& pmergeMe) = delete;
		PmergeMe& operator=(const PmergeMe& pmergeMe) = delete;

		void sort(char** sequence);
		void sortVector(char** sequence);
	
	private:

		// VECTOR
		void fordJohnsonSort(std::vector<int>& sequence);
		void binaryInsertion(std::vector<int>& sortedVector, int element);
		
		std::vector<int>* parseToVector(char** sequence);
		void printVector(std::vector<int>& sequence);


		// LIST
};

#endif