//
// Created by cmbuhler on 2020-01-26.
//
#include <iostream>

#include "MongoLogger.hpp"

int main(int, char**) {
    //Open new connection to mongo on localhost port 27017.
//    BasePersistentLogger* logger;
//    MongoLogger* mongo = new MongoLogger("127.0.0.1", "27017", "jitserver_logs", "jitlogger", "jitlogger");
//    logger = mongo;
//
//    char * logs =  "0x7f38af800194 00000134 [0x7f38c13565f0] 48 83 7d 50 ff \
//    cmpqword ptr [rbp+0x50], 0xffffffffffffffff	# CMP8MemImms, \
//    SymRef  stackOverflowMark[#455  MethodMeta +80] [flags 0x200 0x0 ]\
//    0x7f38af800199 00000139 [0x7f38c1356740]                                    Label L0081:			# LABEL	# (Start of internal control flow)\
//    0x7f38af800199 00000139 [0x7f38c1380590]                                    vfpSave			# AdjustFramePtr\
//    0x7f38af800199 00000139 [0x7f38c13567e0] 0f 84 d1 01 00 00                  je	Outlined Label L0080			# JE4\
//    0x7f38af80019f 0000013f [0x7f38c1356bd0]  Label L0082:			# LABEL	# (End of internal control flow)";
//
//    char * clientID = "570241675495946978";
//    char * method = "java/util/Hashtable;";
//
//    logger->logMethod(method, clientID, logs);
    return 0;
}
