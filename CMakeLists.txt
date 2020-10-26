cmake_policy(VERSION 3.10)
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(OOP_indie_studio_2019 VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(Irrlicht_DIR ${Irrlicht_DIR} "${PROJECT_SOURCE_DIR}/lib/irrlicht")
add_compile_definitions(ROOT_PATH="${PROJECT_SOURCE_DIR}/")

file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/bomb/*.cpp
    ${PROJECT_SOURCE_DIR}/src/bonus/*.cpp
    ${PROJECT_SOURCE_DIR}/src/engine/*.cpp
    ${PROJECT_SOURCE_DIR}/src/map/*.cpp
    ${PROJECT_SOURCE_DIR}/src/object/*.cpp
    ${PROJECT_SOURCE_DIR}/src/player/*.cpp
    ${PROJECT_SOURCE_DIR}/src/scene/*.cpp
    ${PROJECT_SOURCE_DIR}/src/sound/*.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/*.cpp
)

add_executable(bomberman ${SRC})

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/bomb
    ${PROJECT_SOURCE_DIR}/include/bonus
    ${PROJECT_SOURCE_DIR}/include/engine
    ${PROJECT_SOURCE_DIR}/include/map
    ${PROJECT_SOURCE_DIR}/include/object
    ${PROJECT_SOURCE_DIR}/include/player
    ${PROJECT_SOURCE_DIR}/include/scene
    ${PROJECT_SOURCE_DIR}/include/sound
    ${PROJECT_SOURCE_DIR}/include/utils
)

if(MSVC)
    target_compile_definitions(bomberman PRIVATE WIN)
    include_directories(
        ${Irrlicht_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/lib
    )
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    target_link_libraries (bomberman
        ${PROJECT_SOURCE_DIR}/bin/ogg.lib
        ${PROJECT_SOURCE_DIR}/bin/openal32.lib
        ${PROJECT_SOURCE_DIR}/bin/sfml-audio.lib
        ${PROJECT_SOURCE_DIR}/bin/sfml-audio-d.lib
        ${PROJECT_SOURCE_DIR}/bin/sfml-audio-s.lib
        ${PROJECT_SOURCE_DIR}/bin/sfml-audio-s-d.lib
        ${PROJECT_SOURCE_DIR}/bin/sfml-system.lib
        ${PROJECT_SOURCE_DIR}/bin/sfml-system-d.lib
        ${PROJECT_SOURCE_DIR}/bin/sfml-system-s.lib
        ${PROJECT_SOURCE_DIR}/bin/sfml-system-s-d.lib
      )
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
    find_package(SFML 2 COMPONENTS audio)
    include_directories(
        ${SFML_INCLUDE_DIR}
    )
    target_link_libraries (bomberman
        ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} /usr/lib/x86_64-linux-gnu/libsfml-audio.so
    )
endif()


find_package (Threads)
find_package (Irrlicht)

target_link_libraries (bomberman
    ${CMAKE_THREAD_LIBS_INIT}
    ${Irrlicht_LIBRARIES}
)
