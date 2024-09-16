#include "RPN.hpp"

int main(int ac, char *argv[])
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return -1;
	}

	RPN rpn;

	rpn.solve(argv[1]);
	return 0;
}