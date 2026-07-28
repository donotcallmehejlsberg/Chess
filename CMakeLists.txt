cmake_minimum_required(VERSION 3.20)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE CHESS_CORE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

list(REMOVE_ITEM CHESS_CORE_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

add_library(chess_core STATIC
  ${CHESS_CORE_SOURCES}
)

target_include_directories(chess_core PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(chess
  src/main.cpp
)

target_link_libraries(chess PRIVATE
  chess_core
)

if(MSVC)
  target_compile_options(chess_core
    PRIVATE
    /W4
    /WX
    /permissive-
  )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
  target_compile_options(chess_core
    PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wformat=2
  )
else()
  message(WARNING
    "No warning flags configured for "
    "${CMAKE_CXX_COMPILER_ID}"
  )
endif()

enable_testing()

add_executable(chess_tests
  tests/MoveParserTests.cpp
  tests/MoveRecordTests.cpp
)

target_link_libraries(chess_tests PRIVATE
  chess_core
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(chess_tests)
