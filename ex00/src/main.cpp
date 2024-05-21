#include "../inc/BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	try
	{	
		if (argc != 2)
			throw BitcoinExchange::WrongArgumentsException();
		BitcoinExchange a;

		a.calculate(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
