CC = g++
CFLAGS = -std=c++11 -Wall -g -O2
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)


all: clean compile cassandra mongo
clean:
	rm -f *.o cassandra mongo
compile:
%.o: %.cpp
	$(CC) ${CFLAGS} -c $^ -o $@ -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/bsoncxx/v_noabi

cassandra: $(OBJECTS)
	$(CC) -o cassandra Test.o CassandraLogger.o -Lcpp-build/build -lcassandra

mongo: $(OBJECTS)
	$(CC) -o mongo test.o MongoLogger.o -L/usr/local/lib -lmongocxx -lbsoncxx

