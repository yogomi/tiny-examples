cmake_minimum_required(VERSION 3.2)
project(OpenCLSample)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "/usr/local/share/cmake/Modules")
message("${CMAKE_MODULE_PATH}")

include_directories(${PROJECT_SOURCE_DIR}/include)

# For Boost
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

add_subdirectory(src)
