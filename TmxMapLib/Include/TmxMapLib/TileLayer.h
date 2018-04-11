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

        void LoadTileLayer(const tinyxml2::XMLElement* layerElement);
        void LoadTiles(const tinyxml2::XMLElement* layerElement);

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
        int GetHeight() const;

        /*
        *   Returns the tile at the specified index or null
        *   if the coordinate is out of range.
        */
        const Tile* GetTile(const size_t index) const;

        /*
        *   Returns the tile at the specified coordinate or null
        *   if the coordinate is out of range.
        */
        const Tile* GetTile(const int x, const int y) const;

        /*
        *   Returns the tiles in this layer.
        */
        const std::vector<Tile>& GetTiles() const;

        /*
        *   Returns the total number of tiles in this layer.
        */
        int GetTileCount() const;

        /*
        *   Returns the width of this layer in tiles.
        */
        int GetWidth() const;
    };
}
