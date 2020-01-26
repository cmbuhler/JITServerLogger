#include <cassandra.h>
#include <iostream>
using namespace std;
class CassandraLogger {

    private:
    CassCluster* _cluster;
    CassSession* _session;
    CassFuture* _connect_future;
    char * _databaseIpAddress;
    public:
        CassandraLogger(char* databaseIpAddress);
        void execute_query(char* key, char* logContent);
        void connect();
        void disconnect();
        void setCassCluster(CassCluster* cluster);
        void setCassSession(CassSession* session);
        void setCassFuture(CassFuture* connect_future);
        CassCluster * getCassCluster();
        CassSession * getCassSession();
        CassFuture * getCassFuture();
};