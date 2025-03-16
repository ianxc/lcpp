cmake_minimum_required(VERSION 3.15...3.31)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(lcpp VERSION 0.1
  DESCRIPTION "Leetcode solutions"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include(CTest)

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
find_path(ICECREAM_CPP_INCLUDE_DIRS "icecream.hpp")

function(set_warnings TARGET)
  if(MSVC)
    target_compile_options(${TARGET} PRIVATE /W4 /WX)
  else()
    target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
  endif()
endfunction()

function(add_leetcode_problem P_ID)
  # add src target as library
  set(P_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/${P_ID}")
  set(P_LIB "${P_ID}_lib")

  if(EXISTS "${P_SRC_DIR}/solution.cpp")
    add_library(${P_LIB} STATIC
      ${P_SRC_DIR}/solution.cpp
      ${P_SRC_DIR}/solution.h
    )
    target_include_directories(${P_LIB} PUBLIC
      ${P_SRC_DIR}
    )
    target_include_directories(${P_LIB} PRIVATE
      ${ICECREAM_CPP_INCLUDE_DIRS}
    )
    set_warnings(${P_LIB})
  else()
    # header-only library
    add_library(${P_LIB} INTERFACE)
    target_include_directories(${P_LIB} INTERFACE
      ${P_SRC_DIR}
    )
    # exposes transitive dependencies. not ideal, but allows for icecream-cpp usage
    # within a header file for ease of solution submission.
    target_include_directories(${P_LIB} SYSTEM INTERFACE
      ${ICECREAM_CPP_INCLUDE_DIRS}
    )
  endif()

  set_target_properties(${P_LIB} PROPERTIES LINKER_LANGUAGE CXX)

  # add test target
  set(P_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test/${P_ID}")
  set(P_TEST_FILE "${P_TEST_DIR}/solution.test.cpp")
  set(P_TEST_NAME "${P_ID}_test")
  if(EXISTS "${P_TEST_FILE}")
    add_executable(${P_TEST_NAME}
      ${P_TEST_FILE}
    )
    target_link_libraries(${P_TEST_NAME} PRIVATE
      ${P_LIB}
      GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
    )
    target_include_directories(${P_TEST_NAME} PRIVATE
      ${ICECREAM_CPP_INCLUDE_DIRS}
    )
    set_warnings(${P_TEST_NAME})

    gtest_discover_tests(${P_TEST_NAME}
      PROPERTIES LABELS "${P_ID}"
      TEST_PREFIX "${P_ID}."
      DISCOVERY_TIMEOUT 10
    )
  endif()

  # add main executable
  if(EXISTS "${P_SRC_DIR}/main.cpp")
    add_executable(${P_ID}_run
      ${P_SRC_DIR}/main.cpp
    )
    target_link_libraries(${P_ID}_run PRIVATE
      ${P_LIB}
    )
    target_include_directories(${P_ID}_run PRIVATE
      ${ICECREAM_CPP_INCLUDE_DIRS}
    )
  endif()
endfunction()

# auto-discover and add all problems
file(GLOB P_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
foreach(P_DIR ${P_DIRS})
  if(IS_DIRECTORY ${P_DIR})
    get_filename_component(P_ID ${P_DIR} NAME)
    if(P_ID MATCHES "([0-9]+)-(.*)")
      add_leetcode_problem(${P_ID})
    endif()
  endif()
endforeach()
