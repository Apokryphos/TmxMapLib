#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Tileset.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
Tileset::Tileset(const int firstGid, const XMLElement* tilesetElement)
    : mFirstGid(firstGid) {
    this->loadTileset(tilesetElement);
}

//  ===========================================================================
int Tileset::getFirstGid() const {
    return mFirstGid;
}

//  ===========================================================================
const Image& Tileset::getImage() const {
    return mImage;
}

//  ===========================================================================
const std::string& Tileset::getName() const {
    return mName;
}

//  ===========================================================================
const PropertySet& Tileset::getPropertySet() const {
    return mProperties;
}

//  ===========================================================================
const TilesetTile* Tileset::getTile(int id) const {
    auto t = mTiles.find(id);

    return
        t != mTiles.end() ?
        &(t->second) :
        nullptr;
}

//  ===========================================================================
const std::unordered_map<int, TilesetTile>& Tileset::getTiles() const {
    return mTiles;
}

//  ===========================================================================
int Tileset::getTileHeight() const {
    return mTileHeight;
}

//  ===========================================================================
int Tileset::getTileCount() const {
    return mTileCount;
}

//  ===========================================================================
int Tileset::getTileWidth() const {
    return mTileWidth;
}

//  ===========================================================================
void Tileset::loadTileset(const XMLElement* tilesetElement) {
    if (tilesetElement == nullptr) {
        throw NullArgumentException("Tileset element cannot be null.");
    }

    if (tilesetElement->Attribute("name")) {
        mName = tilesetElement->Attribute("name");
    }

    if (tilesetElement->QueryIntAttribute("tilewidth", &mTileWidth) != XML_SUCCESS) {
        throw XmlAttributeException("tilewidth");
    }

    if (tilesetElement->QueryIntAttribute("tileheight", &mTileHeight) != XML_SUCCESS) {
        throw XmlAttributeException("tileheight");
    }

    if (tilesetElement->QueryIntAttribute("tilecount", &mTileCount) != XML_SUCCESS) {
        throw XmlAttributeException("tilecount");
    }

    if (tilesetElement->QueryIntAttribute("columns", &mColumns) != XML_SUCCESS) {
        throw XmlAttributeException("columns");
    }

    //  Tileset level properties
    if (tilesetElement->FirstChildElement("properties")) {
        mProperties.loadProperties(tilesetElement->FirstChildElement("properties"));
    }

    int tileCount = countElements(tilesetElement, "tile");
    mTiles.reserve(tileCount);

    const XMLElement* tileElement = tilesetElement->FirstChildElement("tile");
    while (tileElement != nullptr) {
        int id;
        if (tileElement->QueryIntAttribute("id", &id) != XML_SUCCESS) {
            throw XmlAttributeException("id");
        }

        mTiles.emplace(id, tileElement);

        tileElement = tileElement->NextSiblingElement("tile");
    }

    const XMLElement* imageElement = tilesetElement->FirstChildElement("image");
    mImage.loadImage(imageElement);
}
}