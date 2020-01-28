CC = g++
CFLAGS = -std=c++11 -Wall -g -O2
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)


all: clean compile cassandra mongo

clean:
	rm -f *.o cassandra
compile:
%.o: %.cpp
	${CC} ${CFLAGS} -c $^ -o $@

cassandra: $(OBJECTS)
	$(CC) -o cassandra $(OBJECTS) -Lcpp-build/build -lcassandra

mongo: $(OBJECTS)
	$(CC) -o mongo $(OBJECTS) -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/bsoncxx/v_noabi -L/usr/local/lib -lmongocxx -lbsoncxx