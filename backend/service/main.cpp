#include <iostream>

#include "RestServer.hpp"
#include "DatabaseManager.hpp"

int main() {

    DatabaseManager dbManager;
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    RestServer server(addr);
    server.init();
    server.start();

	while(true);
    return 0;
}
