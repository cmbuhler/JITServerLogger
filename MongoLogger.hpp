#ifndef MONGOLOGGER_HPP
#define MONGOLOGGER_HPP

#include "BasePersistentLogger.hpp"
#include <mongoc/mongoc.h>
#include "LoadDBLibs.hpp"

class MongoLogger : public BasePersistentLogger {
private:
    Omongoc_uri_t *_uri;
    mongoc_client_t *_client;
    mongoc_database_t *_db;
    mongoc_collection_t *_collection;

    std::string constructURI();
public:
    bool connect();
    void disconnect();
    MongoLogger(std::string const &databaseIP, std::uint32_t databasePort, std::string const &databaseName);
    MongoLogger(std::string const &databaseIP, std::uint32_t databasePort, std::string const &databaseName,
                std::string const &databaseUsername, std::string const &databasePassword);
    MongoLogger();
    ~MongoLogger();
    bool logMethod(std::string const &method, std::uint64_t clientID, std::string const &logContent);
};

#endif //MONGOLOGGER_HPP
