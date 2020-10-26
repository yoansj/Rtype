if(UNIX)
else()
  SET(CMAKE_C_COMPILER C:/MinGW/bin/gcc)
  SET(CMAKE_CXX_COMPILER C:/MinGW/bin/g++)
endif(UNIX)

project(R-Type)
cmake_minimum_required(VERSION 2.8.12)
# cmake_minimum_required(VERSION 2.8)
# set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB BSON_SRC
  utils/src/bson/Bson.cpp
  utils/src/bson/Bson_Value.cpp
  utils/src/bson/BsonBufferFunctions.cpp
	utils/src/bson/BsonIterator.cpp
  utils/src/bson/message.cpp
  utils/include/BsonException.cpp
)

cmake_minimum_required(VERSION 2.8)
include(${CMAKE_CURRENT_SOURCE_DIR}/server/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/client/CMakeLists.txt)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/utils/include
)
