#include "yfapi.hpp"

namespace yfapi {

YahooFinanceAPI::YahooFinanceAPI() {
    this->_base_url =
        "https://query1.finance.yahoo.com/v8/finance/chart/{ticker}?period1={start_time}&period2={end_time}&interval={interval}&events=div%7Csplit&events=history";
    this->_interval = DAILY;
    this->_col_name = "Open";
}

bool YahooFinanceAPI::string_replace(std::string& str, const std::string from, const std::string to) {
    try {
        size_t start = str.find(from);
        if (start == std::string::npos) {
            return false;
        }
        str.replace(start, from.length(), to);
        return true;
    } catch (const std::exception& e) {
        spdlog::error("Exception in string_replace: {}", e.what());
        return false;
    } catch (...) {
        spdlog::error("Unknown exception in string_replace");
        return false;
    }
}

std::string YahooFinanceAPI::build_url(std::string ticker, std::string start_date, std::string end) {
    try {
        std::string url = this->_base_url;
        string_replace(url, "{ticker}", ticker);
        string_replace(url, "{start_time}", std::to_string(Formatter::dateStringToEpoch(start_date)));
        string_replace(url, "{end_time}", std::to_string(Formatter::dateStringToEpoch(end)));
        string_replace(url, "{interval}", get_api_interval_value(this->_interval));
        return url;
    } catch (const std::exception& e) {
        spdlog::error("Exception in build_url: {}", e.what());
        return "";
    } catch (...) {
        spdlog::error("Unknown exception in build_url");
        return "";
    }
}

void YahooFinanceAPI::set_interval(Interval interval) {
    try {
        this->_interval = interval;
    } catch (const std::exception& e) {
        spdlog::error("Exception in set_interval: {}", e.what());
    } catch (...) {
        spdlog::error("Unknown exception in set_interval");
    }
}

void YahooFinanceAPI::set_col_name(std::string name) {
    try {
        this->_col_name = name;
    } catch (const std::exception& e) {
        spdlog::error("Exception in set_col_name: {}", e.what());
    } catch (...) {
        spdlog::error("Unknown exception in set_col_name");
    }
}

size_t YahooFinanceAPI::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    try {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    } catch (const std::exception& e) {
        spdlog::error("Exception in WriteCallback: {}", e.what());
        return 0;
    } catch (...) {
        spdlog::error("Unknown exception in WriteCallback");
        return 0;
    }
}

std::string YahooFinanceAPI::download_file(std::string url) {
    try {
        CURL* curl;
        CURLcode res;
        curl = curl_easy_init();
        std::string readBuffer;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    } catch (const std::exception& e) {
        spdlog::error("Exception in download_file: {}", e.what());
        return "";
    } catch (...) {
        spdlog::error("Unknown exception in download_file");
        return "";
    }
}

std::string YahooFinanceAPI::get_ticker_data(std::string ticker, std::string start_date, std::string end) {
    try {
        std::string url = build_url(ticker, start_date, end);
        std::time_t now = std::time(0);
        return download_file(url);
    } catch (const std::exception& e) {
        spdlog::error("Exception in get_ticker_data: {}", e.what());
        return "";
    } catch (...) {
        spdlog::error("Unknown exception in get_ticker_data");
        return "";
    }
}

std::map<std::string, double> YahooFinanceAPI::createUsdTlMapbyDate(const std::string& start_date) {
    try {
        auto current_date = getCurrentDate();
        std::string usdTl = get_ticker_data("TRY=X", start_date, current_date);
        return Formatter::convertDateValueMap(usdTl);
    } catch (const std::exception& e) {
        spdlog::error("Exception in createUsdTlMapbyDate: {}", e.what());
        return {};
    } catch (...) {
        spdlog::error("Unknown exception in createUsdTlMapbyDate");
        return {};
    }
}

}  // namespace yfapi