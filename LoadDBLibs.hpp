//
// Created by cmbuhler on 2020-03-11.
//

#ifndef JITSERVER_LOADDBLIBS_HPP
#define JITSERVER_LOADDBLIBS_HPP

#include <mongoc/mongoc.h>

typedef void Omongoc_init_t(void);
typedef void Omongoc_cleanup_t(void);
typedef mongoc_uri_t Omongoc_uri_t;
typedef Omongoc_uri_t * Omongoc_uri_new_with_error_t(const char *uri_string,
                                                  bson_error_t *error) BSON_GNUC_WARN_UNUSED_RESULT;

extern "C" Omongoc_init_t * Omongoc_init;
extern "C" Omongoc_cleanup_t * Omongoc_cleanup;
extern "C" Omongoc_uri_new_with_error_t * Omongoc_uri_new_with_error;

namespace JITServer
{
    void * loadLibmongoc();
    void * loadLibbson();
    void unloadDBLib(void * handle);
    void * findDBLibSymbol(void * handle, const char * sym);

    bool loadLibmongocAndSymbols();
    bool loadLibbsonAndSymbols();
}
#endif //JITSERVER_LOADDBLIBS_HPP
