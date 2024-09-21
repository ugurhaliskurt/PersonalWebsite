#pragma once

#include <pqxx/pqxx>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
private:
    std::unique_ptr<pqxx::connection> connection;
};