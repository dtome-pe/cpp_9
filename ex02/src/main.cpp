#include "../inc/PmergeMe.hpp"

int main(int argc, char *argv[]) 
{
    try 
	{
		if (argc < 2) 
       		throw PmergeMe::WrongArgumentsException();
		
		PmergeMe a(argv[1]);

		//std::cout << "Before: ";
		//a.printAux();

		a.sortVec();
		a.sortDeque();
		
		std::cout << "After: ";
		a.printMain();
    } 
	catch (std::exception &e) 
	{
        std::cout << e.what() << std::endl;
    }
    return 0;
}