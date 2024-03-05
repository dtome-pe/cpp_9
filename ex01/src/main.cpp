#include "../inc/RPN.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{	
	try
	{
		if (argc != 2)
			throw RPN::WrongArgumentsException();

		RPN a;

		a.calculate(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}