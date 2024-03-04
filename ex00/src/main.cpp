#include "../inc/BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	try
	{	
		if (argc != 2)
			throw BitcoinExchange::WrongArgumentsException();
		BitcoinExchange a;

		a.bounceDatabase(argv[1]);
		a.calculate();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}