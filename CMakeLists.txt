cmake_minimum_required(VERSION 3.20)

project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE CHESS_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(chess ${CHESS_SOURCES})

target_include_directories(chess PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MSVC)
  target_compile_options(chess
    PRIVATE
    /W4
    /WX
    /permissive-
  )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
  target_compile_options(chess
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
