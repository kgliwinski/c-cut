cmake_minimum_required(VERSION 3.0.0)
project(c-cut C)

include(CTest)
enable_testing()

add_executable(c-cut main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Include cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(Warnings)

