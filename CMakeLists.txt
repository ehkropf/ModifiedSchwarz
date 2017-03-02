cmake_minimum_required(VERSION 3.7)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type defaulting to '${CMAKE_BUILD_TYPE}'")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

######################################################################
set(SCHWARZ_SOURCE
    src/RealInterpolant.cpp
    src/UnitCircleDomain.cpp
    src/SpectralData.cpp
    src/SpectralMethod.cpp
    src/Solver.cpp
    src/Problem.cpp
    src/Solution.cpp
    )
add_library(schwarz SHARED ${SCHWARZ_SOURCE})
add_library(schwarz_static STATIC ${SCHWARZ_SOURCE})
set_target_properties(schwarz_static PROPERTIES OUTPUT_NAME schwarz)
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

# ######################################################################
# add_executable(tProblem test/Problem.cpp)
# target_link_libraries(tProblem schwarz)
#
# add_executable(tSpectralData test/SpectralData.cpp)
# target_link_libraries(tSpectralData schwarz)

######################################################################
set(TESTDIR "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(TESTSRC
    test/testRunner.cpp
    test/checkPolynomial.cpp
    test/checkInterpolant.cpp
    test/checkUnitDomain.cpp
    test/checkSpectralData.cpp
    test/checkSpectralMethod.cpp
    test/checkProblem.cpp
    test/checkSolution.cpp
    )

###
add_executable(testRunner EXCLUDE_FROM_ALL ${TESTSRC})
target_include_directories(testRunner
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PUBLIC ${UNITTEST_INCLUDE_DIR}
    )
target_link_libraries(testRunner schwarz ${UNITTEST_LIBRARY})

add_custom_target(check
    COMMAND ${CMAKE_BINARY_DIR}/testRunner
    DEPENDS testRunner
    )

###
add_executable(matWrite EXCLUDE_FROM_ALL test/matWrite.cpp)
target_include_directories(matWrite
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    PUBLIC ${UNITTEST_INCLUDE_DIR}
    )
target_link_libraries(matWrite schwarz)

add_custom_target(write
    COMMAND ${CMAKE_BINARY_DIR}/matWrite
    DEPENDS matWrite
    )

######################################################################
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_SOURCE_DIR}/doc/Doxyfile.in
        ${CMAKE_BINARY_DIR}/Doxyfile @ONLY
        )
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API docs with Doxygen"
        )
endif()
