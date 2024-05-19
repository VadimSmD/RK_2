cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(template_usage_testing)

option(BUILD_MAIN "Build main.cpp" OFF)
option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/third-party/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/templates)

add_library(abstract STATIC ${CMAKE_CURRENT_SOURCE_DIR}/templates/AbstractClass.cpp)
add_library(concreteX STATIC ${CMAKE_CURRENT_SOURCE_DIR}/templates/ConcreteClassX.cpp)
target_link_libraries(concreteX abstract)
add_library(concreteY STATIC ${CMAKE_CURRENT_SOURCE_DIR}/templates/ConcreteClassY.cpp)
target_link_libraries(concreteY abstract)

if (BUILD_MAIN)
    add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/templates/main.cpp)
    target_link_libraries(main concreteX concreteY)
    install(TARGETS main RUNTIME DESTINATION bin)
endif()

if (BUILD_TESTS)
    add_subdirectory(third-party/gtest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
    file(GLOB ACCOUNT_TEST_SOURCES tests/*.cpp)
    add_executable(check ${ACCOUNT_TEST_SOURCES})
    target_link_libraries(check gtest_main gtest gmock abstract)
    add_test(NAME check COMMAND check)
endif()

