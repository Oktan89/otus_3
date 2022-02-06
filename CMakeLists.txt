cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(alocator VERSION ${PROJECT_VESRION})

option(WITH_GOOGLE_TEST "Whether to build Google tets" ON)

configure_file(version.h.in version.h)

add_executable(aloc main.cpp)
add_library(aloc_ver lib.cpp)

set_target_properties(aloc PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(aloc_ver
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(aloc PRIVATE
    aloc_ver
)

if(WITH_GOOGLE_TEST)
    add_subdirectory(./googletest EXCLUDE_FROM_ALL)
    add_executable(google_test_version test_version_g.cpp)

    set_target_properties(google_test_version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(google_test_version 
        gtest_main 
        gmock
        aloc_ver
    )
endif()

if (MSVC)
    target_compile_options(alocator PRIVATE
        /W4
    )
    target_compile_options(aloc_ver PRIVATE
        /W4
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(google_test_version PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(aloc PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(aloc_ver PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(google_test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS aloc RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT r.zhigalenko@mail.ru)
include(CPack)

if(WITH_GOOGLE_TEST)
    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(google_test_version)
endif()