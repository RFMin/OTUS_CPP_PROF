cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_sort VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(ip_sort_cli ip_srt_c.cpp)
add_library(ip_sort lib.cpp ip_srt_lib.c)
add_executable(test_version test_version.cpp)

set_target_properties(ip_sort_cli ip_sort test_version PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)
target_include_directories(ip_sort
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(ip_sort_cli PRIVATE
    ip_sort
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    ip_sort
)

if (MSVC)
    target_compile_options(ip_sort_cli PRIVATE
        /W4
    )
    target_compile_options(ip_sort PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_sort_cli PRIVATE
        -Wall -Wextra -pedantic -Werror -static
    )
    target_compile_options(ip_sort PRIVATE
        -Wall -Wextra -pedantic -Werror -static
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_sort_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
