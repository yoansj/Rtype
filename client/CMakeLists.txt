project(r-type_client)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_CXX_STANDARD 20)
set(MONSTERS_DIR "${PROJECT_SOURCE_DIR}/client/monsters")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/client/src/)


file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/client/*.cpp
    ${PROJECT_SOURCE_DIR}/client/src/entities/*
    ${PROJECT_SOURCE_DIR}/client/src/systems/*
    ${PROJECT_SOURCE_DIR}/client/src/engine/*
)

include_directories(${CMAKE_INCLUDE_PATH})

include_directories(
    ${PROJECT_SOURCE_DIR}/client/include/
    ${PROJECT_SOURCE_DIR}/client/include/component/
    ${PROJECT_SOURCE_DIR}/client/include/systems/
    ${PROJECT_SOURCE_DIR}/client/include/engine/
)

add_compile_definitions(ROOT_PATH="${PROJECT_SOURCE_DIR}/")
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

# Frog
add_library("frog" SHARED ${MONSTERS_DIR}/Frog.cpp)