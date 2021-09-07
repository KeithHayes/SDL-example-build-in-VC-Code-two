cmake_minimum_required(VERSION 3.7)
project(showpic VERSION 1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(inc)
file(GLOB SOURCES "src/*.cpp")

find_package(SDL2 REQUIRED)
include(FindPkgConfig)
pkg_check_modules(SDL2_Image REQUIRED IMPORTED_TARGET SDL2_image)

add_executable(${PROJECT_NAME}.out ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}.out PkgConfig::SDL2_Image)
