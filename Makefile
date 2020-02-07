CC = g++
CFLAGS = -std=c++11 -Wall -g -O2
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)


all: clean compile
clean:
	rm -f *.o cassandra mongo
compile:
%.o: %.cpp
	$(CC) ${CFLAGS} -c $^ -o $@ -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/bsoncxx/v_noabi -DCASSANDRA_LOGGER

cassandra: $(OBJECTS)
	$(CC) -o test.out Test.o CassandraLogger.o -Lcpp-build/build -lcassandra -DCASSANDRA_LOGGER

mongo: $(OBJECTS)
	$(CC) -o test.out Test.o MongoLogger.o -L/usr/local/lib -lmongocxx -lbsoncxx -DMONGO_LOGGER

