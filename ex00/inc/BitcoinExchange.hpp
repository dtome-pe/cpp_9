#include <string>
#include <vector>
#include <map>
#include <iostream>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange &copy);
		BitcoinExchange& operator=(const BitcoinExchange &instance);
		~BitcoinExchange();

		void	calculate(std::string argv);

		void	printCsv();

		class 	WrongArgumentsException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class 	FileNotOpenException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
	
	private:
		std::multimap<std::string, float>_csv;
};