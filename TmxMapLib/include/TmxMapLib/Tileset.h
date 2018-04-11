#pragma once

#include "Image.h"
#include "PropertySet.h"
#include "TilesetTile.h"
#include <unordered_map>
#include <string>

namespace tinyxml2
{
class XMLElement;
}

namespace TmxMapLib
{
class Tileset
{
private:
    int mFirstGid;
    int mTileWidth;
    int mTileHeight;
    int mTileCount;
    int mColumns;
    std::string mName;
    Image mImage;
    PropertySet mProperties;
    std::unordered_map<int, TilesetTile> mTiles;

    void loadTileset(const tinyxml2::XMLElement* tilesetElement);

public:

    /*
    *   Constructs a Tileset from the specified XML element.
    */
    Tileset(const int firstGid, const tinyxml2::XMLElement* tilesetElement);

    /*
    *   Returns the first global tile ID for this tileset.
    */
    int getFirstGid() const;

    /*
    *   Returns the image for this tileset.
    */
    const Image& getImage() const;

    /*
    *   Returns the name of this tileset.
    */
    const std::string& getName() const;

    /*
    *   Returns the set of properties for this tileset.
    */
    const PropertySet& getPropertySet() const;

    /*
    *   Returns the tileset tile with the specified tileset tile ID or
    *   null if the tile doesn't exist.
    */
    const TilesetTile* getTile(int id) const;

    /*
    *   Returns all tileset tiles in this tileset.
    */
    const std::unordered_map<int, TilesetTile>& getTiles() const;

    /*
    *   Returns the height in pixels of each tile in this tileset.
    */
    int getTileHeight() const;

    /*
    *   Returns the total number of tiles in this tileset.
    */
    int getTileCount() const;

    /*
    *   Returns the width in pixels of each tile in this tileset.
    */
    int getTileWidth() const;
};
}
