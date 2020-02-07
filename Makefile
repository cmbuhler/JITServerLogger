CC = g++
CFLAGS = -std=c++11 -Wall -g -O2
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)


all: clean compile cassandra mongo
cassandra: CassandraLogger.o CassTest.o
	$(CC) -o cass_test.out CassTest.o CassandraLogger.o -Lcpp-build/build -lcassandra -DCASSANDRA_LOGGER

mongo: MongoLogger.o MongoTest.o
	$(CC) -o mongo_test.out MongoTest.o MongoLogger.o -L/usr/local/lib -lmongocxx -lbsoncxx -DMONGO_LOGGER

clean:
	rm -f *.o *.out *.gch

compile: MongoLogger.o MongoTest.o CassandraLogger.o CassTest.o
MongoLogger.o: MongoLogger.cpp
	$(CC) ${CFLAGS} -c $^ -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/bsoncxx/v_noabi

CassandraLogger.o: CassandraLogger.cpp
	$(CC) ${CFLAGS} -c $^

CassTest.o: Test.cpp
	$(CC) ${CFLAGS} -c $^ -o $@ -DCASSANDRA_LOGGER

MongoTest.o: Test.cpp
	$(CC) ${CFLAGS} -c $^ -o $@ -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/bsoncxx/v_noabi -DMONGO_LOGGER