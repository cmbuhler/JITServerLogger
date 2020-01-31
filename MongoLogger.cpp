#include "MongoLogger.hpp"
mongocxx::instance MongoLogger::_inst = mongocxx::instance{};

MongoLogger::MongoLogger(){
    _uri = mongocxx::uri("mongodb://localhost:27017");
    _client = mongocxx::client(_uri);
    connect();
}

MongoLogger::MongoLogger(std::string databaseIP, std::string databasePort){
    _uri = mongocxx::uri(("mongodb://" + std::string("superuser:UserSuper@") + databaseIP + ":" + databasePort +"/?ssl=true&authSource=my_test_db").c_str());
    _client = mongocxx::client(_uri);
    connect();
}

void MongoLogger::connect() {
    _db = _client["my_test_db"];
    //return true;
}

void MongoLogger::disconnect() {
//    Does not actually do anything for Mongocxx!
    return;
}

bool MongoLogger::logMethod(std::string method, std::string clientID, std::string logContent) {
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
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}

