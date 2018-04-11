#include "TmxMapLib/Map.h"
#include "catch.hpp"

using namespace TmxMapLib;

//  ===============================================================================
TEST_CASE("TmxMap TMX filename constructor", "[map]")
{
    Map map("map01.tmx");

    REQUIRE(map.getWidth() == 20);
    REQUIRE(map.getHeight() == 16);
    REQUIRE(map.getTileWidth() == 16);
    REQUIRE(map.getTileHeight() == 16);

    //  Map properties
    REQUIRE(map.getPropertySet().getProperty("AllowSave")->getName() == "AllowSave");
    REQUIRE(map.getPropertySet().getProperty("AllowSave")->getType() == PropertyType::Bool);
    REQUIRE(map.getPropertySet().getProperty("AllowSave")->getValue() == "true");
    REQUIRE(map.getPropertySet().getProperty("AllowSave")->getBoolValue() == true);
    REQUIRE(map.getPropertySet().getBoolValue("AllowSave", false) == true);

    REQUIRE(map.getPropertySet().getProperty("Difficulty")->getName() == "Difficulty");
    REQUIRE(map.getPropertySet().getProperty("Difficulty")->getType() == PropertyType::Int);
    REQUIRE(map.getPropertySet().getProperty("Difficulty")->getValue() == "2");
    REQUIRE(map.getPropertySet().getProperty("Difficulty")->getIntValue() == 2);
    REQUIRE(map.getPropertySet().getProperty("Difficulty")->getDoubleValue() == 2);
    REQUIRE(map.getPropertySet().getProperty("Difficulty")->getFloatValue() == 2.0f);
    REQUIRE(map.getPropertySet().getIntValue("Difficulty", 0) == 2);
    REQUIRE(map.getPropertySet().getDoubleValue("Difficulty", 0) == 2.0);
    REQUIRE(map.getPropertySet().getFloatValue("Difficulty", 0.0f) == 2.0f);

    REQUIRE(map.getPropertySet().getProperty("LootChance")->getName() == "LootChance");
    REQUIRE(map.getPropertySet().getProperty("LootChance")->getType() == PropertyType::Float);
    REQUIRE(map.getPropertySet().getProperty("LootChance")->getValue() == "0.5");
    REQUIRE(map.getPropertySet().getProperty("LootChance")->getDoubleValue() == 0.5);
    REQUIRE(map.getPropertySet().getProperty("LootChance")->getFloatValue() == 0.5f);
    REQUIRE(map.getPropertySet().getDoubleValue("LootChance", 0) == 0.5);
    REQUIRE(map.getPropertySet().getFloatValue("LootChance", 0.0f) == 0.5f);

    REQUIRE(map.getPropertySet().getProperty("Name")->getName() == "Name");
    REQUIRE(map.getPropertySet().getProperty("Name")->getValue() == "Test Map");
    REQUIRE(map.getPropertySet().getProperty("Name")->getType() == PropertyType::String);

    //  Layer opacity and visibility
    REQUIRE(map.getTileLayer(0).getOpacity() == 1);
    REQUIRE(map.getTileLayer(0).getVisible() == true);
    REQUIRE(map.getTileLayer(1).getOpacity() == 1);
    REQUIRE(map.getTileLayer(1).getVisible() == true);
    REQUIRE(map.getObjectGroup(0).getOpacity() == 1);
    REQUIRE(map.getObjectGroup(0).getVisible() == true);
    REQUIRE(map.getImageLayer(0).getOpacity() == 0.5);
    REQUIRE(map.getImageLayer(0).getVisible() == false);

    //  Tilesets
    REQUIRE(map.getTilesetCount() == 2);

    //  GIDs start at 1. GID 0 is an empty tile.
    REQUIRE(map.getTilesetByGid(0) == nullptr);
    REQUIRE(map.getTilesetByGid(1) == &map.getTileset(0));
    REQUIRE(map.getTilesetByGid(280) == &map.getTileset(0));
    REQUIRE(map.getTilesetByGid(281) == &map.getTileset(1));
    REQUIRE(map.getTilesetByGid(560) == &map.getTileset(1));
    REQUIRE(map.getTilesetByGid(561) == nullptr);

    //  Embedded tileset
    REQUIRE(map.getTileset(0).getName() == "embedded_tileset");
    REQUIRE(map.getTileset(0).getTileWidth() == 16);
    REQUIRE(map.getTileset(0).getTileHeight() == 16);
    REQUIRE(map.getTileset(0).getTileCount() == 280);
    REQUIRE(map.getTileset(0).getImage().getWidth() == 160);
    REQUIRE(map.getTileset(0).getImage().getHeight() == 448);
    REQUIRE(map.getTileset(0).getImage().getSource() == "tileset.png");

    REQUIRE(map.getTileset(0).getPropertySet().getProperty("Comment")->getName() == "Comment");
    REQUIRE(map.getTileset(0).getPropertySet().getProperty("Comment")->getValue() == "Imbedded tileset.");
    REQUIRE(map.getTileset(0).getPropertySet().getProperty("Comment")->getType() == PropertyType::String);

    REQUIRE(map.getTileset(0).getTile(0)->getId() == 0);
    REQUIRE(map.getTileset(0).getTile(0)->getPropertySet().getProperty("Collision")->getBoolValue() == true);

    REQUIRE(map.getTileset(0).getTile(57)->getId() == 57);
    REQUIRE(map.getTileset(0).getTile(57)->getPropertySet().getProperty("Collision")->getBoolValue() == true);

    //  External tileset TSX
    REQUIRE(map.getTileset(1).getName() == "external_tileset");
    REQUIRE(map.getTileset(1).getTileWidth() == 16);
    REQUIRE(map.getTileset(1).getTileHeight() == 16);
    REQUIRE(map.getTileset(1).getTileCount() == 280);
    REQUIRE(map.getTileset(1).getImage().getWidth() == 160);
    REQUIRE(map.getTileset(1).getImage().getHeight() == 448);
    REQUIRE(map.getTileset(1).getImage().getSource() == "tileset.png");

    REQUIRE(map.getTileLayerCount() == 2);

    //  Tile layer tiles
    REQUIRE(map.getTileLayer(0).getTile(128)->getGid() == 58);
    REQUIRE(map.getTileLayer(0).getTile(8, 6)->getGid() == 58);

    //  Tile layer properties
    REQUIRE(map.getTileLayer(0).getPropertySet().getProperty("Tile Layer Property")->getName() == "Tile Layer Property");
    REQUIRE(map.getTileLayer(0).getPropertySet().getProperty("Tile Layer Property")->getValue() == "99");
    REQUIRE(map.getTileLayer(0).getPropertySet().getProperty("Tile Layer Property")->getType() == PropertyType::Int);
    REQUIRE(map.getTileLayer(0).getPropertySet().getProperty("Tile Layer Property")->getIntValue() == 99);
    REQUIRE(map.getTileLayer(0).getPropertySet().getProperty("Tile Layer Property")->getDoubleValue() == 99);
    REQUIRE(map.getTileLayer(0).getPropertySet().getProperty("Tile Layer Property")->getFloatValue() == 99.0f);

    //  Flip and rotate tiles
    REQUIRE(map.getTileLayer(1).getTile(1, 12)->getGid() == 257);
    REQUIRE(map.getTileLayer(1).getTile(2, 12)->getGid() == 257);
    REQUIRE(map.getTileLayer(1).getTile(3, 12)->getGid() == 257);
    REQUIRE(map.getTileLayer(1).getTile(4, 12)->getGid() == 257);

    REQUIRE(map.getTileLayer(1).getTile(1, 12)->getRawGid() == 257);
    REQUIRE(map.getTileLayer(1).getTile(2, 12)->getRawGid() == 2684354817);
    REQUIRE(map.getTileLayer(1).getTile(3, 12)->getRawGid() == 3221225729);
    REQUIRE(map.getTileLayer(1).getTile(4, 12)->getRawGid() == 1610612993);

    REQUIRE(map.getTileLayer(1).getTile(1, 12)->getFlipHorizontally() == false);
    REQUIRE(map.getTileLayer(1).getTile(1, 12)->getFlipVertically() == false);
    REQUIRE(map.getTileLayer(1).getTile(1, 12)->getFlipDiagonally() == false);

    REQUIRE(map.getTileLayer(1).getTile(2, 12)->getFlipHorizontally() == true);
    REQUIRE(map.getTileLayer(1).getTile(2, 12)->getFlipVertically() == false);
    REQUIRE(map.getTileLayer(1).getTile(2, 12)->getFlipDiagonally() == true);

    REQUIRE(map.getTileLayer(1).getTile(3, 12)->getFlipHorizontally() == true);
    REQUIRE(map.getTileLayer(1).getTile(3, 12)->getFlipVertically() == true);
    REQUIRE(map.getTileLayer(1).getTile(3, 12)->getFlipDiagonally() == false);

    REQUIRE(map.getTileLayer(1).getTile(4, 12)->getFlipHorizontally() == false);
    REQUIRE(map.getTileLayer(1).getTile(4, 12)->getFlipVertically() == true);
    REQUIRE(map.getTileLayer(1).getTile(4, 12)->getFlipDiagonally() == true);

    //  Object groups
    REQUIRE(map.getObjectGroupCount() == 1);

    //  Object group properties
    REQUIRE(map.getObjectGroup(0).getPropertySet().getProperty("Object Layer Property")->getName() == "Object Layer Property");
    REQUIRE(map.getObjectGroup(0).getPropertySet().getProperty("Object Layer Property")->getValue() == "true");
    REQUIRE(map.getObjectGroup(0).getPropertySet().getProperty("Object Layer Property")->getType() == PropertyType::Bool);
    REQUIRE(map.getObjectGroup(0).getPropertySet().getProperty("Object Layer Property")->getBoolValue() == true);

    //  Tile object
    REQUIRE(map.getObjectGroup(0).getObject(0)->getId() == 1);
    REQUIRE(map.getObjectGroup(0).getObject(0)->getName() == "Slime");
    REQUIRE(map.getObjectGroup(0).getObject(0)->getType() == "Monster");
    REQUIRE(map.getObjectGroup(0).getObject(0)->getObjectType() == ObjectType::Tile);
    REQUIRE(map.getObjectGroup(0).getObject(0)->getTile() != nullptr);
    REQUIRE(map.getObjectGroup(0).getObject(0)->getTile()->getGid() == 221);
    REQUIRE(map.getObjectGroup(0).getObject(0)->getX() == 72.5);
    REQUIRE(map.getObjectGroup(0).getObject(0)->getY() == 55.5);
    REQUIRE(map.getObjectGroup(0).getObject(0)->getWidth() == 16);
    REQUIRE(map.getObjectGroup(0).getObject(0)->getHeight() == 16);
    REQUIRE(map.getObjectGroup(0).getObject(0)->getPropertySet().getProperty("Speed") != nullptr);

    //  Polyline object
    REQUIRE(map.getObjectGroup(0).getObject(2)->getId() == 6);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getName() == "SlimePath");
    REQUIRE(map.getObjectGroup(0).getObject(2)->getType() == "Path");
    REQUIRE(map.getObjectGroup(0).getObject(2)->getObjectType() == ObjectType::Polyline);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getTile() == nullptr);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getX() == 80.5);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getY() == 51);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getPointCount() == 8);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getPoints()[0].X == 0);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getPoints()[0].Y == 0);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getPoints()[1].X == 12);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getPoints()[1].Y == 64.5);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getPoints()[2].X == 39);
    REQUIRE(map.getObjectGroup(0).getObject(2)->getPoints()[2].Y == 83.5);

    //  Polygon object
    REQUIRE(map.getObjectGroup(0).getObject(3)->getId() == 7);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getName() == "Dig Area");
    REQUIRE(map.getObjectGroup(0).getObject(3)->getType() == "");
    REQUIRE(map.getObjectGroup(0).getObject(3)->getObjectType() == ObjectType::Polygon);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getTile() == nullptr);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getX() == 225.5);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getY() == 169.5);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getPointCount() == 4);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getPoints()[0].X == 0);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getPoints()[0].Y == 0);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getPoints()[1].X == -38);
    REQUIRE(map.getObjectGroup(0).getObject(3)->getPoints()[1].Y == 57.5);

    //  Image layers
    REQUIRE(map.getImageLayerCount() == 1);

    REQUIRE(map.getImageLayer(0).getImage().getWidth() == 160);
    REQUIRE(map.getImageLayer(0).getImage().getHeight() == 448);
    REQUIRE(map.getImageLayer(0).getImage().getSource() == "tileset.png");

    //  TMX order
    REQUIRE(map.getTileLayer(0).getTmxOrder() == 0);
    REQUIRE(map.getTileLayer(1).getTmxOrder() == 1);
    REQUIRE(map.getObjectGroup(0).getTmxOrder() == 2);
    REQUIRE(map.getImageLayer(0).getTmxOrder() == 3);

    REQUIRE(map.getLayersInTmxOrder()[0]->getTmxOrder() == 0);
    REQUIRE(map.getLayersInTmxOrder()[1]->getTmxOrder() == 1);
    REQUIRE(map.getLayersInTmxOrder()[2]->getTmxOrder() == 2);
    REQUIRE(map.getLayersInTmxOrder()[3]->getTmxOrder() == 3);

    REQUIRE(map.getLayersInTmxOrder()[0] == &map.getTileLayer(0));
    REQUIRE(map.getLayersInTmxOrder()[1] == &map.getTileLayer(1));
    REQUIRE(map.getLayersInTmxOrder()[2] == &map.getObjectGroup(0));
    REQUIRE(map.getLayersInTmxOrder()[3] == &map.getImageLayer(0));

    REQUIRE(map.getLayersInTmxOrder()[0]->getLayerType() == LayerType::Tile);
    REQUIRE(map.getLayersInTmxOrder()[1]->getLayerType() == LayerType::Tile);
    REQUIRE(map.getLayersInTmxOrder()[2]->getLayerType() == LayerType::Object);
    REQUIRE(map.getLayersInTmxOrder()[3]->getLayerType() == LayerType::Image);

    //  Tile animations
    const Animation& animation = map.getTileset(0).getTile(250)->getAnimation();
    REQUIRE(animation.getFrameCount() == 9);
    REQUIRE(animation.getFrame(0).getDuration() == 100);
    REQUIRE(animation.getFrame(0).getTileId() == 250);
    REQUIRE(animation.getFrame(1).getDuration() == 100);
    REQUIRE(animation.getFrame(1).getTileId() == 251);

    //  Tile collision object group
    const TilesetTile* collisionTile = map.getTileset(0).getTile(216);
    REQUIRE(collisionTile->getObjectGroup().getObjectCount() == 1);

    //  Tile collision shapes
    const Object* collisionShape = collisionTile->getObjectGroup().getObject(0);
    REQUIRE(collisionShape != nullptr);

    //  Iterate over properties
    for (const auto property : map.getPropertySet().getProperties())
    {
        const std::string propertyName = property->getName();

        bool match =
            propertyName =="AllowSave" ||
            propertyName == "Difficulty" ||
            propertyName == "LootChance" ||
            propertyName == "Name";

        REQUIRE(match == true);
    }


    //  Iterate over tilesets
    for (const auto& tileset : map.getTilesets())
    {
        const std::string tilesetName = tileset.getName();

        bool match =
            tilesetName =="embedded_tileset" ||
            tilesetName == "external_tileset";

        REQUIRE(match == true);

        int tileCount = 0;
        for (const auto& tile : tileset.getTiles())
        {
            ++tileCount;
        }

        int expectedTileCount = tilesetName == "embedded_tileset" ? 4 : 0;

        REQUIRE(tileCount == expectedTileCount);
    }
}