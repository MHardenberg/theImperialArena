cmake_minimum_required(VERSION 3.10)
project(ImperialArena)

# Building
# set(CMAKE_BUILD_TYPE "Debug")
# Define a preprocessor macro based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Common settings
set(CMAKE_CC_COMPILER gcc)
set(CMAKE_CC_STANDARD 17)
set(CMAKE_CC_FLAGS "-Wall -Wpedantic -Wextra ")
set(CMAKE_CC_FLAGS_DEBUG "${CMAKE_CC_FLAGS} -fsanitize=address -O0 -g")
set(CMAKE_CC_FLAGS_RELEASE "${CMAKE_CC_FLAGS} -O3 -s")


# Lib sources
set(SOURCES ${CMAKE_SOURCE_DIR}/src/arena.c)


# Executable
add_library(ImperialArena ${SOURCES})

target_include_directories(ImperialArena PRIVATE 
    ${CMAKE_SOURCE_DIR}/include/
    )
