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
	{	
		_csv.insert(std::pair<std::string, float>(line.substr(0, line.find(",")),
		std::atof(line.substr(line.find(",") + 1).c_str())));
	}

	//printDatabase(_csv);
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
	if (std::atof(value.c_str()) < 0 || std::atof(value.c_str()) > 1000)
		return (false);
	else
		return (true);
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
		throw BitcoinExchange::WrongYearException();
	year = static_cast<int>(std::atof(field.c_str()));
	getline(ss, field, '-');
	month = static_cast<int>(std::atof(field.c_str()));
	field = date.substr(date.find_last_of('-') + 1, date.length());
	day = static_cast<int>(std::atof(field.c_str()));
	
	if(day < 1 || day > 31) 	
        throw BitcoinExchange::WrongDayException();
	else if(month < 1 || month > 12) 
    	throw BitcoinExchange::WrongMonthException();
	else if (year < 2009 || year > 2024)
        throw BitcoinExchange::WrongYearException();
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
        throw BitcoinExchange::WrongDayException(); 
    else if ((month == 2) && (year % 4 == 0) && day > 29)
        throw BitcoinExchange::WrongDayException();
    else if ((month == 2) && (year % 4 != 0) && day > 28)
        throw BitcoinExchange::WrongDayException(); 
    return true;
}

static bool	checkLine(const std::string &line)
{	
	if (line.find("|") == std::string::npos)
		throw BitcoinExchange::WrongFormatException();
	std::string date = line.substr(0, line.find("|") - 1);
	checkDate(date);
	std::string value = line.substr(line.find("|") + 2);
	if (!checkValue(value))
		return (false);
	else
		return (true);
}


void BitcoinExchange::bounceDatabase(std::string argv)
{
	std::ifstream db(argv.c_str());
	if (!db.is_open())
		throw BitcoinExchange::FileNotOpenException();
	std::string	line;
	std::getline(db, line);
	while (std::getline(db, line))
	{	
		if (checkLine(line))
			_db.insert(std::pair<std::string, float>(line.substr(0, line.find("|") - 1),
			std::atof(line.substr(line.find("|") + 2).c_str())));
	}
	//printDatabase(_db);
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

const char*BitcoinExchange::WrongFormatException::what(void) const throw()
{
	return ("Wrong format in provided database");
};

const char*BitcoinExchange::WrongYearException::what(void) const throw()
{
	return ("Invalid year value or year not entered in a correct format (YYYY-mm-dd) (From 2009 to 2024)");
};

const char*BitcoinExchange::WrongMonthException::what(void) const throw()
{
	return ("Invalid month value");
};

const char*BitcoinExchange::WrongDayException::what(void) const throw()
{
	return ("Invalid day value");
};