#include <cassandra.h>
#include <time.h>
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
        CassandraLogger(std::string const &databaseIP, std::string const &databasePort, std::string const &databaseName,
                        std::string const &databaseUsername, std::string const &databasePassword);
        CassandraLogger(std::string const &databaseIP, std::string const &databasePort, std::string const &databaseName);
        CassandraLogger();
        bool logMethod(std::string const &method, std::string const &clientID, std::string const &logContent);
       
};