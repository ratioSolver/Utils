add_executable(utils_lib_tests test_utils.cpp)
target_link_libraries(utils_lib_tests PRIVATE utils)

add_test(NAME UTILS_LibTest COMMAND utils_lib_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})