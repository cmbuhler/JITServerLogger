#ifndef JITSERVERLOGGER_MONGOLOGGER_HPP
#define JITSERVERLOGGER_MONGOLOGGER_HPP
#include <chrono>
#include <iostream>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/exception/logic_error.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

#include "BasePersistentLogger.hpp"

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

class MongoLogger : public BasePersistentLogger {
private:
    static mongocxx::instance _inst;
    mongocxx::uri _uri;
    mongocxx::client _client;
    mongocxx::database _db;

    std::string constructURI();
public:
    bool connect();
    void disconnect();
    MongoLogger(std::string databaseIP, std::string databasePort, std::string databaseName);
    MongoLogger(std::string databaseIP, std::string databasePort, std::string databaseName,
                std::string databaseUsername, std::string databasePassword);
    MongoLogger();
    ~MongoLogger();
    bool logMethod(std::string method, std::string clientID, std::string logContent);
};

#endif //JITSERVERLOGGER_MONGOLOGGER_HPP
