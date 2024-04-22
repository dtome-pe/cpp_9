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
	std::vector<unsigned int> uniqueCheck;
    for (unsigned int i = 0; i < _auxVec.size(); i++) 
	{
        for (unsigned int j = 0; j < uniqueCheck.size(); j++)
		{
			if (_auxVec[i] == uniqueCheck[j])
				throw PmergeMe::DuplicateErrorException();
		}
		uniqueCheck.push_back(_auxVec[i]);
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

static unsigned int generateJacob(unsigned int n)
{
	 if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return (generateJacob(n - 1) + 2 * generateJacob(n - 2));
}

static std::vector<unsigned int> buildJacob(unsigned int n)
{
	//std::cout << "n es: " << n << std::endl; 
    std::vector<unsigned int>jacobSeq;
    unsigned int jacob_index = 3;

    while (generateJacob(jacob_index) < n -1)
	{
		jacobSeq.push_back(generateJacob(jacob_index));
        jacob_index++;
	}

    return (jacobSeq);
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

static size_t bisect(const std::vector<unsigned int>& main, unsigned int item, size_t left, size_t right) 
{
    while (left < right) 
	{
        size_t mid = left + (right - left) / 2;
        if (main[mid] < item)
            left = mid + 1;
    	else 
            right = mid;
    }

    return left;
}

static std::vector<unsigned int>insertVec(std::vector<unsigned int> &main, std::vector<unsigned int> &pend,
 std::vector<unsigned int> &aux, std::vector<std::pair<unsigned int, unsigned int> > &pairVec, unsigned int n, bool _odd)
{
	(void) n;

	unsigned int straggler;

	for (unsigned int i = 0; i < pairVec.size(); i++)
		main.push_back(pairVec[i].first);
	for (unsigned int i = 0; i < pairVec.size(); i++)
		pend.push_back(pairVec[i].second);
	if (aux.size())
	{
		pend.push_back(aux[0]);
		aux.erase(aux.begin());
	}
	if (_odd)
	{
		straggler = pend[pend.size() - 1];
		pend.erase(pend.end() - 1);
	}
	
	std::vector<unsigned int>::iterator it = main.begin();
	main.insert(it, getFirst(pairVec, pend, main[0]));
	std::vector<unsigned int>jacobSeq = buildJacob(pend.size());
	
	unsigned int				jacobIndex = 3;
	std::string 				last = "default";
	std::vector<unsigned int>	indexSeq(1);
	unsigned int				element;
	unsigned int				iterator = 0;

	while (iterator <= pend.size())
	{
		if (jacobSeq.size() != 0 && last != "jacob")
		{
			indexSeq.push_back(jacobSeq[0]);
			element = pend[jacobSeq[0] - 1];
			jacobSeq.erase(jacobSeq.begin());
			last = "jacob";
			
		}
		else
		{
			if (std::find(indexSeq.begin(), indexSeq.end(), iterator) != indexSeq.end())
				iterator++;
			element = pend[iterator - 1];
			indexSeq.push_back(iterator);
			last = "not-jacob";
		}
		size_t insertionPoint = bisect(main, element, 0, main.size());

		std::cout << "element inserted: " << element << std::endl;
		main.insert(main.begin() + insertionPoint, element);

		iterator++;
		jacobIndex++;
	}
	if (_odd)
	{
		size_t insertion_point = bisect(main, straggler, 0, main.size());
    	main.insert(main.begin() + insertion_point, straggler);
	}
	return (main);
}

static std::vector<std::pair<unsigned int, unsigned int> > merge(std::vector<std::pair<unsigned int, unsigned int> >& left, std::vector<std::pair<unsigned int, unsigned int> >& right)
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

static std::vector<std::pair<unsigned int, unsigned int> >mergeSortVec(std::vector<std::pair<unsigned int, unsigned int> >&vec)
{
	if (vec.size() <= 1)
	{
		return vec;
	}
	int mid = vec.size() / 2;
	std::vector<std::pair<unsigned int, unsigned int> >left(vec.begin(), vec.begin() + mid);
    std::vector<std::pair<unsigned int, unsigned int> >right(vec.begin() + mid, vec.end());

	left = mergeSortVec(left);
    right = mergeSortVec(right);

	return (merge(left, right));
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
		_auxVec.erase(_auxVec.begin() + i);
		size--;
	}
	if (!_odd)
		_auxVec.erase(_auxVec.begin(), _auxVec.end());
	else
		_auxVec.erase(_auxVec.begin(), _auxVec.end() - 1);
	_pairVec = mergeSortVec(_pairVec);
	insertVec(_mainVec, _pendVec, _auxVec, _pairVec, _n, _odd);
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

void PmergeMe::printPend()
{	
	std::cout << "_pendVec: ";
    for(std::vector<unsigned int>::iterator it = _pendVec.begin(); it != _pendVec.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

/* 	std::cout << "_auxDeque: ";
	for(std::deque<unsigned int>::iterator it = _auxDeque.begin(); it != _auxDeque.end() ; ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; */
}

void PmergeMe::printMain()
{	
	std::cout << "_mainVec: ";
    for(std::vector<unsigned int>::iterator it = _mainVec.begin(); it != _mainVec.end() ; ++it){
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

const char*PmergeMe::DuplicateErrorException::what(void) const throw()
{
	return ("Duplicate integers found");
};