#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

class BitcoinExchange {
	private:
		std::string dataPath;
		std::string inputPath;
		std::map<std::string, std::string> data;
		int readData();
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange(std::string dataPath, std::string inputPath);

		~BitcoinExchange();

		BitcoinExchange &operator=(const BitcoinExchange &copy);

		void setDataPath(std::string dataPath);
		void setInputPath(std::string inputPath);
		
		std::map<std::string, std::string> getData();
		
		void readInput();

		//static void outMap(const std::map<std::string, std::string> &map);

};

std::string trim(const std::string &str);