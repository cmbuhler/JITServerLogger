#include "MongoLogger.hpp"
mongocxx::instance MongoLogger::_inst = mongocxx::instance{};

MongoLogger::MongoLogger(){
    _uri = mongocxx::uri("mongodb://localhost:27017");
    _client = mongocxx::client(_uri);
    connect();
}

MongoLogger::MongoLogger(char *databaseIP, char *databasePort){
    _uri = mongocxx::uri((std::string("mongodb://") + databaseIP + ":" + databasePort).c_str());
    _client = mongocxx::client(_uri);
    connect();
}

void MongoLogger::connect() {
//    TODO: Make this a constructor variable.
    _db = _client["my_test_db"];
}

void MongoLogger::disconnect() {
//    Does not actually do anything for Mongocxx!
    return;
}

bool MongoLogger::logMethod(char* method, char* clientID, char* logContent) {
    mongocxx::collection logs = _db.collection("logs"); //TODO: Name this 'table' properly
    auto builder = bsoncxx::builder::stream::document{};

    /*
     * The following constructs the following JSON structure:
     * {
     *     "method" : "method/package/methodName()",
     *     "client_id" : "clientid",
     *     "log" : "big_log"
     * }
     */
    bsoncxx::document::value doc_value = builder
            << "method" << method
            << "client_id" << clientID
            << "log" << logContent
            << bsoncxx::builder::stream::finalize;

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
            logs.insert_one(doc_value.view());

    //TODO Verify Result
    return true;
}

