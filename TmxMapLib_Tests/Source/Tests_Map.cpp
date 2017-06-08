#include "TmxMapLib/Map.h"
#include "catch.hpp"

using namespace TmxMapLib;

//  ===========================================================================
TEST_CASE("TmxMap TMX filename constructor", "[map]")
{
    Map map("map01.tmx");

    REQUIRE(map.GetWidth() == 20);
    REQUIRE(map.GetHeight() == 16);
    REQUIRE(map.GetTileWidth() == 16);
    REQUIRE(map.GetTileHeight() == 16);

    //  Map properties
    REQUIRE(map.GetPropertySet().GetProperty("AllowSave")->GetName() == "AllowSave");
    REQUIRE(map.GetPropertySet().GetProperty("AllowSave")->GetType() == PropertyType::Bool);
    REQUIRE(map.GetPropertySet().GetProperty("AllowSave")->GetValue() == "true");
    REQUIRE(map.GetPropertySet().GetProperty("AllowSave")->GetBoolValue() == true);
    REQUIRE(map.GetPropertySet().GetBoolValue("AllowSave", false) == true);

    REQUIRE(map.GetPropertySet().GetProperty("Difficulty")->GetName() == "Difficulty");
    REQUIRE(map.GetPropertySet().GetProperty("Difficulty")->GetType() == PropertyType::Int);
    REQUIRE(map.GetPropertySet().GetProperty("Difficulty")->GetValue() == "2");
    REQUIRE(map.GetPropertySet().GetProperty("Difficulty")->GetIntValue() == 2);
    REQUIRE(map.GetPropertySet().GetProperty("Difficulty")->GetDoubleValue() == 2);
    REQUIRE(map.GetPropertySet().GetProperty("Difficulty")->GetFloatValue() == 2.0f);
    REQUIRE(map.GetPropertySet().GetIntValue("Difficulty", 0) == 2);
    REQUIRE(map.GetPropertySet().GetDoubleValue("Difficulty", 0) == 2.0);
    REQUIRE(map.GetPropertySet().GetFloatValue("Difficulty", 0.0f) == 2.0f);

    REQUIRE(map.GetPropertySet().GetProperty("LootChance")->GetName() == "LootChance");
    REQUIRE(map.GetPropertySet().GetProperty("LootChance")->GetType() == PropertyType::Float);
    REQUIRE(map.GetPropertySet().GetProperty("LootChance")->GetValue() == "0.5");
    REQUIRE(map.GetPropertySet().GetProperty("LootChance")->GetDoubleValue() == 0.5);
    REQUIRE(map.GetPropertySet().GetProperty("LootChance")->GetFloatValue() == 0.5f);
    REQUIRE(map.GetPropertySet().GetDoubleValue("LootChance", 0) == 0.5);
    REQUIRE(map.GetPropertySet().GetFloatValue("LootChance", 0.0f) == 0.5f);

    REQUIRE(map.GetPropertySet().GetProperty("Name")->GetName() == "Name");
    REQUIRE(map.GetPropertySet().GetProperty("Name")->GetValue() == "Test Map");
    REQUIRE(map.GetPropertySet().GetProperty("Name")->GetType() == PropertyType::String);

    //  Layer opacity and visibility
    REQUIRE(map.GetTileLayer(0).GetOpacity() == 1);
    REQUIRE(map.GetTileLayer(0).GetVisible() == true);
    REQUIRE(map.GetTileLayer(1).GetOpacity() == 1);
    REQUIRE(map.GetTileLayer(1).GetVisible() == true);
    REQUIRE(map.GetObjectGroup(0).GetOpacity() == 1);
    REQUIRE(map.GetObjectGroup(0).GetVisible() == true);
    REQUIRE(map.GetImageLayer(0).GetOpacity() == 0.5);
    REQUIRE(map.GetImageLayer(0).GetVisible() == false);

    //  Tilesets
    REQUIRE(map.GetTilesetCount() == 2);

    //  GIDs start at 1. GID 0 is an empty tile.
    REQUIRE(map.GetTilesetByGid(0) == nullptr);
    REQUIRE(map.GetTilesetByGid(1) == &map.GetTileset(0));
    REQUIRE(map.GetTilesetByGid(280) == &map.GetTileset(0));
    REQUIRE(map.GetTilesetByGid(281) == &map.GetTileset(1));
    REQUIRE(map.GetTilesetByGid(560) == &map.GetTileset(1));
    REQUIRE(map.GetTilesetByGid(561) == nullptr);

    //  Embedded tileset
    REQUIRE(map.GetTileset(0).GetName() == "embedded_tileset");
    REQUIRE(map.GetTileset(0).GetTileWidth() == 16);
    REQUIRE(map.GetTileset(0).GetTileHeight() == 16);
    REQUIRE(map.GetTileset(0).GetTileCount() == 280);
    REQUIRE(map.GetTileset(0).GetImage().GetWidth() == 160);
    REQUIRE(map.GetTileset(0).GetImage().GetHeight() == 448);
    REQUIRE(map.GetTileset(0).GetImage().GetSource() == "tileset.png");

    REQUIRE(map.GetTileset(0).GetPropertySet().GetProperty("Comment")->GetName() == "Comment");
    REQUIRE(map.GetTileset(0).GetPropertySet().GetProperty("Comment")->GetValue() == "Imbedded tileset.");
    REQUIRE(map.GetTileset(0).GetPropertySet().GetProperty("Comment")->GetType() == PropertyType::String);

    REQUIRE(map.GetTileset(0).GetTile(0)->GetId() == 0);
    REQUIRE(map.GetTileset(0).GetTile(0)->GetPropertySet().GetProperty("Collision")->GetBoolValue() == true);

    REQUIRE(map.GetTileset(0).GetTile(57)->GetId() == 57);
    REQUIRE(map.GetTileset(0).GetTile(57)->GetPropertySet().GetProperty("Collision")->GetBoolValue() == true);

    //  External tileset TSX
    REQUIRE(map.GetTileset(1).GetName() == "external_tileset");
    REQUIRE(map.GetTileset(1).GetTileWidth() == 16);
    REQUIRE(map.GetTileset(1).GetTileHeight() == 16);
    REQUIRE(map.GetTileset(1).GetTileCount() == 280);
    REQUIRE(map.GetTileset(1).GetImage().GetWidth() == 160);
    REQUIRE(map.GetTileset(1).GetImage().GetHeight() == 448);
    REQUIRE(map.GetTileset(1).GetImage().GetSource() == "tileset.png");

    REQUIRE(map.GetTileLayerCount() == 2);

    //  Tile layer tiles
    REQUIRE(map.GetTileLayer(0).GetTile(128)->GetGid() == 58);
    REQUIRE(map.GetTileLayer(0).GetTile(8, 6)->GetGid() == 58);

    //  Tile layer properties
    REQUIRE(map.GetTileLayer(0).GetPropertySet().GetProperty("Tile Layer Property")->GetName() == "Tile Layer Property");
    REQUIRE(map.GetTileLayer(0).GetPropertySet().GetProperty("Tile Layer Property")->GetValue() == "99");
    REQUIRE(map.GetTileLayer(0).GetPropertySet().GetProperty("Tile Layer Property")->GetType() == PropertyType::Int);
    REQUIRE(map.GetTileLayer(0).GetPropertySet().GetProperty("Tile Layer Property")->GetIntValue() == 99);
    REQUIRE(map.GetTileLayer(0).GetPropertySet().GetProperty("Tile Layer Property")->GetDoubleValue() == 99);
    REQUIRE(map.GetTileLayer(0).GetPropertySet().GetProperty("Tile Layer Property")->GetFloatValue() == 99.0f);

    //  Flip and rotate tiles
    REQUIRE(map.GetTileLayer(1).GetTile(1, 12)->GetGid() == 257);
    REQUIRE(map.GetTileLayer(1).GetTile(2, 12)->GetGid() == 257);
    REQUIRE(map.GetTileLayer(1).GetTile(3, 12)->GetGid() == 257);
    REQUIRE(map.GetTileLayer(1).GetTile(4, 12)->GetGid() == 257);

    REQUIRE(map.GetTileLayer(1).GetTile(1, 12)->GetRawGid() == 257);
    REQUIRE(map.GetTileLayer(1).GetTile(2, 12)->GetRawGid() == 2684354817);
    REQUIRE(map.GetTileLayer(1).GetTile(3, 12)->GetRawGid() == 3221225729);
    REQUIRE(map.GetTileLayer(1).GetTile(4, 12)->GetRawGid() == 1610612993);

    REQUIRE(map.GetTileLayer(1).GetTile(1, 12)->GetFlipHorizontally() == false);
    REQUIRE(map.GetTileLayer(1).GetTile(1, 12)->GetFlipVertically() == false);
    REQUIRE(map.GetTileLayer(1).GetTile(1, 12)->GetFlipDiagonally() == false);

    REQUIRE(map.GetTileLayer(1).GetTile(2, 12)->GetFlipHorizontally() == true);
    REQUIRE(map.GetTileLayer(1).GetTile(2, 12)->GetFlipVertically() == false);
    REQUIRE(map.GetTileLayer(1).GetTile(2, 12)->GetFlipDiagonally() == true);

    REQUIRE(map.GetTileLayer(1).GetTile(3, 12)->GetFlipHorizontally() == true);
    REQUIRE(map.GetTileLayer(1).GetTile(3, 12)->GetFlipVertically() == true);
    REQUIRE(map.GetTileLayer(1).GetTile(3, 12)->GetFlipDiagonally() == false);

    REQUIRE(map.GetTileLayer(1).GetTile(4, 12)->GetFlipHorizontally() == false);
    REQUIRE(map.GetTileLayer(1).GetTile(4, 12)->GetFlipVertically() == true);
    REQUIRE(map.GetTileLayer(1).GetTile(4, 12)->GetFlipDiagonally() == true);

    //  Object groups
    REQUIRE(map.GetObjectGroupCount() == 1);

    //  Object group properties
    REQUIRE(map.GetObjectGroup(0).GetPropertySet().GetProperty("Object Layer Property")->GetName() == "Object Layer Property");
    REQUIRE(map.GetObjectGroup(0).GetPropertySet().GetProperty("Object Layer Property")->GetValue() == "true");
    REQUIRE(map.GetObjectGroup(0).GetPropertySet().GetProperty("Object Layer Property")->GetType() == PropertyType::Bool);
    REQUIRE(map.GetObjectGroup(0).GetPropertySet().GetProperty("Object Layer Property")->GetBoolValue() == true);

    //  Tile object
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetId() == 1);
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetName() == "Slime");
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetType() == "Monster");
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetObjectType() == ObjectType::Tile);
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetTile() != nullptr);
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetTile()->GetGid() == 221);
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetX() == 72.5);
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetY() == 55.5);
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetWidth() == 16);
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetHeight() == 16);
    REQUIRE(map.GetObjectGroup(0).GetObject(0)->GetPropertySet().GetProperty("Speed") != nullptr);

    //  Polyline object
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetId() == 6);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetName() == "SlimePath");
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetType() == "Path");
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetObjectType() == ObjectType::Polyline);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetTile() == nullptr);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetX() == 80.5);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetY() == 51);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetPointCount() == 8);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetPoints()[0].X == 0);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetPoints()[0].Y == 0);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetPoints()[1].X == 12);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetPoints()[1].Y == 64.5);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetPoints()[2].X == 39);
    REQUIRE(map.GetObjectGroup(0).GetObject(2)->GetPoints()[2].Y == 83.5);

    //  Polygon object
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetId() == 7);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetName() == "Dig Area");
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetType() == "");
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetObjectType() == ObjectType::Polygon);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetTile() == nullptr);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetX() == 225.5);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetY() == 169.5);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetPointCount() == 4);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetPoints()[0].X == 0);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetPoints()[0].Y == 0);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetPoints()[1].X == -38);
    REQUIRE(map.GetObjectGroup(0).GetObject(3)->GetPoints()[1].Y == 57.5);

    //  Image layers
    REQUIRE(map.GetImageLayerCount() == 1);

    REQUIRE(map.GetImageLayer(0).GetImage().GetWidth() == 160);
    REQUIRE(map.GetImageLayer(0).GetImage().GetHeight() == 448);
    REQUIRE(map.GetImageLayer(0).GetImage().GetSource() == "tileset.png");

    //  TMX order
    REQUIRE(map.GetTileLayer(0).GetTmxOrder() == 0);
    REQUIRE(map.GetTileLayer(1).GetTmxOrder() == 1);
    REQUIRE(map.GetObjectGroup(0).GetTmxOrder() == 2);
    REQUIRE(map.GetImageLayer(0).GetTmxOrder() == 3);

    REQUIRE(map.GetLayersInTmxOrder()[0]->GetTmxOrder() == 0);
    REQUIRE(map.GetLayersInTmxOrder()[1]->GetTmxOrder() == 1);
    REQUIRE(map.GetLayersInTmxOrder()[2]->GetTmxOrder() == 2);
    REQUIRE(map.GetLayersInTmxOrder()[3]->GetTmxOrder() == 3);

    REQUIRE(map.GetLayersInTmxOrder()[0] == &map.GetTileLayer(0));
    REQUIRE(map.GetLayersInTmxOrder()[1] == &map.GetTileLayer(1));
    REQUIRE(map.GetLayersInTmxOrder()[2] == &map.GetObjectGroup(0));
    REQUIRE(map.GetLayersInTmxOrder()[3] == &map.GetImageLayer(0));

    REQUIRE(map.GetLayersInTmxOrder()[0]->GetLayerType() == LayerType::Tile);
    REQUIRE(map.GetLayersInTmxOrder()[1]->GetLayerType() == LayerType::Tile);
    REQUIRE(map.GetLayersInTmxOrder()[2]->GetLayerType() == LayerType::Object);
    REQUIRE(map.GetLayersInTmxOrder()[3]->GetLayerType() == LayerType::Image);

    //  Tile animations
    const Animation& animation = map.GetTileset(0).GetTile(250)->GetAnimation();
    REQUIRE(animation.GetFrameCount() == 9);
    REQUIRE(animation.GetFrame(0).GetDuration() == 100);
    REQUIRE(animation.GetFrame(0).GetTileId() == 250);
    REQUIRE(animation.GetFrame(1).GetDuration() == 100);
    REQUIRE(animation.GetFrame(1).GetTileId() == 251);

    //  Tile collision object group
    const TilesetTile* collisionTile = map.GetTileset(0).GetTile(216);
    REQUIRE(collisionTile->GetObjectGroup().GetObjectCount() == 1);

    //  Tile collision shapes
    const Object* collisionShape = collisionTile->GetObjectGroup().GetObject(0);
    REQUIRE(collisionShape != nullptr);

}