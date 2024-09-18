#include <iostream>
#include <pqxx/pqxx>  // PostgreSQL C++ library

int main() {
    try {
        pqxx::connection conn("dbname=mydatabase user=user password=password host=postgres port=5432");
        if (conn.is_open()) {
            std::cout << "Connected to database!" << std::endl;
        } else {
            std::cout << "Failed to connect to database." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
