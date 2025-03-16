cmake_minimum_required(VERSION 3.15...3.31)
project(lcpp VERSION 0.1
  DESCRIPTION "Leetcode solutions"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.16.0
)
FetchContent_Declare(
  icecream-cpp
  GIT_REPOSITORY https://github.com/renatoGarcia/icecream-cpp
  GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(googletest icecream-cpp)
include(GoogleTest)

function(add_leetcode_problem P_ID)
  # add src target as library
  set(P_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/${P_ID}")
  set(P_LIB "${P_ID}_lib")

  add_library(${P_LIB} STATIC
    ${P_SRC_DIR}/solution.cpp
  )
  target_include_directories(${P_LIB} PUBLIC
    ${P_SRC_DIR}
  )

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
      GTest::gtest GTest::gtest_main
    )

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
