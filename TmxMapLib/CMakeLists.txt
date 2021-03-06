project(TmxMapLib)

set(TMXMAPLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TMXMAPLIB_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(TMXMAPLIB_INCLUDE
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Animation.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Exceptions.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Frame.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/GidUtil.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Image.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/ImageLayer.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/LayerBase.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Map.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Object.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/ObjectGroup.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Point.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Property.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/PropertySet.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Tile.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/TileLayer.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/Tileset.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/TilesetTile.h
    ${TMXMAPLIB_INCLUDE_DIR}/TmxMapLib/XmlUtil.h
)

set(TMXMAPLIB_SOURCE
    ${TMXMAPLIB_SOURCE_DIR}/Animation.cpp
    ${TMXMAPLIB_SOURCE_DIR}/Frame.cpp
    ${TMXMAPLIB_SOURCE_DIR}/Image.cpp
    ${TMXMAPLIB_SOURCE_DIR}/ImageLayer.cpp
    ${TMXMAPLIB_SOURCE_DIR}/LayerBase.cpp
    ${TMXMAPLIB_SOURCE_DIR}/Map.cpp
    ${TMXMAPLIB_SOURCE_DIR}/Object.cpp
    ${TMXMAPLIB_SOURCE_DIR}/ObjectGroup.cpp
    ${TMXMAPLIB_SOURCE_DIR}/Property.cpp
    ${TMXMAPLIB_SOURCE_DIR}/PropertySet.cpp
    ${TMXMAPLIB_SOURCE_DIR}/Tile.cpp
    ${TMXMAPLIB_SOURCE_DIR}/TileLayer.cpp
    ${TMXMAPLIB_SOURCE_DIR}/Tileset.cpp
    ${TMXMAPLIB_SOURCE_DIR}/TilesetTile.cpp
    ${TMXMAPLIB_SOURCE_DIR}/XmlUtil.cpp
)

include_directories(${TMXMAPLIB_INCLUDE_DIR})

add_library(TmxMapLib ${TMXMAPLIB_SOURCE} ${TMXMAPLIB_INCLUDE})

target_include_directories(TmxMapLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_link_libraries(TmxMapLib tinyxml2)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wextra")
    #target_compile_options(${PROJECT_NAME} PRIVATE "-Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE "/Wall")
endif()

install(TARGETS TmxMapLib
    EXPORT TmxMapLib-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(EXPORT TmxMapLib-targets
    FILE TmxMapLibConfig.cmake
    DESTINATION lib/cmake/TmxMapLib)

install(FILES ${TMXMAPLIB_INCLUDE} DESTINATION include/TmxMapLib)