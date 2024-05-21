#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <iostream>

class BitcoinExchange
{
	private:
		std::map<std::string, float>_csv;

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
};

#endif
