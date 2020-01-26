#include "CassandraLogger.hpp"

CassandraLogger::CassandraLogger(char* databaseIpAddress)
{
    _databaseIpAddress = databaseIpAddress;
    _session = NULL;
    _connect_future = NULL;
    _cluster = NULL;
}

void CassandraLogger::connect() {
    /* Setup and connect to cluster */
    _connect_future = NULL;
    _cluster = cass_cluster_new();
    _session = cass_session_new();

     cass_cluster_set_protocol_version(_cluster, 3);
    /* Add contact points */
    cass_cluster_set_contact_points(_cluster, _databaseIpAddress);

    /* Provide the cluster object as configuration to connect the session */
    _connect_future = cass_session_connect(_session, _cluster);
   
    /* This operation will block until the result is ready */
    CassError rc = cass_future_error_code(_connect_future);

    if (rc != CASS_OK) {
        /* Display connection error message */
        const char* message;
        size_t message_length;
        cass_future_error_message(_connect_future, &message, &message_length);
        fprintf(stderr, "Connect error: '%.*s'\n", (int)message_length, message);
    }


}
void CassandraLogger::execute_query(char* key, char* logContent){


    
    /* There are two bind variables in the query string */
    CassStatement* statement
    = cass_statement_new("INSERT INTO test.logs (key, log_content) VALUES (?, ?)", 2);

    /* Bind the values using the indices of the bind variables */
    cass_statement_bind_string(statement, 0, key);
    cass_statement_bind_string(statement, 1, logContent);

    CassFuture* query_future = cass_session_execute(_session, statement);

    /* Statement objects can be freed immediately after being executed */
    cass_statement_free(statement);

    /* This will block until the query has finished */
    CassError rc = cass_future_error_code(query_future);
    printf("Query result: %s\n", cass_error_desc(rc));
    cass_future_free(query_future);
    

}
void CassandraLogger::disconnect() {
    cass_future_free(_connect_future);
    cass_session_free(_session);
    cass_cluster_free(_cluster);
}









