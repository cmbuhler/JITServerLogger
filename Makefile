CC = g++
CFLAGS = -std=c++11 -Wall -g -O2
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)


all: clean compile cassandra mongo
cassandra: CassandraLogger.o CassTest.o
	$(CC) -o cass_test.out CassTest.o CassandraLogger.o -Lcpp-build/build -lcassandra -DCASSANDRA_LOGGER

mongo: MongoLogger.o MongoTest.o LoadDBLibs.o
	$(CC) MongoTest.o MongoLogger.o LoadDBLibs.o -L/usr/local/lib -ldl -lmongoc-1.0 -lbson-1.0 -o mongo_test.out -DMONGO_LOGGER

clean:
	rm -f *.o *.out *.gch

compile: MongoLogger.o MongoTest.o CassandraLogger.o CassTest.o LoadDBLibs.o
MongoLogger.o: MongoLogger.cpp
	$(CC) ${CFLAGS} -c $^ -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0

CassandraLogger.o: CassandraLogger.cpp
	$(CC) ${CFLAGS} -c $^

CassTest.o: Test.cpp
	$(CC) ${CFLAGS} -c $^ -o $@ -DCASSANDRA_LOGGER

MongoTest.o: Test.cpp
	$(CC) ${CFLAGS} -c $^ -o $@ -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0 -DMONGO_LOGGER

LoadDBLibs.o: LoadDBLibs.cpp
	$(CC) ${CFLAGS} -c $^ -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/libbson-1.0