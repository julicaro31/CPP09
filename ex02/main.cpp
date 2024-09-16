#include "PmergeMe.hpp"

int main(int ac, char *argv[])
{
	if (ac < 2)
	{
		return 0;
	}
	
	PmergeMe pmm;
	pmm.sort(argv + 1);
}