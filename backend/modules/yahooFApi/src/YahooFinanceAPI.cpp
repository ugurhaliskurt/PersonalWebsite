#include "YahooFinanceAPI.hpp"
#include <nlohmann/json.hpp>

YahooFinanceAPI::YahooFinanceAPI() {
}

std::string YahooFinanceAPI::convertEpochToDateString(int epochTime) {
    std::time_t time = epochTime;
    std::tm* tm_ptr = std::gmtime(&time); // Convert epoch time to UTC time structure

    // Format the date as YYYY-MM-DD
    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%Y-%m-%d");
    return oss.str();
}

std::string YahooFinanceAPI::getStockDividends(std::string& stockSymbol, std::string& range) {
    try {
        std::string url = "https://query1.finance.yahoo.com/v8/finance/chart/" + stockSymbol + "?range=" + range +"y&interval=1mo&events=div%7Csplit&events=history";
        auto responseString = download_file(url);
        auto dividends = parseDividends(responseString);
        return convertToJson(dividends);
    } catch (const std::exception& e) {
        return "";
    } catch (...) {
        return "";
    }
}


size_t YahooFinanceAPI::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    try {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    } catch (const std::exception& e) {
        return 0;
    } catch (...) {
        return 0;
    }
}

std::string YahooFinanceAPI::download_file(std::string& url) {
    try {
        CURL* curl;
        CURLcode res;
        curl = curl_easy_init();
        std::string readBuffer;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Disable SSL verification for testing
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3");
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            }
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return "";
    }
}

std::vector<Dividend> YahooFinanceAPI::parseDividends( std::string &responseString )
{
    std::vector<Dividend> result;
    try {
        auto jsonData = nlohmann::json::parse(responseString);
        // Extract dividend data (this depends on Yahoo Finance's actual response format)
        if (jsonData.contains("chart") && jsonData["chart"].contains("result")) {
            auto dividends = jsonData["chart"]["result"][0]["events"]["dividends"];
            if (!dividends.empty()) {
                for (auto& [key, dividend] : dividends.items()) {
                    // Convert numeric types to strings
                    std::string dateStr = convertEpochToDateString(dividend["date"].get<int>());
                    std::string amountStr = std::to_string(dividend["amount"].get<double>());
                    result.emplace_back(Dividend(dateStr, amountStr));
                    std::cout << "Date: " << dividend["date"] << ", Amount: " << dividend["amount"] << "\n";
                }
            } else {
                std::cout << "No dividend data found for .\n";
            }
        }
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    return result;
}

std::string YahooFinanceAPI::convertToJson(std::vector<Dividend>& dividends)
{
    nlohmann::json jsonDividends = nlohmann::json::array();
    
    for (const auto& dividend : dividends) {
        jsonDividends.push_back({
            {"date", dividend.date},
            {"amount", std::stod(dividend.amount)}, // Convert string to double
            {"currency", dividend.currency}
        });
    }
    return jsonDividends.dump();
}