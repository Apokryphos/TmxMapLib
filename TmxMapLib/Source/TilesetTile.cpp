#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/TilesetTile.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
TilesetTile::TilesetTile(const XMLElement* tilesetTileElement) {
    this->loadTilesetTile(tilesetTileElement);
}

//  ===========================================================================
const Animation& TilesetTile::getAnimation() const {
    return mAnimation;
}

//  ===========================================================================
int TilesetTile::getId() const {
    return mId;
}

//  ===========================================================================
const ObjectGroup& TilesetTile::getObjectGroup() const {
    return mObjectGroup;
}

//  ===========================================================================
const PropertySet& TilesetTile::getPropertySet() const {
    return mProperties;
}

//  ===========================================================================
void TilesetTile::loadTilesetTile(const XMLElement* tilesetTileElement) {
    if (tilesetTileElement == nullptr) {
        throw NullArgumentException("Tileset element cannot be null.");
    }

    if (tilesetTileElement->QueryIntAttribute("id", &mId) != XML_SUCCESS) {
        throw XmlAttributeException("id");
    }

    //  Tileset tile level properties
    if (tilesetTileElement->FirstChildElement("properties")) {
        mProperties.loadProperties(
            tilesetTileElement->FirstChildElement("properties"));
    }

    //  Animation
    const XMLElement* animElement =
        tilesetTileElement->FirstChildElement("animation");
    if (animElement != nullptr) {
        mAnimation.loadAnimation(animElement);
    }

    //  Object group (collision shapes)
    const XMLElement* groupElement =
        tilesetTileElement->FirstChildElement("objectgroup");
    if (groupElement != nullptr) {
        mObjectGroup.loadObjectGroup(groupElement);
    }
}
}