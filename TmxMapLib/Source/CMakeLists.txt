set(TMXMAPLIB_SOURCE
    Animation.cpp
    Frame.cpp
    Image.cpp
    ImageLayer.cpp
    LayerBase.cpp
    Object.cpp
    ObjectGroup.cpp
    Property.cpp
    PropertySet.cpp
    Tile.cpp
    TileLayer.cpp
    Tileset.cpp
    TilesetTile.cpp
    TmxMap.cpp
    XmlUtil.cpp
)

include_directories(${TmxMapLib_SOURCE_DIR}/TmxMapLib/Include)

add_library(TmxMapLib ${TMXMAPLIB_SOURCE})