#include <iostream>
#include "BitcoinExchange.hpp"

#define DATA_PATH "data.csv"


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Wrong number of arguments" << std::endl;
		return 1;
	}
	BitcoinExchange exchange(DATA_PATH, argv[1]);

	exchange.readData();
	exchange.readInput();

	// BitcoinExchange::outMap(exchange.getData());
	// std::cout << "----------" <<std::endl;
}