#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>
# define ADDITION 0
# define SUBSTRACTION 1
# define MULTIPLICATION 2
# define DIVISION 3

class RPN
{	
	private:
		std::stack<float>_exp;

	public:
		RPN();
		RPN(RPN &copy);
		RPN& operator=(const RPN &instance);
		~RPN();

		void	calculate(std::string argv);

		class 	WrongArgumentsException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif