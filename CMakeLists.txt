if(UNIX)
else()
  SET(CMAKE_C_COMPILER C:/MinGW/bin/gcc)
  SET(CMAKE_CXX_COMPILER C:/MinGW/bin/g++)
endif(UNIX)

project(R-Type)
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

cmake_minimum_required(VERSION 2.8)
include(${CMAKE_CURRENT_SOURCE_DIR}/server/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/client/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/monsters/CMakeLists.txt)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/utils/include
)