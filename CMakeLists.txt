cmake_minimum_required(VERSION 3.14.2)
project(c-cut C)

include(CTest)
enable_testing()

# tests
add_executable(reader_test ${PROJECT_SOURCE_DIR}/tests/readerTest.c)
add_executable(msTimer_test ${PROJECT_SOURCE_DIR}/tests/msTimerTest.c)
target_link_libraries(reader_test -lpthread -lX11 )
target_link_libraries(msTimer_test -lpthread -lX11 ${PROJECT_SOURCE_DIR}/source/msTimer.c)

enable_testing()

# define tests
add_test(
  NAME reader_test
  COMMAND $<TARGET_FILE:reader_test>
)

add_test(
  NAME msTimer_test
  COMMAND $<TARGET_FILE:msTimer_test>
)

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
  target_compile_options(${PROJECT_NAME} PUBLIC -Wall --pedantic -Wextra -pthread -fno-stack-protector)
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "clang")
  add_compile_options(${PROJECT_NAME} PUBLIC -Weverything -pthread)
endif()