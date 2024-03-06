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
		unsigned int x = 0;
		std::stringstream number(str);
		number >> x;
		_auxVec.push_back(x);
		_auxDeque.push_back(x);
		ss >> std::ws;
	}
	_n = _auxVec.size();
	if (_n % 2 != 0)
		_odd = true;
	else
		_odd = false;

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

std::vector<std::pair<unsigned int, unsigned int> > merge(std::vector<std::pair<unsigned int, unsigned int> >& left, std::vector<std::pair<unsigned int, unsigned int> >& right)
{
	std::vector<std::pair<unsigned int, unsigned int> > result;

	while (!left.empty() && !right.empty())
	{
        if (left.front().first <= right.front().first)
		{
            result.push_back(left.front());
            left.erase(left.begin());
        }
		else
		{
            result.push_back(right.front());
            right.erase(right.begin());
        }
    }

	while (!left.empty())
	{
        result.push_back(left.front());
        left.erase(left.begin());
    }
    while (!right.empty())
	{
        result.push_back(right.front());
        right.erase(right.begin());
    }
    return result;
}

static std::vector<std::pair<unsigned int, unsigned int> >mergeVec(std::vector<std::pair<unsigned int, unsigned int> >&vec)
{
    if (vec.size() <= 1)
        return vec;
	int mid = vec.size() / 2;
	
	std::vector<std::pair<unsigned int, unsigned int> >left(vec.begin(), vec.begin() + mid);
    std::vector<std::pair<unsigned int, unsigned int> >right(vec.begin() + mid, vec.end());

	left = mergeVec(left);
    right = mergeVec(right);

	return (merge(left, right));
}

static unsigned int	getFirst(std::vector<std::pair<unsigned int, unsigned int> > &pairVec, std::vector<unsigned int> &aux, unsigned int element)
{	
	unsigned int ret = 0;
	for (unsigned int i = 0; i < pairVec.size(); i++)
	{
		if (element == pairVec[i].first)
			ret = pairVec[i].second;
	}
	for (unsigned int i = 0; i < aux.size(); i++)
	{
		if (ret == aux[i])
		{	
			aux.erase(aux.begin() + i);
			break ;
		}
	}
	return (ret);
}

static std::vector<unsigned int>insertVec(std::vector<unsigned int> &sorted, std::vector<unsigned int> &aux, std::vector<std::pair<unsigned int, unsigned int> > &pairVec)
{	
	for (unsigned int i = 0; i < pairVec.size(); i++)
		sorted.push_back(pairVec[i].first);
	std::vector<unsigned int>::iterator it = sorted.begin();
	sorted.insert(it, getFirst(pairVec, aux, sorted[0]));

	return (sorted);
}

void PmergeMe::sortVec()
{	
	size_t size = _n;
	if (_odd)
		size -=  1;
	for (unsigned int i = 0; i < size - 1; i++)
	{	
		if (_auxVec[i] < _auxVec[i + 1])
			std::swap(_auxVec[i], _auxVec[i + 1]);
		_pairVec.push_back(std::make_pair(_auxVec[i], _auxVec[i + 1]));
		//_sortedVec.push_back(_auxVec[i]);
		_auxVec.erase(_auxVec.begin() + i);
		//_auxVec.erase(it + i + 1);
		size--;
	}
	if (!_odd)
		_auxVec.erase(_auxVec.begin(), _auxVec.end());
	else
		_auxVec.erase(_auxVec.begin(), _auxVec.end() - 1);
	_pairVec = mergeVec(_pairVec);
	insertVec(_sortedVec, _auxVec, _pairVec);
}

void PmergeMe::printAux()
{	
	std::cout << "_auxVec: ";
    for(std::vector<unsigned int>::iterator it = _auxVec.begin(); it != _auxVec.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

/* 	std::cout << "_auxDeque: ";
	for(std::deque<unsigned int>::iterator it = _auxDeque.begin(); it != _auxDeque.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; */
}

void PmergeMe::printSorted()
{	
	std::cout << "_sortedVec: ";
    for(std::vector<unsigned int>::iterator it = _sortedVec.begin(); it != _sortedVec.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

/* 	std::cout << "_sortedDeque: ";
	for(std::deque<unsigned int>::iterator it = _sortedDeque.begin(); it != _sortedDeque.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; */
}

void PmergeMe::printPairs()
{	
	std::cout << "_pairVec: " << std::endl;
    for(std::vector<std::pair<unsigned int, unsigned int> >::iterator it = _pairVec.begin(); it != _pairVec.end() ; ++it){
        std::cout << it->first << ":" << it->second << std::endl;
    }

/* 	std::cout << "_sortedDeque: ";
	for(std::deque<unsigned int>::iterator it = _sortedDeque.begin(); it != _sortedDeque.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; */
}

const char*PmergeMe::WrongArgumentsException::what(void) const throw()
{
	return ("Wrong number of arguments");
};

const char*PmergeMe::ArgumentErrorException::what(void) const throw()
{
	return ("Error found while parsing entered argument");
};