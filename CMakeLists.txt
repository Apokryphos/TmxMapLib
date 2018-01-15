cmake_minimum_required(VERSION 3.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

project(TmxMapLib)

find_package(TinyXML2 REQUIRED)

# Catch (header-only library)
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
enable_testing()

add_subdirectory(TmxMapLib)
add_subdirectory(TmxMapLib_Tests)