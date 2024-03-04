#include <string>
#include <vector>
#include <set>
#include <iostream>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange &copy);
		BitcoinExchange& operator=(const BitcoinExchange &instance);
		~BitcoinExchange();

		void	bounceDatabase(std::string argv);
		void	calculate();

		void	printCsv();
		void 	printDb();

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
		std::multiset<std::string>_csv;
		std::vector<std::string>_db;
};