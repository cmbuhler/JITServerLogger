#include "MongoLogger.hpp"
#include <chrono>
#include <iostream>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/exception/logic_error.hpp>
#include <mongocxx/stdx.hpp>

mongocxx::instance MongoLogger::_inst = mongocxx::instance{};

MongoLogger::MongoLogger(){
    _databaseIP = "127.0.0.1";
    _databasePort = "27017";
    _databaseName = "jitserver_logs";
    connect();
}

MongoLogger::MongoLogger(std::string const &databaseIP, std::string const &databasePort, std::string const &databaseName)
        : BasePersistentLogger(databaseIP, databasePort, databaseName){
    connect();
}

MongoLogger::MongoLogger(std::string const &databaseIP, std::string const &databasePort, std::string const &databaseName,
        std::string const &databaseUsername, std::string const &databasePassword)
        : BasePersistentLogger(databaseIP, databasePort, databaseName, databaseUsername, databasePassword){
    connect();
}

std::string MongoLogger::constructURI() {
    // Check if we have the database name
    std::cout << _databaseIP << std::endl;
    if(_databaseName.empty()){
        // We can not connect to an unknown database.
        return "";
    }

    // Check if we have db IP and Port
    if(_databaseIP.empty()) {
        // No IP try localhost
        _databaseIP = "127.0.0.1";
    }
    if(_databasePort.empty()) {
        // No Port try default MongoDB port
        _databasePort = "27017";
    }

    std::string host = _databaseIP + ":" + _databasePort;

    // Check if we have credentials
    std::string credentials = "";
    if(!_databaseUsername.empty()){
        if(_databasePassword.empty()){
            credentials = _databaseUsername;
        } else {
            credentials = _databaseUsername + ":" + _databasePassword;
        }
    }

    std::cout << "mongodb://" + credentials + "@" + host + "/?authSource=" + _databaseName << std::endl;
    if(credentials.empty()){
        return "mongodb://" + host + "";
    }
    return "mongodb://" + credentials + "@" + host + "/?authSource=" + _databaseName;
}

bool MongoLogger::connect() {

    try {
        _uri = mongocxx::uri(constructURI());
        _client = mongocxx::client(_uri);
        _db = _client[_databaseName];
    } catch (const mongocxx::logic_error& e) {
        std::cout << "Error configuring connection to MongoDB Server: "
            << e.what() << std::endl;
        return false;
    }

    return true;
}

void MongoLogger::disconnect() {
//  Does not actually do anything for Mongocxx
    return;
}

bool MongoLogger::logMethod(std::string const &method, std::string const &clientID, std::string const &logContent) {
    mongocxx::collection logs = _db.collection("logs"); //TODO: Name this 'table' properly
    auto builder = bsoncxx::builder::stream::document{};
    auto timestamp = std::chrono::system_clock::now();

    /*
     * The following constructs the following JSON structure:
     * {
     *     "method" : "method/package/methodName()",
     *     "client_id" : "clientid",
     *     "log" : "big_log",
     *     "timestamp" : ISODate
     * }
     */
    bsoncxx::document::value doc_value = builder
            << "method" << method
            << "client_id" << clientID
            << "log" << logContent
            << "timestamp" << bsoncxx::types::b_date(timestamp)
            << bsoncxx::builder::stream::finalize;

    try {
        bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
                logs.insert_one(doc_value.view());
    } catch (const mongocxx::bulk_write_exception& e){
        //Insert failed print why and exit for now
        //TODO: Not exit but handle properly.
        std::cout << "Error executing log insert query: "
            << e.what() << std::endl;
        return false;
    }

    return true;
}

