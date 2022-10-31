cmake_minimum_required(VERSION 3.0)
project(meta HOMEPAGE_URL "https://github.com/phisko/meta")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(cmake_helpers)
include(conan_helper)

option(PUTILS_META_TESTS "Build meta tests" OFF)
if (PUTILS_META_TESTS)
    enable_testing()

    set(test_exe_name putils_meta_tests)
    file(GLOB test_src tests/*.tests.cpp)

    add_executable(${test_exe_name} ${test_src})
    target_include_directories(${test_exe_name} PRIVATE .)

    set(customFindPackageNames gtest:GTest)
    set(customLibraryNames gtest:GTest)
    putils_conan_download_and_link_packages_with_names(
        ${test_exe_name} PRIVATE
        "${customFindPackageNames}"
        "${customLibraryNames}"
        gtest/cci.20210126
    )

    include(GoogleTest)
    gtest_discover_tests(${test_exe_name})
endif()
