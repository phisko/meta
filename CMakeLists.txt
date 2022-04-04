set(CMAKE_CXX_STANDARD 20)

if (PUTILS_TESTS)
    set(test_exe_name putils_meta_tests)
    file(GLOB test_src tests/*.tests.cpp)

    add_executable(${test_exe_name} ${test_src})
    target_include_directories(${test_exe_name} PRIVATE .)

    putils_conan(gtest/cci.20210126)
    target_link_libraries(${test_exe_name} CONAN_PKG::gtest)

    include(GoogleTest)
    gtest_discover_tests(${test_exe_name})
endif()