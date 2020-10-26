project(babel_server)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC -g3")

message(${CMAKE_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(RUNTIME_OUTPUT_DIRECTORY build)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

message("before setting up")

conan_basic_setup()

message("after setting up")


#set(NET_DIR server/src/network)
#set(DB_DIR server/src/db)
#set(INC_DIR server/include)
#set(BSON_INC utils/include)

set(SERVER_SRC
        server/main.cpp
)

message("before finding")

message("after finding")

include_directories(${CMAKE_INCLUDE_PATH} ${INC_DIR} ${BSON_INC})
add_executable(babel_server ${SERVER_SRC} ${BSON_SRC})

target_link_libraries(babel_server ${CONAN_LIBS})

configure_file(./table.txt ./bin/table.txt COPYONLY)
