cmake_minimum_required(VERSION 3.7)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
    message(STATUS "Build type defaulting to '${CMAKE_BUILD_TYPE}'")
endif()

# enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

######################################################################
set(SCHWARZ_SOURCE src/ModifiedSchwarz.cpp)
add_library(schwarz SHARED ${SCHWARZ_SOURCE})
target_link_libraries(schwarz ${ARMADILLO_LIBRARIES})

######################################################################
# Testing.

# Because MacPorts does not install the cmake file needed to use find_package().
if(NOT UNITTEST_LIBRARY)
    find_library(UNITTEST_LIBRARY UnitTest++)
    if(NOT UNITTEST_LIBRARY)
        message(FATAL_ERROR "UnitTest++ library not found.")
    else()
        message(STATUS "Found UnitTest++: " ${UNITTEST_LIBRARY})
    endif()

    get_filename_component(UNITTEST_LIBRARY_DIR ${UNITTEST_LIBRARY} DIRECTORY)
    get_filename_component(UNITTEST_INCLUDE_DIR ${UNITTEST_LIBRARY_DIR} DIRECTORY)
    set(UNITTEST_INCLUDE_DIR "${UNITTEST_INCLUDE_DIR}/include")
endif()

include_directories(${UNITTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)
link_directories(${UNITTEST_LIBRARY_DIR})

# ######################################################################
# add_executable(tProblem test/Problem.cpp)
# target_link_libraries(tProblem schwarz)
#
# add_executable(tSpectralData test/SpectralData.cpp)
# target_link_libraries(tSpectralData schwarz)

######################################################################
set(TESTDIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(TESTSRC test/testRunner.cpp
    test/Problem.cpp
    test/Polynomial.cpp
    test/SpectralData.cpp test/SpectralSolution.cpp)

add_executable(testRunner EXCLUDE_FROM_ALL ${TESTSRC})
target_link_libraries(testRunner schwarz ${UNITTEST_LIBRARY})

add_custom_target(check
    COMMAND ${CMAKE_BINARY_DIR}/testRunner
    DEPENDS testRunner)

# add_test(NAME matrix COMMAND first)
# add_test(matrixView COMMAND ${TESTDIR}/matplot.py Lmatrix.dat)
# add_test(NAME shared COMMAND shared)

# add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
#                   DEPENDS first shared)
