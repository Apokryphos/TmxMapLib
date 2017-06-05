cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

project("TmxMapLib")

find_package(TinyXML2 REQUIRED)

# Catch (header-only library)
set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/extlibs/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
enable_testing()

add_subdirectory(TmxMapLib/Source)
add_subdirectory(TmxMapLib_Tests/Source)