#pragma once

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

class RestServer {
public:
    RestServer(Pistache::Address addr);
    void init(size_t threads = 2);
    void start();
    void shutdown();
private:
    void setupRoutes();
	void handleHello(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response);
    void addCORSHeaders( Pistache::Http::ResponseWriter& response);
    void handleOptions(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response);
    std::shared_ptr<Pistache::Http::Endpoint> endpoint;
    Pistache::Rest::Router router;
};
