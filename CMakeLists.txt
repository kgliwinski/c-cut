cmake_minimum_required(VERSION 3.14.2)
project(c-cut C)

include(CTest)
enable_testing()

include_directories(include)

add_executable(c-cut main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#Add warning flags

if(CMAKE_COMPILER_IS_GNUCC)
  target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic -Wextra)
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  add_compile_options(${PROJECT_NAME} PUBLIC -Wall)
endif()

