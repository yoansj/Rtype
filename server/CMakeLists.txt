project( r-type_server)
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
set(BSON_INC utils/include)
set(INC_DIR server/include)

set(SERVER_SRC
        server/main.cpp
        server/src/UdpServer.cpp
        server/src/TcpHandler.cpp
        server/src/ServerEngine.cpp
        server/src/TcpManager.cpp
        server/src/ServerGame.cpp
)


include_directories(
    ${PROJECT_SOURCE_DIR}/server/include
)

add_executable(${PROJECT_NAME} ${SERVER_SRC} ${BSON_SRC})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

configure_file(./table.txt ./bin/table.txt COPYONLY)
