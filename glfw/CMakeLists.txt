cmake_minimum_required(VERSION 3.2)
project(OculusWithLeap)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "/usr/local/share/cmake/Modules")
message("${CMAKE_MODULE_PATH}")

include_directories(${PROJECT_SOURCE_DIR}/include)

# For Eigen
find_package(Eigen3 REQUIRED)

# For GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# For OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# For Boost
FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

add_subdirectory(src)
