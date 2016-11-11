cmake_minimum_required(VERSION 3.6)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type defaulting to '${CMAKE_BUILD_TYPE}'")
endif()

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

######################################################################
add_executable(first firstMatrix.cpp ModifiedSchwarz.cpp)
target_link_libraries(first ${ARMADILLO_LIBRARIES})

######################################################################
set(TESTDIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

add_test(NAME run COMMAND first)
add_test(matrixView COMMAND ${TESTDIR}/matplot.py Lmatrix.dat)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS first)
