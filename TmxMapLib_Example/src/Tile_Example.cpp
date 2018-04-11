#include <TmxMapLib/Map.h>
#include <iostream>

using namespace TmxMapLib;

//  ===============================================================================
int main()
{
    Map map("map01.tmx");

    std::cout << "Map Width: "     << map.getWidth()            << std::endl;
    std::cout << "Map Height: "    << map.getHeight()           << std::endl;
    std::cout << "Tile Layers: "   << map.getTileLayerCount()   << std::endl;
    std::cout << "Object Groups: " << map.getObjectGroupCount() << std::endl;

    //  Iterate over tilesets.
    const auto& tilesets = map.getTilesets();
    for (const Tileset& tileset : tilesets) {
        std::cout << "Tileset: " << tileset.getName() << std::endl;
    }

    //  Iterate over tile layers.
    const auto& tileLayers = map.getTileLayers();
    for (const TileLayer& tileLayer : tileLayers) {
        //  Iterate over tiles.
        //  You could also use for loops along with the GetTile() method.
        const auto& tiles = tileLayer.getTiles();
        for (const Tile& tile : tiles) {
            //  Get the tileset this tile belongs to
            const Tileset* tileset = map.getTilesetByGid(tile.getGid());

            if (tileset != nullptr) {
                //  Get the tileset tile for this tile.
                //  This could be null if Tiled didn't export an entry for
                //  that tile (e.g. if you didn't add any properties)
                const TilesetTile* tilesetTile =
                    tileset->getTile(tile.getGid() - tileset->getFirstGid());

                if (tilesetTile != nullptr) {
                    std::cout << "Tileset Tile ID: "
                              << tilesetTile->getId() << std::endl;

                    const PropertySet& propertySet = tilesetTile->getPropertySet();

                    for (const Property* property : propertySet.getProperties()) {
                        std::cout << property->getName() << ":"
                                  << property->getValue() << std::endl;
                    }
                }
            }
        }
    }

    return 0;
}