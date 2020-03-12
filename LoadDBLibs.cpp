//
// Created by cmbuhler on 2020-03-11.
//
#include "LoadDBLibs.hpp"

#include <dlfcn.h>
#include <iostream>

Omongoc_init_t * Omongoc_init = NULL;
Omongoc_cleanup_t * Omongoc_cleanup = NULL;
Omongoc_uri_new_with_error_t * Omongoc_uri_new_with_error = NULL;

namespace JITServer
{
    void * loadLibmongoc()
    {
        void *result = NULL;
        result = dlopen("libmongoc-1.0.so", RTLD_NOW);
        return result;
    }

    void unloadDBLib(void * handle)
    {
        (void)dlclose(handle);
    }

    void * findDBLibSymbol(void * handle, const char * sym)
    {
        return dlsym(handle, sym);
    }

    bool loadLibmongocAndSymbols()
    {
        void *handle = NULL;

        handle = loadLibmongoc();
        if(!handle)
        {
            printf("#JITServer: Failed to load libmongoc\n");
            return false;
        }

        Omongoc_init = (Omongoc_init_t *)findDBLibSymbol(handle, "mongoc_init");
        Omongoc_cleanup = (Omongoc_cleanup_t *)findDBLibSymbol(handle, "mongoc_cleanup");
        Omongoc_uri_new_with_error = (Omongoc_uri_new_with_error_t *)findDBLibSymbol(handle, "mongoc_uri_new_with_error");

        if(
                (Omongoc_init == NULL) ||
                (Omongoc_cleanup == NULL) ||
                (Omongoc_uri_new_with_error == NULL)
                )
        {
            printf("#JITServer: Failed to load all the required Mongoc symbols\n");
            unloadDBLib(handle);
        }

        return true;
    }
}