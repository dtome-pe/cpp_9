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
	{
		return vec;
	}
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

static std::vector<unsigned int>insertVec(std::vector<unsigned int> &main, std::vector<unsigned int> &pend,
 std::vector<unsigned int> &aux, std::vector<std::pair<unsigned int, unsigned int> > &pairVec, unsigned int n)
{	
	(void)	n;
	u_int64_t jacobsthal_diff[] = {
        2u, 2u, 6u, 10u, 22u, 42u, 86u, 170u, 342u, 682u, 1366u,
        2730u, 5462u, 10922u, 21846u, 43690u, 87382u, 174762u, 349526u, 699050u,
        1398102u, 2796202u, 5592406u, 11184810u, 22369622u, 44739242u, 89478486u,
        178956970u, 357913942u, 715827882u, 1431655766u, 2863311530u, 5726623062u,
        11453246122u, 22906492246u, 45812984490u, 91625968982u, 183251937962u,
        366503875926u, 733007751850u, 1466015503702u, 2932031007402u, 5864062014806u,
        11728124029610u, 23456248059222u, 46912496118442u, 93824992236886u, 187649984473770u,
        375299968947542u, 750599937895082u, 1501199875790165u, 3002399751580331u,
        6004799503160661u, 12009599006321322u, 24019198012642644u, 48038396025285288u,
        96076792050570576u, 192153584101141152u, 384307168202282304u, 768614336404564608u,
        1537228672809129216u, 3074457345618258432u, 6148914691236516864u
    };
	for (unsigned int i = 0; i < pairVec.size(); i++)
		main.push_back(pairVec[i].first);
	for (unsigned int i = 0; i < pairVec.size(); i++)
		pend.push_back(pairVec[i].second);
	if (aux.size())
	{
		pend.push_back(aux[0]);
		aux.erase(aux.begin());
	}
	std::vector<unsigned int>::iterator it = main.begin();
	main.insert(it, getFirst(pairVec, pend, main[0]));
	for (int k = 0 ; ; ++k)
    {
        uint64_t dist = jacobsthal_diff[k];
        if (dist >= pend.size()) break;
        std::vector<unsigned int>::iterator it = pend.begin();
        std::advance(it, dist);

        while (true)
        {
            std::vector<unsigned int>::iterator insertion = main.begin();
			while ()
            main.insert(insertion, *it);

            it = pend.erase(it);
            if (it == pend.begin()) break;
            --it;
        }
    }
	return (main);
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
	_pairVec = mergeVec(_pairVec);
	insertVec(_mainVec, _pendVec, _auxVec, _pairVec, _n);
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