#include "DatabaseManager.hpp"
#include "iostream"

DatabaseManager::DatabaseManager()
{
    try {
        connection = std::make_unique<pqxx::connection>("dbname=mydatabase user=user password=password host=postgres port=5432");
        if (connection->is_open()) {
            std::cout << "Connected to database!" << std::endl;
        } else {
            std::cout << "Failed to connect to database." << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

DatabaseManager::~DatabaseManager()
{
    if (connection && connection->is_open()) {
        connection->disconnect();
    }
}