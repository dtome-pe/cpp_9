#include "../inc/PmergeMe.hpp"
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

PmergeMe::PmergeMe(char *argv[])
{

	for (unsigned int i = 1; argv[i]; i++)
	{
		std::string str(argv[i]);
		if (!isInt(str))
			throw PmergeMe::ArgumentErrorException();
		unsigned int x = 0;
		std::stringstream number(str);
		number >> x;
		_beforeVec.push_back(x);
	}
	if (_beforeVec.size() > 3000)
		throw PmergeMe::TooManyNumbersException();
	_n = _beforeVec.size();
	if (_n % 2 != 0)
		_odd = true;
	else
		_odd = false;
}

PmergeMe::PmergeMe(PmergeMe &copy)
{
		_beforeVec = copy._beforeVec;
		_auxVec = copy._auxVec;
		_pendVec = copy._pendVec;
		_pairVec = copy._pairVec;
		_mainVec = copy._mainVec;
		_auxDeque = copy._auxDeque;
		_pendDeque = copy._pendDeque;
		_pairDeque = copy._pairDeque;
		_mainDeque = copy._mainDeque;
		_n = copy._n;
		_odd = copy._odd;
		_timeVec = copy._timeVec;
		_timeDeque = copy._timeDeque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &instance)
{
		_beforeVec = instance._beforeVec;
		_auxVec = instance._auxVec;
		_pendVec = instance._pendVec;
		_pairVec = instance._pairVec;
		_mainVec = instance._mainVec;
		_auxDeque = instance._auxDeque;
		_pendDeque = instance._pendDeque;
		_pairDeque = instance._pairDeque;
		_mainDeque = instance._mainDeque;
		_n = instance._n;
		_odd = instance._odd;
		_timeVec = instance._timeVec;
		_timeDeque = instance._timeDeque;
		return (*this);
}

PmergeMe::~PmergeMe()
{

}

void	PmergeMe::run(char *argv[])
{
	std::cout << "Before: ";
	print(_beforeVec);

	sortVec(argv);
	sortDeque(argv);
		
	std::cout << "After: ";
	print(_mainVec);

	std::cout << "Time to process a range of " << getNumbers() << " elements with std::vec: " << std::fixed << getTimeVec() << "s." << std::endl;
	std::cout << "Time to process a range of " << getNumbers() << " elements with std::deq: " << std::fixed << getTimeDeque() << "s." << std::endl;	
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
    std::vector<unsigned int>jacobSeq;
    unsigned int jacob_index = 3;
    while (generateJacob(jacob_index) < n -1)
	{
		jacobSeq.push_back(generateJacob(jacob_index));
        jacob_index++;
	}
    return (jacobSeq);
}

static unsigned int	getFirstVec(std::vector<std::pair<unsigned int, unsigned int> > &pairVec, std::vector<unsigned int> &pend, unsigned int element)
{	
	unsigned int ret = 0;
	for (unsigned int i = 0; i < pairVec.size(); i++)
	{
		if (element == pairVec[i].first)
			ret = pairVec[i].second;
	}
	for (unsigned int i = 0; i < pend.size(); i++)
	{
		if (ret == pend[i])
		{	
			pend.erase(pend.begin() + i);
			break ;
		}
	}
	return (ret);
}

static size_t bisectVec(const std::vector<unsigned int>& main, unsigned int item, size_t left, size_t right) 
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

static void	insertVec(std::vector<unsigned int> &main, std::vector<unsigned int> &pend,
 unsigned int straggler, std::vector<std::pair<unsigned int, unsigned int> > &pairVec, bool _odd)
{
	for (unsigned int i = 0; i < pairVec.size(); i++)
		main.push_back(pairVec[i].first);
	for (unsigned int i = 0; i < pairVec.size(); i++)
		pend.push_back(pairVec[i].second);
	std::vector<unsigned int>::iterator it = main.begin();
	main.insert(it, getFirstVec(pairVec, pend, main[0]));
	if (pend.size() != 0)
	{
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
			size_t insertionPoint = bisectVec(main, element, 0, main.size());
			main.insert(main.begin() + insertionPoint, element);
			iterator++;
			jacobIndex++;
		}
	}
	if (_odd)
	{
		size_t insertion_point = bisectVec(main, straggler, 0, main.size());
    	main.insert(main.begin() + insertion_point, straggler);
	}
	return ;
}

static std::vector<std::pair<unsigned int, unsigned int> > mergeVec(std::vector<std::pair<unsigned int, unsigned int> >& left, std::vector<std::pair<unsigned int, unsigned int> >& right)
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
		return vec;
	int mid = vec.size() / 2;
	std::vector<std::pair<unsigned int, unsigned int> >left(vec.begin(), vec.begin() + mid);
    std::vector<std::pair<unsigned int, unsigned int> >right(vec.begin() + mid, vec.end());

	left = mergeSortVec(left);
    right = mergeSortVec(right);

	return (mergeVec(left, right));
}

void PmergeMe::sortVec(char *argv[])
{	
	clock_t start = clock();
	addToContainer(_auxVec, argv);
	size_t size = _auxVec.size();
	if (size == 1)
		return (_mainVec.push_back(_auxVec[0]));
	if (_odd)
	{
		size -=  1;
		_straggler = _auxVec[_auxVec.size() - 1];
	}
	for (unsigned int i = 0; i < size; i += 2)
	{
		if (_auxVec[i] < _auxVec[i + 1])
			std::swap(_auxVec[i], _auxVec[i + 1]);
		_pairVec.push_back(std::make_pair(_auxVec[i], _auxVec[i + 1]));
	}
	_pairVec = mergeSortVec(_pairVec);
	insertVec(_mainVec, _pendVec, _straggler, _pairVec, _odd);
	clock_t end = clock();
	_timeVec = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);
	//print(_mainVec);
}

static size_t bisectDeque(const std::deque<unsigned int>& main, unsigned int item, size_t left, size_t right) 
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

static unsigned int	getFirstDeque(std::deque<std::pair<unsigned int, unsigned int> > &pairVec, std::deque<unsigned int> &pend, unsigned int element)
{	
	unsigned int ret = 0;
	for (unsigned int i = 0; i < pairVec.size(); i++)
	{
		if (element == pairVec[i].first)
			ret = pairVec[i].second;
	}
	for (unsigned int i = 0; i < pend.size(); i++)
	{
		if (ret == pend[i])
		{	
			pend.erase(pend.begin() + i);
			break ;
		}
	}
	return (ret);
}

static void	insertDeque(std::deque<unsigned int> &main, std::deque<unsigned int> &pend,
 unsigned int straggler, std::deque<std::pair<unsigned int, unsigned int> > &pairVec, bool _odd)
{
	for (unsigned int i = 0; i < pairVec.size(); i++)
		main.push_back(pairVec[i].first);
	for (unsigned int i = 0; i < pairVec.size(); i++)
		pend.push_back(pairVec[i].second);
	
	std::deque<unsigned int>::iterator it = main.begin();
	main.insert(it, getFirstDeque(pairVec, pend, main[0]));

	if (pend.size() != 0)
	{
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

			size_t insertionPoint = bisectDeque(main, element, 0, main.size());
			main.insert(main.begin() + insertionPoint, element);

			iterator++;
			jacobIndex++;
		}
	}
	if (_odd)
	{
		size_t insertion_point = bisectDeque(main, straggler, 0, main.size());
    	main.insert(main.begin() + insertion_point, straggler);
	}
	return ;
}

static std::deque<std::pair<unsigned int, unsigned int> > mergeDeque(std::deque<std::pair<unsigned int, unsigned int> >& left, std::deque<std::pair<unsigned int, unsigned int> >& right)
{
	std::deque<std::pair<unsigned int, unsigned int> > result;

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

static std::deque<std::pair<unsigned int, unsigned int> >mergeSortDeque(std::deque<std::pair<unsigned int, unsigned int> >&deque)
{
	if (deque.size() <= 1)
		return deque;

	int mid = deque.size() / 2;
	std::deque<std::pair<unsigned int, unsigned int> >left(deque.begin(), deque.begin() + mid);
    std::deque<std::pair<unsigned int, unsigned int> >right(deque.begin() + mid, deque.end());

	left = mergeSortDeque(left);
    right = mergeSortDeque(right);

	return (mergeDeque(left, right));
}

void PmergeMe::sortDeque(char *argv[])
{	
	clock_t start = clock();
	addToContainer(_auxDeque, argv);
	size_t size = _n;
	if (size == 1)
		return (_mainDeque.push_back(_auxDeque[0]));
	if (_odd)
	{
		size -=  1;
		_straggler = _auxDeque[_auxDeque.size() - 1];
	}
	for (unsigned int i = 0; i < size; i += 2)
	{	
		if (_auxDeque[i] < _auxDeque[i + 1])
			std::swap(_auxDeque[i], _auxDeque[i + 1]);
		_pairDeque.push_back(std::make_pair(_auxDeque[i], _auxDeque[i + 1]));
	}
	_pairDeque = mergeSortDeque(_pairDeque);
	insertDeque(_mainDeque, _pendDeque, _straggler, _pairDeque, _odd);
	clock_t end = clock();
	_timeDeque = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);
	//print(_mainDeque);
}

unsigned int	PmergeMe::getNumbers()
{
	return (_n);
}

double			PmergeMe::getTimeVec()
{
	return (_timeVec);
}

double			PmergeMe::getTimeDeque()
{
	return (_timeDeque);
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

const char*PmergeMe::TooManyNumbersException::what(void) const throw()
{
	return ("Too many numbers entered (3000 or less)");
};