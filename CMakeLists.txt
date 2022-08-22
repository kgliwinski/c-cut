cmake_minimum_required(VERSION 3.14.2)
project(c-cut C)

include(CTest)
enable_testing()

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source
)

link_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source)


file(GLOB all_SRCS
  "${PROJECT_SOURCE_DIR}/include/*.h"
  "${PROJECT_SOURCE_DIR}/source/*.c"
  "${PROJECT_SOURCE_DIR}/main.c"
)

add_executable(${PROJECT_NAME} ${all_SRCS})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(${PROJECT_NAME} -lpthread -lX11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Add warning flags
if(CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(${PROJECT_NAME} PUBLIC -pthread -Wall -pedantic -Wextra )
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  add_compile_options(${PROJECT_NAME} PUBLIC -pthread -Weverything -pthread)
endif()


