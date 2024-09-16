#ifndef __BITCOIN_EXCHANGE_H__
#define __BITCOIN_EXCHANGE_H__

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <algorithm>

class BitcoinExchange
{
	private:

		std::map<std::string, float>& bitcoinPrice;

		bool isPositiveNumber(std::string value);
		bool isValidDate(std::string date);
		int dateToInt(std::string date);
		std::string findClosestDate(std::string date);

	public:

		BitcoinExchange(std::map<std::string, float>& priceDataBase);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& bitcoinExchange);
		BitcoinExchange& operator=(const BitcoinExchange& bitcoinExchange);
		void displayOutput(std::string fileName);

};

std::map<std::string, float> parseDataBase(std::string fileName);
bool firstLineIsCorrect(std::string line, std::string col1, std::string col2, char delimiter);

#endif