cmake_minimum_required(VERSION 3.0.0)
project(utils VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GenerateExportHeader)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include(CTest)
enable_testing()

set(INTEGER_TYPES "int" "long" "long long")
set(INTEGER_TYPE "long" CACHE STRING "Integer type")
set_property(CACHE INTEGER_TYPE PROPERTY STRINGS ${INTEGER_TYPES})

option(VERBOSE_LOG "Makes log more verbose" OFF)
option(ADD_COVERAGE "Add coverage" OFF)

file(GLOB UTILS_SOURCES src/*.cpp)
file(GLOB UTILS_HEADERS include/*.h)

add_library(${PROJECT_NAME} SHARED ${UTILS_SOURCES})
GENERATE_EXPORT_HEADER(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

message(STATUS "Integer type:           ${INTEGER_TYPE}")
if(INTEGER_TYPE STREQUAL "int")
    target_compile_definitions(${PROJECT_NAME} PUBLIC INTEGER_TYPE_INT)
elseif(INTEGER_TYPE STREQUAL "long")
    target_compile_definitions(${PROJECT_NAME} PUBLIC INTEGER_TYPE_LONG)
elseif(INTEGER_TYPE STREQUAL "long long")
    target_compile_definitions(${PROJECT_NAME} PUBLIC INTEGER_TYPE_LONG_LONG)
else()
    message(FATAL_ERROR "INTEGER_TYPE must be one of ${INTEGER_TYPES}")
endif()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

message(STATUS "Verbose log:            ${VERBOSE_LOG}")
if(VERBOSE_LOG)
    target_compile_definitions(${PROJECT_NAME} PUBLIC VERBOSE_LOG)
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
    if (ADD_COVERAGE)
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${PROJECT_NAME} PRIVATE --coverage)
            target_link_libraries(${PROJECT_NAME} PUBLIC gcov)
        endif()
    endif()
endif()

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(
    FILES ${UTILS_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/utils_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
configure_package_config_file(src/${PROJECT_NAME}Config.cmake.in ${PROJECT_NAME}Config.cmake INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} PATH_VARS CMAKE_INSTALL_INCLUDEDIR)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake VERSION 1.0.0 COMPATIBILITY SameMajorVersion)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
