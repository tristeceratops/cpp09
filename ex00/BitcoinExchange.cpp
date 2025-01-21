#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : dataPath(""), inputPath(""), input() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : dataPath(copy.dataPath), inputPath(copy.inputPath), input(copy.input) {}

BitcoinExchange::BitcoinExchange(std::string dataPath, std::string inputPath) : dataPath(dataPath), inputPath(inputPath), input() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this == &copy)
		return *this;
	dataPath = copy.dataPath;
	inputPath = copy.inputPath;
	input = copy.input;
	return *this;
}

void BitcoinExchange::readData()
{
	std::ifstream file(dataPath.c_str());
	std::string line;
	if (!file.is_open())
	{
		std::cerr << "Error: cannot open file" << std::endl;
		return;
	}
	std::getline(file, line); // skip first line
	while (std::getline(file, line))
	{
		if (line.find(',') == std::string::npos)
			std::cerr << "Error: invalid data" << std::endl;
		std::string key = line.substr(0, line.find(','));
		std::string value = line.substr(line.find(',') + 1);
		std::stringstream ss(trim(value));
		ss >> data[key];
		if (ss.fail())
			std::cerr << "Error: invalid data" << std::endl;
	}
	file.close();
}

void BitcoinExchange::readInput()
{
	std::ifstream file(inputPath.c_str());
	std::string line;
	if (!file.is_open())
	{
		std::cerr << "Error: cannot open file" << std::endl;
		return;
	}
	std::getline(file, line); // skip first line
	while (std::getline(file, line))
	{
		if (line.find('|') == std::string::npos)
			std::cerr << "Error: invalid input" << std::endl;
		std::string key = line.substr(0, line.find('|'));
		std::string value = line.substr(line.find('|') + 1);
		std::stringstream ss(trim(value));
		ss >> data[key];
		if (ss.fail())
			std::cerr << "Error: invalid input" << std::endl;
	}
	file.close();
} 

void BitcoinExchange::outMap(const std::map<std::string, double> &map)
{
	std::map<std::string, double>::const_iterator it = map.begin();
	for (it = map.begin(); it != map.end(); ++it)
	{
		std::cout << it->first << " : " << it->second << std::endl;
	}
}

std::string trim(const std::string &str) {
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isspace(*it)) {
        ++it;
    }

    std::string::const_reverse_iterator rit = str.rbegin();
    while (rit.base() != it && std::isspace(*rit)) {
        ++rit;
    }

    return std::string(it, rit.base());
}

void BitcoinExchange::setDataPath(std::string dataPath)
{
	this->dataPath = dataPath;
}

void BitcoinExchange::setInputPath(std::string inputPath)
{
	this->inputPath = inputPath;
}

std::map<std::string, double> BitcoinExchange::getData()
{
	return data;
}

std::map<std::string, double> BitcoinExchange::getInput()
{
	return input;
}