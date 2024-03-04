#include "../inc/RPN.hpp"
#include <iostream>

RPN::RPN()
{

}


RPN::RPN(RPN &copy)
{

}

RPN& RPN::operator=(const RPN &instance)
{

}

RPN::~RPN()
{
	delete _l;
}
