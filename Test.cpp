#include "BasePersistentLogger.hpp"

#if defined CASSANDRA_LOGGER
#include "CassandraLogger.hpp"
#define DEFAULT_PORT 9042
typedef CassandraLogger PersistentLogger;

#elif defined MONGO_LOGGER
#include "MongoLogger.hpp"
#define DEFAULT_PORT 27017
typedef MongoLogger PersistentLogger;

#else
#error Please specify one of compile variables MONGO_LOGGER CASSANDRA_LOGGER to enable Persistent Logging
#endif

int main() {
    auto* logger = new PersistentLogger("127.0.0.1", DEFAULT_PORT, "jitserver_logs", "jitlogger", "jitlogger");
    std::uint64_t clientID = 570241675495946978;
    std::string method = "java/util/Hashtable()";
    if(logger->connect()){
        std::string logs =  "\
        0x7f38af800194 00000134 [0x7f38c13565f0] 48 83 7d 50 ff \
        cmpqword ptr [rbp+0x50], 0xffffffffffffffff	# CMP8MemImms, \
        SymRef  stackOverflowMark[#455  MethodMeta +80] [flags 0x200 0x0 ]\
        0x7f38af800199 00000139 [0x7f38c1356740]                                    Label L0081:			# LABEL	# (Start of internal control flow)\
        0x7f38af800199 00000139 [0x7f38c1380590]                                    vfpSave			# AdjustFramePtr\
        0x7f38af800199 00000139 [0x7f38c13567e0] 0f 84 d1 01 00 00                  je	Outlined Label L0080			# JE4\
        0x7f38af80019f 0000013f [0x7f38c1356bd0]  Label L0082:			# LABEL	# (End of internal control flow)";

        logger->logMethod(method, clientID, logs);
        logger->disconnect();
    }

    if(logger->connect()){
        logger->logMethod(method, clientID, "another log");
        logger->disconnect();
    }

    return 0;
}