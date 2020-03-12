#include "MongoLogger.hpp"
#include <ctime>
#include <iostream>
#include <mongoc/mongoc.h>

MongoLogger::MongoLogger(std::string const &databaseIP, std::uint32_t databasePort, std::string const &databaseName)
        : BasePersistentLogger(databaseIP, databasePort, databaseName){

}

MongoLogger::MongoLogger(std::string const &databaseIP, std::uint32_t databasePort, std::string const &databaseName,
        std::string const &databaseUsername, std::string const &databasePassword)
        : BasePersistentLogger(databaseIP, databasePort, databaseName, databaseUsername, databasePassword){

}

MongoLogger::~MongoLogger() {
    //Clean up this mongoc logger.
    mongoc_collection_destroy(_collection);
    mongoc_database_destroy(_db);
    mongoc_uri_destroy(_uri);
    mongoc_client_destroy(_client);
}

std::string MongoLogger::constructURI() {
    // Check if we have the database name
    if(_databaseName.empty()){
        return "jitserver_logs";
    }

    // Check if we have db IP and Port
    if(_databaseIP.empty()) {
        // No IP try localhost
        _databaseIP = "127.0.0.1";
    }
    if(!_databasePort) {
        // No Port try default MongoDB port
        _databasePort = 27017;
    }

    std::string host = _databaseIP + ":" + std::to_string(_databasePort);

    // Check if we have credentials
    std::string credentials = "";
    if(!_databaseUsername.empty()){
        if(_databasePassword.empty()){
            credentials = _databaseUsername;
        } else {
            credentials = _databaseUsername + ":" + _databasePassword;
        }
    }

    if(credentials.empty()){
        return "mongodb://" + host + "";
    }
    return "mongodb://" + credentials + "@" + host + "/?authSource=" + _databaseName;
}

bool MongoLogger::connect() {
    bson_error_t error;

    //Validate URI.
    _uri = Omongoc_uri_new_with_error(constructURI().c_str(), &error);
    if (!_uri) {
        fprintf (stderr,
                 "JITServer: Persistent Logger failed to parse URI: %s\n"
                 "error message:       %s\n",
                 constructURI().c_str(),
                 error.message);
        return false;
    }

    //Create a client
    _client = mongoc_client_new_from_uri(_uri);
    if(!_client){
        return false;
    }

    //Register the application name so we can track it in the profile logs
    //on the server if we want.
    mongoc_client_set_appname(_client, "jitserver");

    //Get a handle on the database and collection.
    _db = mongoc_client_get_database(_client, _databaseName.c_str());
    _collection = mongoc_client_get_collection (_client, _databaseName.c_str(), "logs");

    //Mongo is designed to be always available. Thus there is no "Connection" object
    //and you will find that the "Connection" is tested on every read/write.
    return true;
}

void MongoLogger::disconnect() {
    //Does not actually do anything for Mongo as noted in connect()
    return;
}

bool MongoLogger::logMethod(std::string const &method, std::uint64_t clientID, std::string const &logContent) {
    std::time_t timestamp = time(nullptr);
    /*
     * The following constructs and inserts the following JSON structure:
     * {
     *     "method" : "method/package/methodName()",
     *     "client_id" : "clientid",
     *     "log" : "big_log",
     *     "timestamp" : ISODate
     * }
     */
    bson_t *insert;
    bson_error_t error;

    insert = BCON_NEW (
            "method", BCON_UTF8(method.c_str()),
            "client_id", BCON_UTF8(std::to_string(clientID).c_str()),
            "log", BCON_UTF8(logContent.c_str()),
            "timestamp", BCON_DATE_TIME(timestamp)
    );

    if (!mongoc_collection_insert_one(_collection, insert, NULL, NULL, &error)) {
        fprintf(stderr, "JITServer: Mongo Logger failed to insert log.\n"
                        "error message: %s\n", error.message);
    }

    bson_destroy (insert);

    return true;
}

