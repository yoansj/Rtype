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

set(INC_DIR server/include)

set(SERVER_SRC
        server/main.cpp
        server/src/UdpServer.cpp
        ${PROJECT_SOURCE_DIR}/client/src/entities/Entity.cpp
        ${PROJECT_SOURCE_DIR}/client/src/systems/PositionSystem.cpp
        ${PROJECT_SOURCE_DIR}/client/src/systems/VelocitySystem.cpp
        server/src/ServerEngine.cpp
        server/src/ServerGame.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/server/include
    ${PROJECT_SOURCE_DIR}/client/include
    ${PROJECT_SOURCE_DIR}/client/include/component
    ${PROJECT_SOURCE_DIR}/client/include/engine
    ${PROJECT_SOURCE_DIR}/client/include/systems
)

add_executable(${PROJECT_NAME} ${SERVER_SRC} ${BSON_SRC})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
