#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : dataPath(""), inputPath(""){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : dataPath(copy.dataPath), inputPath(copy.inputPath){}

BitcoinExchange::BitcoinExchange(std::string dataPath, std::string inputPath) : dataPath(dataPath), inputPath(inputPath){}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this == &copy)
		return *this;
	dataPath = copy.dataPath;
	inputPath = copy.inputPath;
	return *this;
}

int BitcoinExchange::readData()
{
	std::ifstream file(dataPath.c_str());
	std::string line;
	if (!file.is_open())
	{
		std::cerr << "Error: cannot open file" << std::endl;
		return 1;
	}
	std::getline(file, line); // skip first line
	while (std::getline(file, line))
	{
		std::string value;
		if (line.find(',') == std::string::npos)
			value = "npos";
		else
		{
			value = line.substr(line.find(',') + 1);
			if (value.size() == 0)
				value = "empty";
		}
		std::string key = line.substr(0, line.find(','));
		data[key] = value;
	}
	return 0;
	// file.close();
}

// void BitcoinExchange::outMap(const std::map<std::string, std::string> &map)
// {
// 	std::map<std::string, std::string>::const_iterator it = map.begin();
// 	for (it = map.begin(); it != map.end(); ++it)
// 	{
// 		std::cout << it->first << " : " << it->second << std::endl;
// 	}
// }

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

std::map<std::string, std::string> BitcoinExchange::getData()
{
	return data;
}

bool isLeap(int year)
{
	return (((year % 4 == 0) && 
			(year % 100 != 0)) || 
			(year % 400 == 0)); 
}

bool isValidDate(int year, int month, int day)
{
	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	if (month == 2)
	{
		if (isLeap(year))
			return day <= 29;
		return day <= 28;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return day <= 30;
	return true;
}

//read input file line by line
//For each line:
//skip first line
//parse date and value: date | value
//check if date and value are correct
//date is in the format YYYY-MM-DD and need to exist (no 32 of January)
//value is a int or float between 0 and 1000
//if not correct, output error and go to next line
//if correct, find in data the value of the bitcoin for the date
//if date not exist in data, take the value of the closest date, use lower date, not upper one
//output the date and the value of the bitcoin * by value
//YYYY-MM-DD => value = value * bitcoin value
void BitcoinExchange::readInput()
{
	if (readData())
		return;
	
	std::ifstream file(inputPath.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: cannot open file: " << inputPath << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // Skip the header line

	while (std::getline(file, line))
	{
		if (line.find('|') == std::string::npos)
		{
			std::cerr << "Error: invalid input format in line: " << line << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, line.find('|')));
		std::string valueStr = trim(line.substr(line.find('|') + 1));

		// Validate date format (YYYY-MM-DD)
		if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		{
			std::cerr << "Error: wrong date format: " << date << std::endl;
			continue;
		}
		std::string year, month, day;
		int yearInt, monthInt, dayInt;

		year = date.substr(0, 4);
		month = date.substr(5, 2);
		day = date.substr(8, 2);

		std::stringstream yearStream(year);
		std::stringstream monthStream(month);
		std::stringstream dayStream(day);

		yearStream >> yearInt;
		monthStream >> monthInt;
		dayStream >> dayInt;

		if (yearStream.fail() || monthStream.fail() || dayStream.fail())
		{
			std::cerr << "Error: wrong date format: " << date << std::endl;
			continue;
		}

		if (!isValidDate(yearInt, monthInt, dayInt))
		{
			std::cerr << "Error: invalid date: " << date << std::endl;
			continue;
		}
		
		// Convert value to float
		std::stringstream valueStream(valueStr);
		float value;
		if (!(valueStream >> value) || value < 0 || value > 1000 || valueStream.fail() || !valueStream.eof())
		{
			if (value < 0)
				std::cerr << "Error: not a positive value: " << valueStr << std::endl;
			else if (value > 1000)
				std::cerr << "Error: value too high: " << valueStr << std::endl;
			else
				std::cerr << "Error: invalid value: " << valueStr << std::endl;
			continue;
		}

		// Find the corresponding exchange rate
		std::map<std::string, std::string>::iterator it = data.find(date);
		if (it == data.end())
		{
			std::map<std::string, std::string>::iterator it2 = data.lower_bound(date);
			if (it2 == data.begin())
			{
				std::cerr << "Error: no data available for date: " << date << std::endl;
				continue;
			}
			it2--;
			std::stringstream rateStream(it2->second);
			float rate;
			if (!(rateStream >> rate) || rateStream.fail() || !rateStream.eof())
			{
				std::cerr << "Error: invalid rate in data map for date: " << it2->first << std::endl;
				continue;
			}
			std::cout << date << " => " << value << " = " << value * rate << std::endl;
		}
		else
		{
			std::stringstream rateStream(it->second);
			float rate;
			if (!(rateStream >> rate) || rateStream.fail() || !rateStream.eof())
			{
				std::cerr << "Error: invalid rate in data map for date: " << it->first << std::endl;
				continue;
			}
			std::cout << date << " => " << value << " = " << value * rate << std::endl;
		}
	}

	file.close();
}
