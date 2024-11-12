#include "RestServer.hpp"
#include <pistache/router.h>
#include <iostream>
#include <nlohmann/json.hpp>

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

void RestServer::handleDividends(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response) {

    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    std::cout<<"this is called" << std::endl;
    // Example dividend data
    nlohmann::json dividendData = {
        { {"date", "2024-01-15"}, {"amount", 1.23}, {"currency", "USD"} },
        { {"date", "2024-04-15"}, {"amount", 1.35}, {"currency", "USD"} },
        { {"date", "2024-07-15"}, {"amount", 1.40}, {"currency", "USD"} }
    };

    // Convert JSON data to string and send it
    response.send(Pistache::Http::Code::Ok, dividendData.dump());
}
