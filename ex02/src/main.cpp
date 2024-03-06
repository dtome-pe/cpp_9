#include "../inc/PmergeMe.hpp"

int main(int argc, char *argv[]) 
{
    try 
	{
		if (argc < 2) 
       		throw PmergeMe::WrongArgumentsException();
		
		PmergeMe a(argv[1]);
		
		//a.printAux();
		a.sortVec();
		a.printAux();
		a.printSorted();
		a.printPairs();
		//a.printAux();
    } 
	catch (std::exception &e) 
	{
        std::cout << e.what() << std::endl;
    }
    return 0;
}