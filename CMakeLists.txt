cmake_minimum_required(VERSION 3.0)
project(putils_meta HOMEPAGE_URL "https://github.com/phisko/meta")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(cmake_helpers)

add_library(putils_meta INTERFACE)
target_include_directories(putils_meta INTERFACE .)

option(PUTILS_META_TESTS "Build meta tests")
if (PUTILS_META_TESTS)
    enable_testing()

    set(test_exe_name putils_meta_tests)
    file(GLOB test_src
        putils/meta/tests/*.tests.cpp
        putils/meta/traits/tests/*.tests.cpp
        putils/meta/concepts/tests/*.tests.cpp
        )

    putils_add_test_executable(${test_exe_name} ${test_src})
    target_link_libraries(${test_exe_name} PRIVATE putils_meta)
endif()
