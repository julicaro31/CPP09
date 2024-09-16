#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::map<std::string, float>& priceDataBase): bitcoinPrice(priceDataBase)
{
	std::cout << "BitcoinExchange constructor has been called." << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << "BitcoinExchange destructor has been called." << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& bitcoinExchange): bitcoinPrice(bitcoinExchange.bitcoinPrice)
{
	std::cout << "BitcoinExchange copy constructor operator has been called." << std::endl;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& bitcoinExchange)
{
	std::cout << "BitcoinExchange copy assignment operator has been called." <<std::endl;
	if (this != &bitcoinExchange)
	{
		this->bitcoinPrice = bitcoinExchange.bitcoinPrice;
	}
	return *this;
}

bool BitcoinExchange::isPositiveNumber(std::string value)
{
	try 
	{
		float floatValue = std::stof(value);
		return floatValue >= 0;
	} 
	catch (const std::invalid_argument& e) 
	{
		return false;
	}
}

bool BitcoinExchange::isValidDate(std::string date)
{
	if (date.length() != 11 || date[4] != '-' || date[7] != '-') 
	{
		return false;
	}

	int year, month, day;
	char dash1, dash2;

	std::stringstream ss(date);
	ss >> year >> dash1 >> month >> dash2 >> day;

	if (ss.fail() || dash1 != '-' || dash2 != '-') 
	{
		return false;
	}

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) 
	{
		return false;
	}

	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	int daysInMonth[] = {31, (isLeapYear ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	return day <= daysInMonth[month - 1];
}

int BitcoinExchange::dateToInt(std::string date)
{
	date.erase(std::remove(date.begin(), date.end(), '-'), date.end());
	return std::stoi(date);
}

std::string BitcoinExchange::findClosestDate(std::string date)
{
	int dateInt =  dateToInt(date);

	std::map<std::string, float>::iterator it;
	int minDif = std::numeric_limits<int>::max();
	std::string closestDate = this->bitcoinPrice.begin()->first;

	for (it = this->bitcoinPrice.begin(); it != this->bitcoinPrice.end(); it++)
	{
		int dif = dateInt - dateToInt(it->first);
		if (dif > 0 && dif < minDif)
		{
			closestDate = it->first;
			minDif = dif;
		}
	}
	return closestDate;
}

void BitcoinExchange::displayOutput(std::string fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) 
	{
		std::cerr << "Error: File " << fileName << " does not exist or cannot be opened." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line);
	if (!firstLineIsCorrect(line, "date ", " value", '|'))
	{
		std::cout << "Error: bad input" << std::endl;
		file.close();
		return;
	}
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string date, amount;

		if (!std::getline(ss, date, '|') || !std::getline(ss, amount, '|') || !isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
		}
		else if(!isPositiveNumber(amount))
		{
			std::cout << "Error: not a positive number." << std::endl;
		}
		else if(std::stof(amount) > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
		}
		else
		{
			date.pop_back();
			std::cout << date << " => " << amount << " = ";
			try 
			{
				std::cout << this->bitcoinPrice.at(date) *  std::stof(amount) << std::endl;
			} 
			catch (const std::out_of_range& e)
			{
				std::cout << this->bitcoinPrice.at(findClosestDate(date))* std::stof(amount) << std::endl;
			}
		}
	}
	file.close();
}

std::map<std::string, float> parseDataBase(std::string fileName)
{
	std::map<std::string, float> dataBase;
	std::ifstream file(fileName);
	if (!file.is_open()) 
	{
		std::cerr << "Error: File " << fileName << " does not exist or cannot be opened." << std::endl;
		return dataBase;
	}

	std::string line;

	std::getline(file, line);
	if (!firstLineIsCorrect(line, "date", "exchange_rate", ','))
	{
		std::cout << "Error in file." << std::endl;
		file.close();
		return dataBase;
	}
	int lines = 0;
	while (std::getline(file, line)) 
	{
		lines++;
		std::stringstream ss(line);
		std::string key, value;

		if (std::getline(ss, key, ',') && std::getline(ss, value, ','))
		{
			try 
			{
				float floatValue = std::stof(value);
				dataBase[key] = floatValue;
			} 
			catch (const std::invalid_argument& e) 
			{
				std::cerr << "Invalid float in line: " << line << std::endl;
			} 
			catch (const std::out_of_range& e) 
			{
				std::cerr << "Float out of range in line: " << line << std::endl;
			}
		}
	}
	file.close();
	return dataBase;
}

bool firstLineIsCorrect(std::string line, std::string col1, std::string col2, char delimiter)
{
	std::stringstream ss(line);
	std::string name1, name2;

	if (std::getline(ss, name1, delimiter) && std::getline(ss, name2, delimiter) && name1 == col1 && name2 == col2)
	{
		return true;
	}
	else
	{
		return false;
	}
}