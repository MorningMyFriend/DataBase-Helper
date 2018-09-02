cmake_minimum_required(VERSION 3.5)
project(InterfaceRedisSQL)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

aux_source_directory(src SOURCE_FILES)

add_executable(InterfaceRedisSQL main.cpp ${SOURCE_FILES} src/structure.cpp)

target_link_libraries(InterfaceRedisSQL
        hiredis
        pqxx
        pq
        mysqlclient
        mysqlcppconn
        jsoncpp)