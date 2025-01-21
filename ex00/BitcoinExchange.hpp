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
		std::map<std::string, double> input;
		std::map<std::string, double> data;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange(std::string dataPath, std::string inputPath);

		~BitcoinExchange();

		BitcoinExchange &operator=(const BitcoinExchange &copy);

		void readData();
		void readInput();

		void setDataPath(std::string dataPath);
		void setInputPath(std::string inputPath);

		std::map<std::string, double> getData();
		std::map<std::string, double> getInput();

		static void outMap(const std::map<std::string, double> &map);

};

std::string trim(const std::string &str);