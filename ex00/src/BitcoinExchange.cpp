#include <fstream>
#include <exception>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::ifstream csv("data.csv");
	if (!csv.is_open())
		throw BitcoinExchange::FileNotOpenException();
	std::string	line;
	std::getline(csv, line);
	while (std::getline(csv, line))	
		_csv.insert(std::make_pair(line.substr(0, line.find(",")), std::atof(line.substr(line.find(",") + 1, line.length()).c_str())));
	//printCsv();
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

static bool	checkValue(std::string &value)
{	
	//std::cout << "value is: " << value << std::endl;
	if (std::atof(value.c_str()) < 0)
	{	
		std::cerr << "Error: Negative value. (0 to 1000)" << std::endl;
		return (false);
	}
	else if(std::atof(value.c_str()) > 1000)
	{
		std::cerr << "Error: Value too big. (0 to 1000)" << std::endl;
		return (false);
	}
	else
		return (true);
}

static bool wrongDayValue()
{
	std::cerr << "Error: Wrong day value" << std::endl;
	return false;
}

static bool wrongMonthValue()
{
	std::cerr << "Error: Wrong month value" << std::endl;
	return false;
}

static bool wrongYearValue()
{
	std::cerr << "Error: Wrong year value (Please, specify a year from 2009 to 2024)" << std::endl;
	return false;
}

static bool	checkDate(std::string &date)
{
	std::stringstream 	ss(date);
	std::string			field;
	int					year;
	int					month;
	int					day;

	getline(ss, field, '-');
	if (field.length() != 4)
	{
		std::cerr << "Error: Wrong year length. (YYYY-mm-dd)" << std::endl;
		return (false);
	}
	year = static_cast<int>(std::atof(field.c_str()));
	getline(ss, field, '-');
	month = static_cast<int>(std::atof(field.c_str()));
	field = date.substr(date.find_last_of('-') + 1, date.length());
	day = static_cast<int>(std::atof(field.c_str()));
	
	if(day < 1 || day > 31)
		return (wrongDayValue());
	else if(month < 1 || month > 12) 
    	return (wrongMonthValue());
	else if (year < 2009 || year > 2024)
        return (wrongYearValue());
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
        return (wrongDayValue());
    else if ((month == 2) && (year % 4 == 0) && day > 29)
        return (wrongDayValue());
    else if ((month == 2) && (year % 4 != 0) && day > 28)
        return (wrongDayValue());
    return true;
}

static bool	checkLine(const std::string &line)
{	
	if (line.find("|") == std::string::npos)
	{	
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}
	std::string date = line.substr(0, line.find("|") - 1);
	if (!checkDate(date))
		return false;
	std::string value = line.substr(line.find("|") + 2);
	if (!checkValue(value))
		return (false);
	else
		return (true);
}

void	BitcoinExchange::calculate(std::string argv)
{	
	std::ifstream db(argv.c_str());
	if (!db.is_open())
		throw BitcoinExchange::FileNotOpenException();
	std::string	line;
	std::getline(db, line);
	while (std::getline(db, line))
	{
		if (!checkLine(line))
			continue ;
		std::string date = line.substr(0, line.find('|') - 1);
		float value = std::atof(line.substr(line.find('|') + 1, line.length()).c_str());

		if (_csv.count(date))
		{
			std::multimap<std::string, float>::iterator it = _csv.find(date);
			std::cout << date << " => " << value << " = " << value * it->second << std::endl;
		}
		else
		{
			std::multimap<std::string, float>::iterator it = _csv.lower_bound(date);
			std::cout << date << " => " << value << " = " << value * it->second << std::endl;
		}
	}
}

void	BitcoinExchange::printCsv()
{
	for (std::multimap<std::string, float>::iterator it = _csv.begin(); it != _csv.end(); it++)
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