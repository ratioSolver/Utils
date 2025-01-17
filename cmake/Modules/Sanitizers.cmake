# Sanitizers.cmake
# A CMake module to simplify sanitizer setup.

function(setup_sanitizers target)
    if (MSVC AND (ENABLE_MSAN OR ENABLE_UBSAN))
        message(FATAL_ERROR "Only address sanitizer is supported on Windows")
    endif()

    if (ENABLE_ASAN AND ENABLE_MSAN)
        message(FATAL_ERROR "Address and memory sanitizers cannot be enabled at the same time")
    endif()

    set(SANITIZERS "")

    if (ENABLE_ASAN)
        list(APPEND SANITIZERS "address")
    endif()

    if (ENABLE_MSAN)
        list(APPEND SANITIZERS "memory")
    endif()

    if (ENABLE_UBSAN)
        list(APPEND SANITIZERS "undefined")
    endif()

    list(JOIN SANITIZERS "," LIST_OF_SANITIZERS)

    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
        if (ENABLE_COV)
            if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
                message(STATUS "Code coverage enabled for ${target}")
                target_compile_options(${target} INTERFACE --coverage)
                target_link_libraries(${target} INTERFACE --coverage)
            endif()
        endif()
    endif()

    if (NOT "${LIST_OF_SANITIZERS}" STREQUAL "")
        message(STATUS "Sanitizers enabled for ${target}: ${LIST_OF_SANITIZERS}")
        target_compile_options(${target} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
        target_link_options(${target} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
    endif()
endfunction()