#include "RestServer.hpp"
#include <pistache/router.h>
#include <iostream>

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
    Routes::Get(router, "/hello", Routes::bind(&RestServer::handleHello, this));
    Routes::Options(router, "/hello", Routes::bind(&RestServer::handleOptions, this));  // Handle CORS preflight
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

void RestServer::handleHello(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response) {
    response.headers().add<Pistache::Http::Header::AccessControlAllowOrigin>("*");
    std::cout<<"this is called" << std::endl;
    response.send(Pistache::Http::Code::Ok, R"({"message": "Hello from C++!"})");
    // Set Content-Type header to JSON (example)
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
}
