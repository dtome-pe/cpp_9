#include "../inc/PmergeMe.hpp"
#include <sstream>
#include <limits>
#include <algorithm>
#include <utility>

static bool isInt(const std::string &str)
{
	if (str.find_first_not_of("0123456789") != std::string::npos)
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
	_n = _auxVec.size();
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
	size_t size = _n;
	if (_n % 2 != 0)
		size = _n - 1;
	for (unsigned int i = 0; i < size; i++)
	{	
		if (_auxVec[i] < _auxVec[i + 1])
			std::swap(_auxVec[i], _auxVec[i + 1]);
		_pairVec.push_back(std::make_pair(_auxVec[i], _auxVec[i + 1]));
		_auxVec.erase(_auxVec.begin() + i);

		size -= 1;
	}
}

void PmergeMe::printAux()
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

void PmergeMe::printPairs()
{	
	std::cout << "_pairVec: " << std::endl;
    for(std::vector<std::pair<int, int> >::iterator it = _pairVec.begin(); it != _pairVec.end() ; ++it){
        std::cout << it->first << ":" << it->second << std::endl;
    }

	std::cout << "_pairDeque: " << std::endl;
	for(std::deque<std::pair<int, int> >::iterator it = _pairDeque.begin(); it != _pairDeque.end() ; ++it){
        std::cout << it->first << ":" << it->second << std::endl;
    }
}

const char*PmergeMe::WrongArgumentsException::what(void) const throw()
{
	return ("Wrong number of arguments");
};

const char*PmergeMe::ArgumentErrorException::what(void) const throw()
{
	return ("Error found while parsing entered argument");
};