#ifndef SPAN_HPP
# define SPAN_HPP

# include <list>
# include <algorithm>
# include <exception>

class Span
{	
	private:
		std::list<int> 		*_l;
		unsigned int		_n;
		unsigned int		*_fill;

	public:
		Span();
		Span(unsigned int n);
		Span(Span &copy);
		Span& operator=(const Span &instance);
		~Span();

		void 	addNumber(int n);
		void	addNumberRange(int n, unsigned int start, unsigned int end);
		unsigned int	shortestSpan();
		unsigned int	longestSpan();

		void	print();

		class OutOfBoundsException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class NoSpanException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

};

#endif