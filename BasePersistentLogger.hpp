#ifndef JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
#define JITSERVERLOGGER_BASEPERSISTENTLOGGER_H


class BasePersistentLogger {
protected:
    std::string _databaseIP;
    std::string _databasePort;

    virtual void connect() = 0;
    virtual void disconnect() = 0;
public:
    BasePersistentLogger(){
        _databaseIP = "127.0.0.1";
        _databasePort = "27017";
    }
    BasePersistentLogger(std::string databaseIP, std::string databasePort){
        _databaseIP = databaseIP;
        _databasePort = databasePort;
    }
    virtual bool logMethod(std::string method, std::string clientID, std::string logContent) = 0;
};

#endif //JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
