cmake_minimum_required(VERSION 3.12)

project(SippetScript VERSION 1.0.0)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/source/*.c")
add_executable(SippetScript ${SOURCES})

target_include_directories(SippetScript PUBLIC "${CMAKE_SOURCE_DIR}/source")