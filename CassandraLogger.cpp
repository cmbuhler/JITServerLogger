#include "CassandraLogger.hpp"
CassandraLogger::CassandraLogger(std::string databaseIP, std::string databasePort, std::string databaseName): BasePersistentLogger(databaseIP, databasePort, databaseName){
    _session = NULL;
    _connectFuture = NULL;
    _cluster = NULL;
}

CassandraLogger::CassandraLogger(): BasePersistentLogger(){
    _session = NULL;
    _connectFuture = NULL;
    _cluster = NULL;
    _databasePort = "9042";
}

CassandraLogger::CassandraLogger(std::string databaseIP, std::string databasePort,
        std::string databaseName, std::string databaseUsername, std::string databasePassword)
        : BasePersistentLogger(databaseIP, databasePort, databaseName, databaseUsername, databasePassword){
    _session = NULL;
    _connectFuture = NULL;
    _cluster = NULL;
}

bool CassandraLogger::createKeySpace(string keyspace) {
    string queryString = "CREATE KEYSPACE IF NOT EXISTS " + keyspace + " WITH REPLICATION = {'class':'SimpleStrategy','replication_factor':1};";
    CassStatement* statement = cass_statement_new(queryString.c_str(), 0);

    CassFuture* queryFuture = cass_session_execute(_session, statement);
    cass_statement_free(statement);
    if (cass_future_error_code(queryFuture) != CASS_OK) {
        /* Display connection error message */
        const char* message;
        size_t messageLength;
        cass_future_error_message(queryFuture, &message, &messageLength);
        fprintf(stderr, "keyspace creation error: '%.*s'\n", (int)messageLength, message);
        
        cass_future_free(queryFuture);
        return false;
    }

    cass_future_free(queryFuture);
    return true;

}
bool CassandraLogger::createTable(string keyspace, string table_name) {
   
    string queryString = "CREATE TABLE IF NOT EXISTS " + keyspace + "." + table_name + " (clientID text, methodName text, logContent text, insertionDate date,insertionTime time, primary key (clientID, methodName, insertionDate, insertionTime));";
    CassStatement* statement = cass_statement_new(queryString.c_str(), 0);

    CassFuture* queryFuture = cass_session_execute(_session, statement);
    cass_statement_free(statement);
    if (cass_future_error_code(queryFuture) != CASS_OK) {
        /* Display connection error message */
        const char* message;
        size_t messageLength;
        cass_future_error_message(queryFuture, &message, &messageLength);
        fprintf(stderr, "table creation error: '%.*s'\n", (int)messageLength, message);
        
        cass_future_free(queryFuture);
        return false;
    }

    cass_future_free(queryFuture);
    return true;





}
bool CassandraLogger::connect() {
    /* Setup and connect to cluster */
    _cluster = cass_cluster_new();
    _session = cass_session_new();

    /*Set protocol version */
    CassError rc_set_protocol = cass_cluster_set_protocol_version(_cluster, 4);
    if (rc_set_protocol != CASS_OK) {
        cout << cass_error_desc(rc_set_protocol) << endl;
        return false;

    }

    /* Add contact points */
    CassError rc_set_ip = cass_cluster_set_contact_points(_cluster, _databaseIP.c_str());
    if (rc_set_ip != CASS_OK) {
        cout << cass_error_desc(rc_set_ip) << endl;
        return false;

    }

    /*Set port number*/
    CassError rc_set_port = cass_cluster_set_port(_cluster, stoi(_databasePort));
    if (rc_set_port != CASS_OK) {
        cout << cass_error_desc(rc_set_port) << endl;
        return false;

    }

    /* Provide the cluster object as configuration to connect the session */
    _connectFuture = cass_session_connect(_session, _cluster);
   
    if (cass_future_error_code(_connectFuture) != CASS_OK) {
        /* Display connection error message */
        const char* message;
        size_t messageLength;
        cass_future_error_message(_connectFuture, &message, &messageLength);
        fprintf(stderr, "Connect error: '%.*s'\n", (int)messageLength, message);
        return false;
    }
    return true;

}


bool CassandraLogger::logMethod(std::string method, std::string clientID, std::string logContent){
    
    // create table space and table first
    if (!createKeySpace("test")) return false;
    if (!createTable("test","logs")) return false;

    
    CassStatement* statement
    = cass_statement_new("INSERT INTO test.logs (clientID, methodName, logContent, insertionDate, insertionTime) VALUES (?, ?, ?, ?, ?)", 5);

    /* Bind the values using the indices of the bind variables */
    CassError rc_set_bind_pk = cass_statement_bind_string(statement, 0, clientID.c_str());
    if (rc_set_bind_pk != CASS_OK) {
        cout << cass_error_desc(rc_set_bind_pk) << endl;
        cass_statement_free(statement);
        return false;
    }

    CassError rc_set_bind_method = cass_statement_bind_string(statement, 1, method.c_str());
    if (rc_set_bind_pk != CASS_OK) {
        cout << cass_error_desc(rc_set_bind_method) << endl;
        cass_statement_free(statement);
        return false;
    }
    CassError rc_set_bind_log_content = cass_statement_bind_string(statement, 2, logContent.c_str());

     if (rc_set_bind_log_content != CASS_OK) {
        cout << cass_error_desc(rc_set_bind_log_content) << endl;
        cass_statement_free(statement);
        return false;
    }

    time_t now = time(NULL); /* Time in seconds from Epoch */
    /* Converts the time since the Epoch in seconds to the 'date' type */
    cass_uint32_t year_month_day_of_insertion = cass_date_from_epoch(now);
    /* Converts the time since the Epoch in seconds to the 'time' type */
    cass_int64_t time_of_insertion = cass_time_from_epoch(now);

    /* 'date' uses an unsigned 32-bit integer */
    CassError rc_set_bind_insertion_date = cass_statement_bind_uint32(statement, 3, year_month_day_of_insertion);
    
    if (rc_set_bind_insertion_date != CASS_OK) {
        cout << cass_error_desc(rc_set_bind_insertion_date) << endl;
        cass_statement_free(statement);
        return false;
    }
    /* 'time' uses a signed 64-bit integer */
    CassError rc_set_bind_insertion_time = cass_statement_bind_int64(statement, 4, time_of_insertion);
    if (rc_set_bind_insertion_time != CASS_OK) {
        cout << cass_error_desc(rc_set_bind_insertion_time) << endl;
        cass_statement_free(statement);
        return false;
    }

    CassFuture* queryFuture = cass_session_execute(_session, statement);

    /* Statement objects can be freed immediately after being executed */
    cass_statement_free(statement);
    if (cass_future_error_code(queryFuture) != CASS_OK) {
        /* Display connection error message */
        const char* message;
        size_t messageLength;
        cass_future_error_message(queryFuture, &message, &messageLength);
        fprintf(stderr, "query execution error: '%.*s'\n", (int)messageLength, message);
        cass_future_free(queryFuture);
        return false;
    }

    cass_future_free(queryFuture);
    return true;
    

}


void CassandraLogger::disconnect() {
    cass_future_free(_connectFuture);
    cass_session_free(_session);
    cass_cluster_free(_cluster);
}









