cmake_minimum_required(VERSION 3.0.0)
project(utils VERSION 0.2.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(INTEGER_TYPES "int" "long" "long long")
set(INTEGER_TYPE "long" CACHE STRING "Integer type")
set_property(CACHE INTEGER_TYPE PROPERTY STRINGS ${INTEGER_TYPES})
list(FIND INTEGER_TYPES ${INTEGER_TYPE} INTEGER_TYPE_INDEX)
if(${INTEGER_TYPE_INDEX} EQUAL -1)
    message(FATAL_ERROR "Invalid integer type: ${INTEGER_TYPE}")
endif()

message(STATUS "Integer type: ${INTEGER_TYPE}")

add_library(utils src/rational.cpp)
target_include_directories(utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_definitions(utils PUBLIC INTEGER_TYPE=${INTEGER_TYPE})

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
