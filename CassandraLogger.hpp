#include <cassandra.h>
#include <iostream>
#include "BasePersistentLogger.hpp"
using namespace std;
class CassandraLogger : public BasePersistentLogger {

    private:
        CassCluster* _cluster;
        CassSession* _session;
        CassFuture* _connectFuture;
        bool createKeySpace(string keyspace);
        bool createTable(string keyspace, string tableName);
        
    public: 
        bool connect();
        void disconnect();
        CassandraLogger(std::string databaseIP, std::string databasePort, std::string databaseName,
                        std::string databaseUsername, std::string databasePassword);
        CassandraLogger(std::string databaseIP, std::string databasePort, std::string databaseName);
        CassandraLogger();
        bool logMethod(std::string method, std::string clientID, std::string logContent);
       
};