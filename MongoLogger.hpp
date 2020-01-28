#ifndef JITSERVERLOGGER_MONGOLOGGER_HPP
#define JITSERVERLOGGER_MONGOLOGGER_HPP
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
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
protected:
    void connect();
    void disconnect();
public:
    MongoLogger(char* databaseIP, char* databasePort);
    MongoLogger();
    ~MongoLogger();
    bool logMethod(char* method, char* clientID, char* logContent);
};

#endif //JITSERVERLOGGER_MONGOLOGGER_HPP
