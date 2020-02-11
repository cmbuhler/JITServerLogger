cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(openj9 LANGUAGES CXX)

# Enforce the C++ standard, and disable extensions.
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
endif()
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
add_definitions(-DMONGO_LOGGER)
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})

add_executable(mongo_test.out ./Test.cpp ./MongoLogger.cpp)

target_link_libraries(mongo_test.out
        PRIVATE ${LIBMONGOCXX_LIBRARIES}
        PRIVATE ${LIBBSONCXX_LIBRARIES})

