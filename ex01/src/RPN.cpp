#include "../inc/RPN.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

RPN::RPN()
{

}


RPN::RPN(RPN &copy)
{
	_exp = copy._exp;
}

RPN& RPN::operator=(const RPN &instance)
{
	_exp = instance._exp;
	return (*this);
}

RPN::~RPN()
{

}

static bool isDigits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}
static bool isToken(const std::string &str)
{	
	if (str.length() > 1)
		return (false);
	return str.find_first_not_of("+-*/") == std::string::npos;
}

static void error()
{	
	std::cout << "Error" << std::endl;
	return ;
}

static int	getOperator(std::string &op)
{
	if (op == "+")
		return (ADDITION);
	else if (op == "-")
		return (SUBSTRACTION);
	else if (op == "*")
		return (MULTIPLICATION);
	else
		return (DIVISION);
}

void RPN::calculate(std::string argv)
{	
	std::stringstream ss(argv);
	std::string str;

	ss >> std::ws;
	while (getline(ss, str, ' '))
	{
		if (isDigits(str))
			_exp.push(std::atof(str.c_str()));
		else if (isToken(str) && _exp.size() >= 2)
		{	
			float total;
			float op2 = _exp.top();
			_exp.pop();
			float op1 = _exp.top();
			_exp.pop();
			int op = getOperator(str);
			switch (op)
			{
				case ADDITION:
					total = op1 + op2;
								break;
				case SUBSTRACTION:
					total = op1 - op2;
								break;
				case MULTIPLICATION:
					total = op1 * op2;
								break;
				case DIVISION:
					total = op1 / op2;
								break;
			}
			_exp.push(total);
		}
		else
			return (error());
		ss >> std::ws;
	}
	if (_exp.size() > 1)
		return (error());	
	std::cout << _exp.top() << std::endl;
}

const char* RPN::WrongArgumentsException::what(void) const throw()
{
	return ("Wrong number of arguments");
};