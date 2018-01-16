#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Tileset.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    Tileset::Tileset(const int firstGid, const XMLElement* tilesetElement)
        : mFirstGid(firstGid)
    {
        LoadTileset(tilesetElement);
    }

    //  =======================================================================
    const int Tileset::GetFirstGid() const
    {
        return mFirstGid;
    }

    //  =======================================================================
    const Image& Tileset::GetImage() const
    {
        return mImage;
    }

    //  =======================================================================
    const std::string& Tileset::GetName() const
    {
        return mName;
    }

    //  =======================================================================
    const PropertySet& Tileset::GetPropertySet() const
    {
        return mProperties;
    }

    //  =======================================================================
    const TilesetTile* Tileset::GetTile(int id) const
    {
        auto t = mTiles.find(id);

        return
            t != mTiles.end() ?
            &(t->second) :
            nullptr;
    }

    //  =======================================================================
    const std::vector<TilesetTile>& Tileset::GetTiles() const
    {
        return mTiles;
    }

    //  =======================================================================
    int Tileset::GetTileHeight() const
    {
        return mTileHeight;
    }

    //  =======================================================================
    int Tileset::GetTileCount() const
    {
        return mTileCount;
    }

    //  =======================================================================
    int Tileset::GetTileWidth() const
    {
        return mTileWidth;
    }

    //  =======================================================================
    void Tileset::LoadTileset(const XMLElement* tilesetElement)
    {
        if (tilesetElement == nullptr)
        {
            throw NullArgumentException("Tileset element cannot be null.");
        }

        if (tilesetElement->Attribute("name"))
        {
            mName = tilesetElement->Attribute("name");
        }

        if (tilesetElement->QueryIntAttribute("tilewidth", &mTileWidth) != XML_NO_ERROR)
        {
            throw XmlAttributeException("tilewidth");
        }

        if (tilesetElement->QueryIntAttribute("tileheight", &mTileHeight) != XML_NO_ERROR)
        {
            throw XmlAttributeException("tileheight");
        }

        if (tilesetElement->QueryIntAttribute("tilecount", &mTileCount) != XML_NO_ERROR)
        {
            throw XmlAttributeException("tilecount");
        }

        if (tilesetElement->QueryIntAttribute("columns", &mColumns) != XML_NO_ERROR)
        {
            throw XmlAttributeException("columns");
        }

        //  Tileset level properties
        if (tilesetElement->FirstChildElement("properties"))
        {
            mProperties.LoadProperties(tilesetElement->FirstChildElement("properties"));
        }

        int tileCount = CountElements(tilesetElement, "tile");
        mTiles.reserve(tileCount);

        const XMLElement* tileElement = tilesetElement->FirstChildElement("tile");
        while (tileElement != nullptr)
        {
            int id;
            if (tileElement->QueryIntAttribute("id", &id) != XML_NO_ERROR)
            {
                throw XmlAttributeException("id");
            }

            mTiles.emplace(id, tileElement);

            tileElement = tileElement->NextSiblingElement("tile");
        }

        const XMLElement* imageElement = tilesetElement->FirstChildElement("image");
        mImage.LoadImage(imageElement);
    }
}