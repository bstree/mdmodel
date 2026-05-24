cmake_minimum_required(VERSION 3.10)

project(mdmodel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CMARK REQUIRED libcmark)

add_library(mdmodel
    src/Node.cpp
    src/Document.cpp
    src/Parser.cpp
)

target_include_directories(mdmodel
    PUBLIC
        include
        ${CMARK_INCLUDE_DIRS}
)

target_link_libraries(mdmodel
    PUBLIC
        ${CMARK_LIBRARIES}
)

option(BUILD_TESTS "Build mdmodel tests" ON)
if(BUILD_TESTS)
    enable_testing()

    add_executable(mdmodel_test
        tests/Test.cpp
    )

    target_link_libraries(mdmodel_test
        PRIVATE
            mdmodel
    )

    target_include_directories(mdmodel_test
        PRIVATE 
            external/doctest
    )

    add_test(NAME mdmodel_test COMMAND mdmodel_test)
endif()

install(TARGETS mdmodel
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)
