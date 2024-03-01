#include "../inc/Span.hpp"
#include <iostream>

Span::Span()
{
	_n = 0;
	_l = new std::list<int>;
	_fill = new unsigned int(0);
}

Span::Span(unsigned int n)
{	
	_n = n;
	_l = new std::list<int>(n);
	_fill = new unsigned int(0);
}

Span::Span(Span &copy)
{
	_n = copy._n;
	_fill = new unsigned int(0);
	*_fill = *copy._fill;
	_l = new std::list<int>(copy._n);
	for (unsigned int i = 0; i < *_fill; i++)
	{
		_l[i] = copy._l[i];
	}
}

Span& Span::operator=(const Span &instance)
{
	_n = instance._n;
	delete _l;
	delete _fill;
	_fill = new unsigned int(0);
	*_fill = *instance._fill;
	_l = new std::list<int>(instance._n);
	for (unsigned int i = 0; i < *_fill; i++)
	{
		_l[i] = instance._l[i];
	}
	return (*this);
}

Span::~Span()
{
	delete _l;
}

const char *Span::OutOfBoundsException::what(void) const throw()
{
	return ("Vector is already full!");
};

const char *Span::NoSpanException::what(void) const throw()
{
	return ("No span can be found!");
};

void Span::addNumber(int n)
{
	if (*_fill == _n)
		throw OutOfBoundsException();
	else
	{
		_l->push_back(n);
		_l->erase(_l->begin());
		(*_fill)++;
	}
}

void Span::addNumberRange(int n, unsigned int start, unsigned int end)
{	
	std::list<int>::iterator it_start;
	std::list<int>::iterator it_end;

	it_start = _l->begin();
	while (start)
	{
		it_start++;
		start--;
	}
	it_end = _l->end();
	unsigned int tmp_n = _n;
	while (tmp_n > end)
	{
		tmp_n--;
		it_end--;
	}
	for(std::list<int>::iterator iter = it_start; iter != it_end; iter++)
	{
		*iter = n;
	}
}

unsigned int Span::shortestSpan()
{
	unsigned int	span = 0;
	unsigned int	tmp = 0;
	int				first = 1;

	if (*_fill == 0 || *_fill == 1)
		throw NoSpanException();
	_l->sort();
	for (std::list<int>::iterator iter = _l->begin(); iter != --_l->end(); iter++)
	{
		std::list<int>::iterator iter_cpy = iter;
		tmp = std::abs(*iter - *(++iter_cpy));
		if (first)
		{
			span = tmp;
			first = 0;
		}
		if (tmp < span)
			span = tmp;
	}
	return (span);
}

unsigned int Span::longestSpan()
{
	if (*_fill == 0 || *_fill == 1)
		throw NoSpanException();
	_l->sort();
	return (std::abs(*_l->begin() - *(--_l->end())));
}

void		Span::print()
{
	for (std::list<int>::iterator iter = _l->begin(); iter != _l->end(); iter++)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}