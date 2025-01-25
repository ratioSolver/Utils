add_executable(utils_lib_tests test_utils.cpp)
add_dependencies(utils_lib_tests utils)
target_link_libraries(utils_lib_tests PRIVATE utils)
setup_sanitizers(utils_lib_tests)

add_executable(crypto_tests test_crypto.cpp)
add_dependencies(crypto_tests utils)
target_link_libraries(crypto_tests PRIVATE utils)
setup_sanitizers(crypto_tests)

add_executable(pointers_tests test_pointers.cpp)
add_dependencies(pointers_tests utils)
target_link_libraries(pointers_tests PRIVATE utils)
setup_sanitizers(pointers_tests)

add_test(NAME UTILS_LibTest COMMAND utils_lib_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME CryptoTest COMMAND crypto_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME PointersTest COMMAND pointers_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})