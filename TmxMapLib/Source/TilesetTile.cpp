#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/TilesetTile.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    TilesetTile::TilesetTile(const XMLElement* tilesetTileElement)
    {
        LoadTilesetTile(tilesetTileElement);
    }

    //  =======================================================================
    const Animation& TilesetTile::GetAnimation() const
    {
        return mAnimation;
    }

    //  =======================================================================
    int TilesetTile::GetId() const
    {
        return mId;
    }

    //  =======================================================================
    const ObjectGroup& TilesetTile::GetObjectGroup() const
    {
        return mObjectGroup;
    }

    //  =======================================================================
    const PropertySet& TilesetTile::GetPropertySet() const
    {
        return mProperties;
    }

    //  =======================================================================
    void TilesetTile::LoadTilesetTile(const XMLElement* tilesetTileElement)
    {
        if (tilesetTileElement == nullptr)
        {
            throw NullArgumentException("Tileset element cannot be null.");
        }

        if (tilesetTileElement->QueryIntAttribute("id", &mId) != XML_NO_ERROR)
        {
            throw XmlAttributeException("id");
        }

        //  Tileset tile level properties
        if (tilesetTileElement->FirstChildElement("properties"))
        {
            mProperties.LoadProperties(tilesetTileElement->FirstChildElement("properties"));
        }

        //  Animation
        const XMLElement* animElement = tilesetTileElement->FirstChildElement("animation");
        if (animElement != nullptr)
        {
            mAnimation.LoadAnimation(animElement);
        }

        //  Object group (collision shapes)
        const XMLElement* groupElement = tilesetTileElement->FirstChildElement("objectgroup");
        if (groupElement != nullptr)
        {
            mObjectGroup.LoadObjectGroup(groupElement);
        }
    }
}