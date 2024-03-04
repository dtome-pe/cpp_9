#ifndef RPN_HPP
# define RPN_HPP

class RPN
{	
	private:

	public:
		RPN();
		RPN(unsigned int n);
		RPN(RPN &copy);
		RPN& operator=(const RPN &instance);
		~RPN();

};

#endif