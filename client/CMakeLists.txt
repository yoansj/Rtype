project(r-type_client)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-fPIC")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(RUNTIME_OUTPUT_DIRECTORY build)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/client/src/)


file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/client/main.cpp
)

file(GLOB QT_Include

)

qt5_wrap_ui(SRC "LoginPage.ui" "CreateAccountPage.ui" "UserPage.ui" "ChangeProfilPage.hpp")

include_directories(${CMAKE_INCLUDE_PATH})

include_directories(
    ${PROJECT_SOURCE_DIR}/client/include
)

add_compile_definitions(ROOT_PATH="${PROJECT_SOURCE_DIR}/")
add_executable(r-type_client ${SRC} ${QT_Include} ${BSON_SRC})
target_link_libraries(r-type_client ${CONAN_LIBS})
target_link_libraries(r-type_client Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui)
