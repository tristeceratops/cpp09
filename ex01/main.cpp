#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " \"rpn\"" << std::endl;
		return 1;
	}

	RPN rpn(argv[1]);

	try
	{
		std::cout << rpn.calculate() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "RPN error : " << e.what() << '\n';
	}
	
	
	return 0;
}