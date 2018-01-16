#ifndef TMXMAPLIB_MAP_HEADER_INCLUDED
#define TMXMAPLIB_MAP_HEADER_INCLUDED

#include "ImageLayer.h"
#include "ObjectGroup.h"
#include "PropertySet.h"
#include "TileLayer.h"
#include "Tileset.h"
#include <string>
#include <vector>

namespace tinyxml2
{
    class XMLElement;
}

namespace TmxMapLib
{
    enum class RenderOrder
    {
        RightDown,
        RightUp,
        LeftDown,
        LeftUp,
    };

    class Map
    {
    private:
        int mWidth;
        int mHeight;
        int mTileWidth;
        int mTileHeight;
        RenderOrder mRenderOrder;
        PropertySet mProperties;

        std::vector<ImageLayer> mImageLayers;
        std::vector<TileLayer> mTileLayers;
        std::vector<Tileset> mTilesets;
        std::vector<ObjectGroup> mObjectGroups;

        std::vector<LayerBase*> mTmxOrder;

        void LoadMap(const tinyxml2::XMLElement* mapElement);
        void LoadLayers(const tinyxml2::XMLElement* mapElement);
        void LoadTilesets(const tinyxml2::XMLElement* mapElement);

    public:

        /*
        *   Constructs a TmxMap from the specified TMX file.
        */
        Map(const std::string& filename);

        /*
        *   Returns the height of this map in tiles.
        */
        int GetHeight() const;

        /*
        *   Returns the image layer at the specified index.
        *   Throws an out_of_range exception if the index is out of range.
        */
        const ImageLayer& GetImageLayer(const int index) const;

        /*
        *   Returns the image layers in this map.
        */
        const std::vector<ImageLayer>& GetImageLayers() const;

        /*
        *   Returns the number of image layers in this map.
        */
        int GetImageLayerCount() const;

        /*
        *   Returns the number of layers in this map.
        */
        int GetLayerCount() const;

        /*
        *   Returns all layers in the map in the same order as the TMX file
        *   (i.e. the same order they are rendered in Tiled).
        */
        const std::vector<LayerBase*>& GetLayersInTmxOrder() const;

        /*
        *   Returns the object at the specified index.
        *   Throws an out_of_range exception if the index is out of range.
        */
        const ObjectGroup& GetObjectGroup(const int index) const;

        /*
        *   Returns the number of object groups in this map.
        */
        int GetObjectGroupCount() const;

        /*
        *   Returns all objects in this map.
        */
        const std::vector<ObjectGroup>& GetObjectGroups() const;

        /*
        *   Returns the set of properties for this map.
        */
        const PropertySet& GetPropertySet() const;

        /*
        *   Returns the order in which the tiles on tile layers are renderered.
        */
        RenderOrder GetRenderOrder() const;

        /*
        *   Returns the height of the tiles in this map in pixels.
        */
        int GetTileHeight() const;

        /*
        *   Returns the tile layer at the specified index.
        *   Throws an out_of_range exception if the index is out of range.
        */
        const TileLayer& GetTileLayer(const int index) const;

        /*
        *   Returns all of the tile layers in this map.
        */
        const std::vector<TileLayer>& GetTileLayers() const;

        /*
        *   Returns the number of tile layers in this map.
        */
        int GetTileLayerCount() const;

        /*
        *   Returns the width of the tiles in this map in pixels.
        */
        int GetTileWidth() const;

        /*
        *   Returns the tileset at the specified index.
        *   Throws std::out_of_range if the index is out of bounds.
        */
        const Tileset& GetTileset(const size_t index) const;

        /*
        *   Returns all tilesets in this map.
        */
        const std::vector<Tileset>& GetTilesets() const;

        /*
        *   Returns the tileset containing the specified tile GID or null
        *   if no tileset exists for the GID. This only checks ID ranges
        *   and a returned tileset may not have a TilesetTile for the GID,
        *   as only tileset tiles explicity specified in the TMX map data
        *   (i.e. tiles with properties or additional data) are loaded.
        */
        const Tileset* GetTilesetByGid(const int gid) const;

        /*
        *   Returns the number of tilesets in this map.
        */
        int GetTilesetCount() const;

        /*
        *   Returns the width of this map in tiles.
        */
        int GetWidth() const;
    };
}

#endif