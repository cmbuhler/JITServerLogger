#include "CassandraLogger.hpp"
int main() {
    
    CassandraLogger* logger = new CassandraLogger();
    logger->connect();
    string logs =  "\
    0x7f38af800194 00000134 [0x7f38c13565f0] 48 83 7d 50 ff \
    cmpqword ptr [rbp+0x50], 0xffffffffffffffff	# CMP8MemImms, \
    SymRef  stackOverflowMark[#455  MethodMeta +80] [flags 0x200 0x0 ]\
    0x7f38af800199 00000139 [0x7f38c1356740]                                    Label L0081:			# LABEL	# (Start of internal control flow)\
    0x7f38af800199 00000139 [0x7f38c1380590]                                    vfpSave			# AdjustFramePtr\
    0x7f38af800199 00000139 [0x7f38c13567e0] 0f 84 d1 01 00 00                  je	Outlined Label L0080			# JE4\
    0x7f38af80019f 0000013f [0x7f38c1356bd0]  Label L0082:			# LABEL	# (End of internal control flow)";
    string clientID = "570241675495946978";
    string method = "java/util/Hashtable.put(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;";
    logger->logMethod(method, clientID, logs);
    logger->disconnect();
    logger->connect();
    logger->logMethod(method, clientID, "another log");
    logger->disconnect();
    return 0;




}