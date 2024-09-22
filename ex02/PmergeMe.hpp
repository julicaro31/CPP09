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
	
	private:

		// VECTOR
		void sortVector(char** sequence);
		void fordJohnsonSort(std::vector<int>& sequence);
		void binaryInsertion(std::vector<int>& sortedVector, int element);
		
		std::vector<int>* parseToVector(char** sequence);
		void printVector(std::vector<int>& sequence);


		// LIST
		void sortList(char** sequence);
		void fordJohnsonSort(std::list<int>& sequence);
		void binaryInsertion(std::list<int>& sortedList, int element);
		
		std::list<int>* parseToList(char** sequence);
		void printList(std::list<int>& sequence);
};

#endif