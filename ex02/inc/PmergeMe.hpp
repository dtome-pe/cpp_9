#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <ctime>
# include <iomanip>
# include <sys/time.h>
# include <sstream>


class PmergeMe
{
	private:

		std::vector<unsigned int>							_beforeVec;

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

		double												_timeVec;
		double												_timeDeque;
		unsigned int										_straggler;

	public:
		PmergeMe(char *argv[]);
		PmergeMe(PmergeMe &copy);
		PmergeMe& operator=(const PmergeMe &instance);
		~PmergeMe();

		void			run(char *argv[]);
		
		void			sortVec(char *argv[]);
		void			sortDeque(char *argv[]);

		template <typename Container> void print(const Container& cont)
		{
			typename Container::const_iterator it; 
			std::cout << "[ ";
			for (it = cont.begin(); it != cont.end(); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << "]";
			std::cout << std::endl;
		}

		template <typename Container> void addToContainer(Container& cont, char *argv[])
		{
			for (unsigned int i = 1; argv[i]; i++)
			{
				std::string str(argv[i]);
				unsigned int x = 0;
				std::stringstream number(str);
				number >> x;
				cont.push_back(x);
			}
		}

		unsigned int	getNumbers();
		double			getTimeVec();
		double			getTimeDeque();

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
		class 	TooManyNumbersException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif