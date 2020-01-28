#ifndef JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
#define JITSERVERLOGGER_BASEPERSISTENTLOGGER_H


class BasePersistentLogger {
protected:
    char * _databaseIP;
    char * _databasePort;

    virtual void connect();
    virtual void disconnect();
public:
    virtual bool logMethod(char* method, char* clientID, char* logContent);
};

#endif //JITSERVERLOGGER_BASEPERSISTENTLOGGER_H
