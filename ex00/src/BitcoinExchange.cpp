#include <fstream>
#include <exception>
#include <cstdlib>
#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::ifstream csv("data.csv");
	if (!csv.is_open())
		throw BitcoinExchange::FileNotOpenException();
	std::string	line;
	std::getline(csv, line);
	while (std::getline(csv, line))
	{	
		_csv.insert(std::pair<std::string, float>(line.substr(0, line.find(",")), std::atof(line.substr(line.find(",") + 1).c_str())));
	}

	printDatabase(_csv);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &copy)
{
	(void) copy;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &instance)
{
	(void) instance;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

void BitcoinExchange::bounceDatabase(std::string argv)
{
	std::ifstream db(argv.c_str());
	if (!db.is_open())
		throw BitcoinExchange::FileNotOpenException();
}

void BitcoinExchange::printDatabase(std::multimap<std::string, float> &db)
{
	for (std::multimap<std::string, float>::iterator it = db.begin(); it != db.end(); it++)
	{
		std::cout << "key: " << it->first << " value: " << it->second << std::endl;
	}
}

const char*BitcoinExchange::WrongArgumentsException::what(void) const throw()
{
	return ("Wrong number of arguments");
};

const char*BitcoinExchange::FileNotOpenException::what(void) const throw()
{
	return ("File could not be opened or found");
};