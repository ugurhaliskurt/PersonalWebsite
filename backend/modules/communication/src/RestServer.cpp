#include "RestServer.hpp"
#include <pistache/router.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include "YahooFinanceAPI.hpp"

RestServer::RestServer(Pistache::Address addr) : endpoint(std::make_shared<Pistache::Http::Endpoint>(addr)) {}

void RestServer::init(size_t threads) {
    auto opts = Pistache::Http::Endpoint::options()
        .threads(static_cast<unsigned int>(threads))
        .flags(Pistache::Tcp::Options::ReuseAddr);

    endpoint->init(opts);
    setupRoutes();
}

void RestServer::setupRoutes() {
    using namespace Pistache::Rest;
    Routes::Get(router, "/dividends", Routes::bind(&RestServer::handleDividends, this));
    Routes::Options(router, "/dividends", Routes::bind(&RestServer::handleOptions, this));  // Handle CORS preflight
    endpoint->setHandler(router.handler());
}

void RestServer::addCORSHeaders(Pistache::Http::ResponseWriter &response) {
        response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
        response.headers().add<Pistache::Http::Header::AccessControlAllowMethods>("GET, POST, OPTIONS");
        response.headers().add<Pistache::Http::Header::AccessControlAllowHeaders>("Content-Type, Authorization");
        response.send(Pistache::Http::Code::Ok);
}

void RestServer::handleOptions(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response) {
        addCORSHeaders(response);
        response.send(Pistache::Http::Code::Ok);
}

void RestServer::start() {
    endpoint->serve();
}

void RestServer::shutdown() {
    endpoint->shutdown();
}

void RestServer::handleDividends(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    std::cout<<"this is called" << std::endl;
    // Example dividend data
    // Extract query parameters from the request
    auto symbol = request.query().get("symbol").value();
    auto startDate = request.query().get("startDate").value();

    if (symbol.empty() || startDate.empty()) {
        response.send(Pistache::Http::Code::Bad_Request, R"({"error": "Missing 'symbol' or 'startDate' parameter"})");
        return;
    }

    // Log the extracted parameters for debugging
    std::cout << "Received request for symbol: " << symbol << ", startDate: " << startDate << std::endl;

    // Call your API function with the extracted parameters
    YahooFinanceAPI yahooFApi;

    // Convert JSON data to string and send it
    response.send(Pistache::Http::Code::Ok, yahooFApi.getStockDividends(symbol, startDate));
}
