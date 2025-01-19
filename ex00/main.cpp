#include "BitcoinExchange.hpp"
int main(int ac, char* argv[])
{
    if (ac < 2)
    {
        std::cout << "Unable to read file." << std::endl;
        return 1;
    }

    if (ac > 2)
    {
        std::cout << "Too many arguments." << std::endl;
        return 1;
    }

    std::map<std::string, float> bitcoinPrice = parseDataBase("data.csv");

    if (bitcoinPrice.empty())
    {
        return -1;
    }

    BitcoinExchange btc(bitcoinPrice);
    btc.displayOutput(argv[1]);

    return 0;
}