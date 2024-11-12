#pragma once

#include <string.h>
#include <curl/curl.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>

struct Dividend
{
    Dividend( std::string& date, std::string& amount ) : date(date), amount(amount){}
    std::string date;
    std::string amount;
    std::string currency = "USD";
};

class YahooFinanceAPI
{
    public:
        YahooFinanceAPI();
        std::string getStockDividends(std::string& stockSymbol, std::string& range);

    private:
        std::string download_file(std::string& url);
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        std::vector<Dividend> parseDividends( std::string &responseString );
        std::string convertToJson(std::vector<Dividend>& dividends);
        std::string convertEpochToDateString(int epochTime);
};