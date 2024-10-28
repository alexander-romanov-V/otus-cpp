cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ipfilter VERSION ${PROJECT_VESRION})

add_executable(ipfilter_cli main.cpp)
add_executable(ipfilter_gtest ipfilter_gtest.cpp)

set_target_properties(ipfilter_cli ipfilter_gtest PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ipfilter_cli
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ipfilter_gtest
    gtest
    # gmock
    pthread
)

if (MSVC)
    target_compile_options(ipfilter_cli PRIVATE
        /W4
    )
    # target_compile_options(ipfilter_gtest PRIVATE
    #     /W4
    # )
else ()
    target_compile_options(ipfilter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(ipfilter_gtest PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
endif()

install(TARGETS ipfilter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
enable_testing()

# add_test(ipfilter_gtest ipfilter_gtest)
add_test(
    NAME ipfilter_cli
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND sh -c "cat ${CMAKE_SOURCE_DIR}/ip_filter.tsv | ${CMAKE_BINARY_DIR}/ipfilter_cli | md5sum | grep -q '24e7a7b2270daee89c64d3ca5fb3da1a'"
    )
