# determining compiler

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(WGCC TRUE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(WCLANG TRUE)
endif()

# set warning flags
