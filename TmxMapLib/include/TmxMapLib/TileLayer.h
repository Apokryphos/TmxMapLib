#pragma once

#include "LayerBase.h"
#include "Tile.h"
#include <vector>

namespace tinyxml2
{
class XMLElement;
}

namespace TmxMapLib
{
class TileLayer : public LayerBase
{
private:
    int mWidth;
    int mHeight;
    std::vector<Tile> mTiles;

    void loadTileLayer(const tinyxml2::XMLElement* layerElement);
    void loadTiles(const tinyxml2::XMLElement* layerElement);

public:

    /*
    *   Constructs a TileLayer from the specified XML element.
    */
    TileLayer(
        const Map* map,
        const int tmxOrder,
        const tinyxml2::XMLElement* layerElement);

    /*
    *   Returns the height of this layer in tiles.
    */
    int getHeight() const;

    /*
    *   Returns the tile at the specified index or null
    *   if the coordinate is out of range.
    */
    const Tile* getTile(const size_t index) const;

    /*
    *   Returns the tile at the specified coordinate or null
    *   if the coordinate is out of range.
    */
    const Tile* getTile(const int x, const int y) const;

    /*
    *   Returns the tiles in this layer.
    */
    const std::vector<Tile>& getTiles() const;

    /*
    *   Returns the total number of tiles in this layer.
    */
    int getTileCount() const;

    /*
    *   Returns the width of this layer in tiles.
    */
    int getWidth() const;
};
}
