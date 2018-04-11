#pragma once

#include "Animation.h"
#include "PropertySet.h"
#include "ObjectGroup.h"

namespace tinyxml2
{
class XMLElement;
}

namespace TmxMapLib
{
class TilesetTile
{
private:
    int mId;
    PropertySet mProperties;
    Animation mAnimation;
    ObjectGroup mObjectGroup;

    void loadTilesetTile(const tinyxml2::XMLElement* tilesetTileElement);

public:

    /*
    *   Constructs a TilesetTile from the specified XML element.
    */
    TilesetTile(const tinyxml2::XMLElement* tilesetTileElement);

    /*
    *   Returns the animation for this tile.
    */
    const Animation& getAnimation() const;

    /*
    *   Returns the tileset ID of this tile.
    */
    int getId() const;

    /*
    *   Returns the object group for this tile.
    */
    const ObjectGroup& getObjectGroup() const;

    /*
    *   Returns the set of properties for this tileset.
    */
    const PropertySet& getPropertySet() const;
};
}
