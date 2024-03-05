#include "../inc/PmergeMe.hpp"
#include <sstream>
#include <limits>

static bool isInt(const std::string &str)
{
	if (!str.find_first_not_of("0123456789"))
		return (false);
	long x = 0;
	std::stringstream number(str);
	number >> x;
	if (x < std::numeric_limits<int>::min() || x > std::numeric_limits<int>::max())
		return (false);
	else
		return (true);
}

PmergeMe::PmergeMe(std::string argv)
{
	std::stringstream ss(argv);
	std::string str;

	ss >> std::ws;
	while (getline(ss, str, ' '))
	{
		if (!isInt(str))
			throw PmergeMe::ArgumentErrorException();
		int x = 0;
		std::stringstream number(str);
		number >> x;
		_auxVec.push_back(x);
		_auxDeque.push_back(x);
		ss >> std::ws;
	}
}

PmergeMe::PmergeMe(PmergeMe &copy)
{	
	(void) copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &instance)
{
	(void) instance;
	return (*this);
}

PmergeMe::~PmergeMe()
{

}

void PmergeMe::generatePairsVec()
{

}

void PmergeMe::print()
{	
	std::cout << "_auxVec: ";
    for(std::vector<int>::iterator it = _auxVec.begin(); it != _auxVec.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

	std::cout << "_auxDeque: ";
	for(std::deque<int>::iterator it = _auxDeque.begin(); it != _auxDeque.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

const char*PmergeMe::WrongArgumentsException::what(void) const throw()
{
	return ("Wrong number of arguments");
};

const char*PmergeMe::ArgumentErrorException::what(void) const throw()
{
	return ("Error found while parsing entered argument");
};