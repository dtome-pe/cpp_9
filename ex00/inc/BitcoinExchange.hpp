#include <string>
#include <map>
#include <iostream>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange &copy);
		BitcoinExchange& operator=(const BitcoinExchange &instance);
		~BitcoinExchange();

		void bounceDatabase(std::string argv);

		void printDatabase(std::multimap<std::string, float> &db);

		class WrongArgumentsException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class FileNotOpenException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class WrongFormatException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class WrongYearException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class WrongMonthException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class WrongDayException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
	
	
	private:
		std::multimap<std::string, float>_csv;
		std::multimap<std::string, float>_db;
};