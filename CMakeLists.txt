cmake_minimum_required(VERSION 3.10)

project(mdmodel VERSION 1.0.0)

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${CMARK_INCLUDE_DIRS}
)

target_link_libraries(mdmodel
    PUBLIC
        ${CMARK_LIBRARIES}
)

set_target_properties(mdmodel PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
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
    EXPORT mdmodelTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/
    DESTINATION include
)

install(EXPORT mdmodelTargets
    FILE mdmodelTargets.cmake
    NAMESPACE mdmodel::
    DESTINATION lib/cmake/mdmodel
)