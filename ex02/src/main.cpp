#include "../inc/PmergeMe.hpp"

int main(int argc, char *argv[]) 
{
    try 
	{
		if (argc < 2) 
       		throw PmergeMe::WrongArgumentsException();
		
		PmergeMe a(argv[1]);
		a.print();
    } 
	catch (std::exception &e) 
	{
        std::cout << e.what() << std::endl;
    }
    return 0;
}