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
  "${PROJECT_SOURCE_DIR}/source/threads/*.c"
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

# tests
file(GLOB test_SRCS
"${PROJECT_SOURCE_DIR}/include/*.h"
"${PROJECT_SOURCE_DIR}/source/*.c"
)

add_executable(reader_test ${PROJECT_SOURCE_DIR}/tests/readerTest.c ${test_SRCS})
target_link_libraries(reader_test -lpthread -lX11)

add_executable(msTimer_test ${PROJECT_SOURCE_DIR}/tests/msTimerTest.c ${test_SRCS})
target_link_libraries(msTimer_test -lpthread -lX11)

add_executable(logQueue_test ${PROJECT_SOURCE_DIR}/tests/logQueueTest.c ${test_SRCS})
target_link_libraries(logQueue_test -lpthread -lX11)

add_executable(cpuAnalyzer_test ${PROJECT_SOURCE_DIR}/tests/cpuAnalyzerTest.c ${test_SRCS})
target_link_libraries(cpuAnalyzer_test -lpthread -lX11)

# define tests
add_test(
  NAME reader_test
  COMMAND $<TARGET_FILE:reader_test>
)

add_test(
  NAME msTimer_test
  COMMAND $<TARGET_FILE:msTimer_test>
)

add_test(
  NAME logQueue_test 
  COMMAND $<TARGET_FILE:logQueue_test>
)

add_test(
  NAME cpuAnalyzer_test
  COMMAND $<TARGET_FILE:cpuAnalyzer_test>
)