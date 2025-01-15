add_executable(utils_lib_tests test_utils.cpp)
target_link_libraries(utils_lib_tests PRIVATE utils)
setup_sanitizers(utils_lib_tests)

add_executable(crypto_tests test_crypto.cpp)
target_link_libraries(crypto_tests PRIVATE utils)
setup_sanitizers(crypto_tests)

add_test(NAME UTILS_LibTest COMMAND utils_lib_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
add_test(NAME CryptoTest COMMAND crypto_tests WORKING_DIRECTORY ${CMAKE_BINARY_DIR})