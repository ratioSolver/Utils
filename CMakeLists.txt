cmake_minimum_required(VERSION 3.0.0)
project(utils VERSION 0.2.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_library(utils src/rational.cpp)
target_include_directories(utils PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
