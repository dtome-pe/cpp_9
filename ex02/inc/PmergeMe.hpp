#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <ctime>
# include <iomanip>

class PmergeMe
{
	private:
		std::vector<unsigned int>							_auxVec;
		std::vector<unsigned int>							_pendVec;
		std::vector<std::pair<unsigned int, unsigned int> > _pairVec;
		std::vector<unsigned int>							_mainVec;

		std::deque<unsigned int>							_auxDeque;
		std::deque<unsigned int>							_pendDeque;
		std::deque<std::pair<unsigned int, unsigned int> >	_pairDeque;
		std::deque<unsigned int>							_mainDeque;

		size_t												_n;
		bool												_odd;

	public:
		PmergeMe(std::string argv);
		PmergeMe(PmergeMe &copy);
		PmergeMe& operator=(const PmergeMe &instance);
		~PmergeMe();

		/*vector*/
		void	sortVec();

		void	sortDeque();

		void	printAux();
		void	printPend();
		void	printPairs();
		void	printMain();

		class 	WrongArgumentsException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class 	ArgumentErrorException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class 	DuplicateErrorException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif