#ifndef __RNP_H__
#define __RNP_H__

#include <iostream>
#include <stack>
#include <string>
#include <sstream>

class RPN
{
	public:

		RPN();
		~RPN();
		RPN(const RPN& rpn) = delete;
		RPN& operator=(const RPN& rpn) = delete;

		void solve(std::string expression);

	private:

		bool isValidNumber(char c);
		bool isValidOperator(char c);
	
};

#endif