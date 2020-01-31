#ifndef JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
#define JITSERVERLOGGER_BASEPERSISTENTLOGGER_H


class BasePersistentLogger {
protected:
    std::string _databaseIP;
    std::string _databasePort;
    std::string _databaseUsername;
    std::string _databasePassword;
    std::string _databaseName;

    virtual void connect() = 0;
    virtual void disconnect() = 0;
public:
    BasePersistentLogger(){
        _databaseIP = "127.0.0.1";
        _databasePort = "";
    }
    BasePersistentLogger(std::string databaseIP, std::string databasePort, std::string databaseName){
        _databaseIP = databaseIP;
        _databasePort = databasePort;
        _databaseName = databaseName;
        _databaseUsername = nullptr;
        _databasePassword = nullptr;
    }
    BasePersistentLogger(std::string databaseIP, std::string databasePort, std::string databaseName,
            std::string databaseUsername, std::string databasePassword){
        _databaseIP = databaseIP;
        _databasePort = databasePort;
    }
    virtual bool logMethod(std::string method, std::string clientID, std::string logContent) = 0;
};

#endif //JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
