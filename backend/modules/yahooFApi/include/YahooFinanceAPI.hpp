#pragma once

#include <string.h>
#include <curl/curl.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdio.h>

#include "Interval.hpp"
#include "Formatter.hpp"
#include "utilities.hpp"

class YahooFinanceAPI
{
    public:
        YahooFinanceAPI();
        void set_interval(Interval interval);
        void set_col_name(std::string col_name);
        std::string get_ticker_data(std::string ticker, std::string start_date, std::string end_date);
        std::map<std::string, double> createUsdTlMapbyDate(const std::string& start_date);

    private:
        std::string _base_url;
        Interval _interval;
        std::string _col_name;

        std::string build_url(std::string ticker, std::string start_date, std::string end_date);
        bool string_replace(std::string& str, const std::string from, const std::string to);
        std::string download_file(std::string url);
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};