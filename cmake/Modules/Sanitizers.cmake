# Sanitizers.cmake
# A CMake module to simplify sanitizer setup.

function(setup_sanitizers target)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)

        if (ENABLE_MSAN)
            message(FATAL_ERROR "Memory sanitizer is not supported with GCC")
        endif()

        set(SANITIZERS "")

        if (ENABLE_ASAN)
            list(APPEND SANITIZERS "address")
        endif()

        if (ENABLE_UBSAN)
            list(APPEND SANITIZERS "undefined")
        endif()

        list(JOIN SANITIZERS "," LIST_OF_SANITIZERS)

        if (NOT "${LIST_OF_SANITIZERS}" STREQUAL "")
            message(STATUS "Sanitizers enabled for ${target}: ${LIST_OF_SANITIZERS}")
            target_compile_options(${target} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
            target_link_options(${target} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
        endif()

        if (ENABLE_COV)
            message(STATUS "Code coverage enabled for ${target}")
            target_compile_options(${target} INTERFACE --coverage)
            target_link_libraries(${target} INTERFACE --coverage)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)

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

        if(NOT "${LIST_OF_SANITIZERS}" STREQUAL "")
            message(STATUS "Sanitizers enabled for ${target}: ${LIST_OF_SANITIZERS}")
            target_compile_options(${target} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
            target_link_options(${target} INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
        endif()
    elseif(MSVC)
        target_compile_options(${target} PRIVATE /W4)

        if (ENABLE_MSAN)
            message(FATAL_ERROR "Memory sanitizer is not supported with MSVC")
        endif()

        if (ENABLE_UBSAN)
            message(FATAL_ERROR "Undefined behavior sanitizer is not supported with MSVC")
        endif()

        if (ENABLE_ASAN)
            message(STATUS "Address sanitizer enabled for ${target}")
            string(FIND "$ENV{PATH}" "$ENV{VSINSTALLDIR}" index_of_vs_install_dir)
            if("${index_of_vs_install_dir}" STREQUAL "-1")
                message(SEND_ERROR "Using MSVC sanitizers requires setting the MSVC environment before building the project. Please manually open the MSVC command prompt and rebuild the project.")
            endif()
            target_compile_options(${target} INTERFACE /fsanitize=address)
            target_compile_definitions(${target} INTERFACE _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION)
            target_link_options(${target} INTERFACE /fsanitize=address)
        endif()
    else()
        message(FATAL_ERROR "Unsupported compiler")
    endif()
endfunction()