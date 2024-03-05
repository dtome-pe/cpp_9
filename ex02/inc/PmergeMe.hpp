#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <iostream>

class PmergeMe
{
	private:
		std::vector<int>					_auxVec;
		std::vector<std::pair<int, int> >	_pairVec;
		std::vector<int>					_sortedVec;

		std::deque<int>						_auxDeque;
		std::deque<std::pair<int, int> >	_pairDeque;
		std::deque<int>						_sortedDeque;
	public:
		PmergeMe(std::string argv);
		PmergeMe(PmergeMe &copy);
		PmergeMe& operator=(const PmergeMe &instance);
		~PmergeMe();

		/*vector*/
		void	generatePairsVec();

		void	print();

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
};

#endif