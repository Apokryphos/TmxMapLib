set(TMXMAPLIB_SOURCE
    Animation.cpp
    Frame.cpp
    Image.cpp
    ImageLayer.cpp
    LayerBase.cpp
    Map.cpp
    Object.cpp
    ObjectGroup.cpp
    Property.cpp
    PropertySet.cpp
    Tile.cpp
    TileLayer.cpp
    Tileset.cpp
    TilesetTile.cpp
    XmlUtil.cpp
)

set(TMXMAPLIB_INCLUDE
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Animation.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Exceptions.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Frame.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/GidUtil.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Image.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/ImageLayer.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/LayerBase.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Map.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Object.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/ObjectGroup.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Point.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Property.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/PropertySet.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Tile.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/TileLayer.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/Tileset.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/TilesetTile.h
    ${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include/TmxMapLib/XmlUtil.h
)

include_directories(${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include)

add_library(TmxMapLib ${TMXMAPLIB_SOURCE} ${TMXMAPLIB_INCLUDE})

target_include_directories(TmxMapLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(TARGETS TmxMapLib
    EXPORT TmxMapLib-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(EXPORT TmxMapLib-targets
    FILE TmxMapLibConfig.cmake
    DESTINATION lib/cmake/TmxMapLib)

install(FILES ${TMXMAPLIB_INCLUDE} DESTINATION include/TmxMapLib)