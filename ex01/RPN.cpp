#include "RPN.hpp"

RPN::RPN()
{
	std::cout << "RPN constructor has been called." << std::endl;
}

RPN::~RPN()
{
	std::cout << "RPN destructor has been called." << std::endl;
}

float doOperation(char op, float a, float b)
{
	switch (op)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
		default:
			return 0;
	}
}

void RPN::solve(std::string expression)
{
	std::stack<float> stack;

	std::stringstream ss(expression);
	std::string token;

	while (std::getline(ss, token, ' ')) 
	{
		std::string str(token);
		if (str.length() != 1)
		{
			std::cout << "Error" << std::endl;
			return;
		}
		if (isValidNumber(str[0]))
		{
			stack.push(str[0] - 48);
		}
		else if (isValidOperator(str[0]) && !stack.empty())
		{
			float b = stack.top();
			stack.pop();
			if (stack.empty())
			{
				std::cout << "Error" << std::endl;
				return;
			}
			float a = stack.top();
			stack.pop();
			stack.push(doOperation(str[0], a, b));
		}
		else
		{
			std::cout << "Error" << std::endl;
			return;
		}
	}

	std::cout << stack.top() << std::endl;
	return;
}


bool RPN::isValidNumber(char c)
{
	return c >= '0' && c <= '9';
}

bool RPN::isValidOperator(char c)
{
	return c == '+' || c == '-' || c == '/' || c == '*';
}
