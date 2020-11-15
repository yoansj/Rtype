project(r-type_client)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_CXX_STANDARD 20)
set(MONSTERS_DIR "${PROJECT_SOURCE_DIR}/monsters/src")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/client/src/)

include_directories(
    ${PROJECT_SOURCE_DIR}/client/include/systems/
    ${PROJECT_SOURCE_DIR}/engine/include/entities/
    ${PROJECT_SOURCE_DIR}/monsters/src/
)

add_library("frog" SHARED ${MONSTERS_DIR}/Frog.cpp)