#ifndef JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
#define JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
#include <string>

class BasePersistentLogger {
protected:
    std::string _databaseIP;
    std::string _databasePort;
    std::string _databaseUsername;
    std::string _databasePassword;
    std::string _databaseName;

public:
    virtual bool connect() = 0;
    virtual void disconnect() = 0;
    BasePersistentLogger(){
        _databaseIP = "127.0.0.1";
        _databasePort = "";
        _databaseName = "";
        _databaseUsername = "";
        _databasePassword = "";
    }
    BasePersistentLogger(std::string databaseIP, std::string databasePort, std::string databaseName){
        _databaseIP = databaseIP;
        _databasePort = databasePort;
        _databaseName = databaseName;
        _databaseUsername = "";
        _databasePassword = "";
    }
    BasePersistentLogger(std::string databaseIP, std::string databasePort, std::string databaseName,
            std::string databaseUsername, std::string databasePassword){
        _databaseIP = databaseIP;
        _databasePort = databasePort;
        _databaseName = databaseName;
        _databaseUsername = databaseUsername;
        _databasePassword = databasePassword;
    }
    virtual bool logMethod(std::string method, std::string clientID, std::string logContent) = 0;
};

#endif //JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
