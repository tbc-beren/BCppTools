#
# === Coverage ===============================================================
# cmake .. -DBCPPTOOLS_TESTCOVERAGE=1
# rm *.info
# rm -rf cov-results
# lcov -t "result" -o coverage_01.info -c -d .
# lcov --remove coverage_01.info -o coverage.info \
#     '/usr/include/*' \
#     '*/googletest-src/*'
# genhtml -o cov-results coverage.info
#
#
# === Build Debug ============================================================
# cmake .. -DCMAKE_BUILD_TYPE=Debug
#
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 11)

project (BCppTools CXX)
add_library(BCppTools INTERFACE)
target_include_directories(BCppTools INTERFACE include/)





# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.gtest googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()





# Set coverage options when needed
if (DEFINED BCPPTOOLS_TESTCOVERAGE)
set(COVERAGE_OPTIONS "--coverage")
endif (DEFINED BCPPTOOLS_TESTCOVERAGE)

enable_testing()
add_executable(
    BCppToolsTest

    # The tests
    test/testHashBase64.cpp
    test/testTimeClock.cpp
    )
target_link_libraries(BCppToolsTest gtest_main)
target_link_libraries(BCppToolsTest BCppTools ${COVERAGE_OPTIONS})
if(MSVC)
  target_compile_options(BCppToolsTest PRIVATE /W4 /WX)
else()
  target_compile_options(BCppToolsTest PRIVATE -Wall -Wextra -pedantic -Werror ${COVERAGE_OPTIONS})
endif()
add_test(NAME BCppToolsTestName COMMAND BCppToolsTest)

# Coverage Update target
if (DEFINED BCPPTOOLS_TESTCOVERAGE)
add_custom_command(
  OUTPUT BCCoverage
  COMMENT "BCCoverage Command"
  COMMAND rm -f *.info
  COMMAND rm -rf cov-results
  COMMAND ./BCppToolsTest
  COMMAND lcov -t "result" -o coverage_01.info -c -d .
  COMMAND lcov --remove coverage_01.info -o coverage.info '/usr/include/*' '*/googletest-src/*'
  COMMAND genhtml -o cov-results coverage.info
)

else ()

add_custom_command(
  OUTPUT BCCoverage
  COMMENT "BCCoverage Command"
  COMMAND echo "Coverage not set. Please rebuild with:"
  COMMAND echo "     cmake ${CMAKE_SOURCE_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DBCPPTOOLS_TESTCOVERAGE=1"
)

endif (DEFINED BCPPTOOLS_TESTCOVERAGE)

add_custom_target(coverage
  DEPENDS
    BCCoverage
    BCppToolsTest
    )