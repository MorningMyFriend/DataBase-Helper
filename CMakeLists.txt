cmake_minimum_required(VERSION 3.5)
project(InterfaceRedisSQL)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

aux_source_directory(src SOURCE_FILES)
#
#add_executable(InterfaceRedisSQL main_old.cpp ${SOURCE_FILES} src/structure.cpp include/interface_database.h include/implementation_database.cpp include/implementation_database.h src/main.cpp)
#
#target_link_libraries(InterfaceRedisSQL
#        hiredis
#        pqxx
#        pq
#        mysqlclient
#        mysqlcppconn
#        jsoncpp)

add_executable(main main.cpp include/interface_database.h ${SOURCE_FILES})
target_link_libraries(main
        hiredis
        mysqlclient
        mysqlcppconn)