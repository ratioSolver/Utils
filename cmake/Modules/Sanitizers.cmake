# Sanitizers.cmake
# A CMake module to simplify sanitizer setup.

function(setup_sanitizers target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -fsanitize=undefined,address)
        target_link_options(${target} PRIVATE -fsanitize=undefined,address)
        if (ENABLE_COVERAGE)
            if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                target_compile_options(${target} PRIVATE --coverage)
                target_link_libraries(${target} PUBLIC gcov)
            endif()
        endif()
    endif()
endfunction()