#include <TmxMapLib/Map.h>
#include <iostream>

using namespace TmxMapLib;

//  ===========================================================================
int main()
{
    Map map("map01.tmx");

    std::cout << "Map Width: "     << map.GetWidth()            << std::endl;
    std::cout << "Map Height: "    << map.GetHeight()           << std::endl;
    std::cout << "Tile Layers: "   << map.GetTileLayerCount()   << std::endl;
    std::cout << "Object Groups: " << map.GetObjectGroupCount() << std::endl;

    //  Iterate over tilesets.
    for (const Tileset& tileset : map.GetTilesets())
    {
        std::cout << "Tileset: " << tileset.GetName() << std::endl;
    }

    //  Iterate over tile layers.
    for (const TileLayer& tileLayer : map.GetTileLayers())
    {
    //  Iterate over tiles.
        //  You could also use for loops along with the GetTile() method.
        for (const Tile& tile : tileLayer.GetTiles())
        {
            //  Get the tileset this tile belongs to
            const Tileset* tileset = map.GetTilesetByGid(tile.GetGid());

            if (tileset != nullptr)
            {
                //  Get the tileset tile for this tile.
                //  This could be null if Tiled didn't export an entry for
                //  that tile (e.g. if you didn't add any properties)
                const TilesetTile* tilesetTile =
                    tileset->GetTile(tile.GetGid() - tileset->GetFirstGid());

                if (tilesetTile != nullptr)
                {
                    std::cout << "Tileset Tile ID: "
                              << tilesetTile->GetId() << std::endl;

                    const PropertySet& propertySet = tilesetTile->GetPropertySet();

                    for (const Property* property : propertySet.GetProperties())
                    {
                        std::cout << property->GetName() << ":"
                                  << property->GetValue() << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}