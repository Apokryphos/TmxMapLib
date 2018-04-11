#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Map.h"
#include "TmxMapLib/XmlUtil.h"
#include <iostream>
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
static void getPath(const std::string& fullPath, std::string& path)
{
    const size_t s = fullPath.find_last_of("/\\");

    if (s == std::string::npos) {
        path = "";
    } else {
        path = fullPath.substr(0, s) + "/";
    }
}

//  ===========================================================================
Map::Map(const std::string& fullPath)
:   mWidth(0),
    mHeight(0),
    mTileWidth(0),
    mTileHeight(0),
    mRenderOrder(RenderOrder::RightDown) {
    std::string filename;

    getPath(fullPath, mPath);

    XMLDocument doc;
    if (doc.LoadFile(fullPath.c_str()) != XMLError::XML_SUCCESS) {
        doc.PrintError();
        throw XmlDocumentException(fullPath);
    }

    this->loadMap(doc.FirstChildElement("map"));
}

//  ===========================================================================
int Map::getHeight() const {
    return mHeight;
}

//  ===========================================================================
const ImageLayer& Map::getImageLayer(const int index) const {
    return mImageLayers.at(index);
}

//  ===========================================================================
const std::vector<ImageLayer>& Map::getImageLayers() const {
    return mImageLayers;
}

//  ===========================================================================
int Map::getImageLayerCount() const {
    return mImageLayers.size();
}

//  ===========================================================================
int Map::getLayerCount() const {
    return mTmxOrder.size();
}

//  ===========================================================================
const std::vector<LayerBase*>& Map::getLayersInTmxOrder() const {
    return mTmxOrder;
}

//  ===========================================================================
const ObjectGroup& Map::getObjectGroup(const int index) const {
    return mObjectGroups.at(index);
}

//  ===========================================================================
int Map::getObjectGroupCount() const {
    return mObjectGroups.size();
}

//  ===========================================================================
const std::vector<ObjectGroup>& Map::getObjectGroups() const {
    return mObjectGroups;
}

//  ===========================================================================
const PropertySet& Map::getPropertySet() const {
    return mProperties;
}

//  ===========================================================================
RenderOrder Map::getRenderOrder() const {
    return mRenderOrder;
}

//  ===========================================================================
int Map::getTileHeight() const {
    return mTileHeight;
}

//  ===========================================================================
const TileLayer& Map::getTileLayer(const int index) const {
    return mTileLayers.at(index);
}

//  ===========================================================================
const std::vector<TileLayer>& Map::getTileLayers() const {
    return mTileLayers;
}

//  ===========================================================================
int Map::getTileLayerCount() const {
    return mTileLayers.size();
}

//  ===========================================================================
int Map::getTileWidth() const {
    return mTileWidth;
}

//  ===========================================================================
const Tileset& Map::getTileset(const size_t index) const {
    if (index >= mTilesets.size()) {
        throw std::out_of_range("Index is out of range.");
    }

    return mTilesets[index];
}

//  ===========================================================================
const std::vector<Tileset>& Map::getTilesets() const {
    return mTilesets;
}

//  ===========================================================================
const Tileset* Map::getTilesetByGid(const int gid) const {
    for (size_t t = 0; t < mTilesets.size(); ++t) {
        int firstGid = mTilesets[t].getFirstGid();
        int lastGid = firstGid + mTilesets[t].getTileCount();

        if (gid >= firstGid &&
            gid < lastGid) {
            return &mTilesets[t];
        }
    }

    return nullptr;
}

//  ===========================================================================
int Map::getTilesetCount() const {
    return mTilesets.size();
}

//  ===========================================================================
int Map::getWidth() const {
    return mWidth;
}

//  ===========================================================================
void Map::loadLayers(const XMLElement* mapElement) {
    //  Reserve vectors
    int layerCount = countElements(mapElement, "layer");
    mTileLayers.reserve(layerCount);

    int groupCount = countElements(mapElement, "objectgroup");
    mObjectGroups.reserve(groupCount);

    int imageLayerCount = countElements(mapElement, "imagelayer");
    mImageLayers.reserve(imageLayerCount);

    mTmxOrder.reserve(layerCount + groupCount + imageLayerCount);

    int tmxOrder = 0;
    const XMLElement* childElement = mapElement->FirstChildElement();
    while (childElement != nullptr) {
        std::string elementName = childElement->Name();

        if (elementName == "layer") {
            mTileLayers.emplace_back(this, tmxOrder++, childElement);
            mTmxOrder.push_back(&mTileLayers[mTileLayers.size() - 1]);
        } else if (elementName == "objectgroup") {
            mObjectGroups.emplace_back(this, tmxOrder++, childElement);
            mTmxOrder.push_back(&mObjectGroups[mObjectGroups.size() - 1]);
        } else if (elementName == "imagelayer") {
            mImageLayers.emplace_back(this, tmxOrder++, childElement);
            mTmxOrder.push_back(&mImageLayers[mImageLayers.size() - 1]);
        }

        childElement = childElement->NextSiblingElement();
    }
}

//  ===========================================================================
void Map::loadMap(const XMLElement* mapElement)
{
    if (mapElement == nullptr) {
        throw NullArgumentException("mapElement");
    }

    if (mapElement->QueryIntAttribute("width", &mWidth) != XML_SUCCESS) {
        throw XmlAttributeException("width");
    }

    if (mapElement->QueryIntAttribute("height", &mHeight) != XML_SUCCESS) {
        throw XmlAttributeException("height");
    }

    if (mapElement->QueryIntAttribute("tilewidth", &mTileWidth) != XML_SUCCESS) {
        throw XmlAttributeException("tilewidth");
    }

    if (mapElement->QueryIntAttribute("tileheight", &mTileHeight) != XML_SUCCESS) {
        throw XmlAttributeException("tileheight");
    }

    if (mapElement->FirstChildElement("properties")) {
        mProperties.loadProperties(mapElement->FirstChildElement("properties"));
    }

    if (mapElement->Attribute("renderorder")) {
        std::string renderOrder = mapElement->Attribute("renderorder");
        if (renderOrder == "right-down") {
            mRenderOrder = RenderOrder::RightDown;
        } else if (renderOrder == "right-up") {
            mRenderOrder = RenderOrder::RightUp;
        } else if (renderOrder == "left-down") {
            mRenderOrder = RenderOrder::LeftDown;
        } else if (renderOrder == "left-up") {
            mRenderOrder = RenderOrder::LeftUp;
        }
    }

    this->loadTilesets(mapElement);
    this->loadLayers(mapElement);
}

//  ===========================================================================
void Map::loadTilesets(const XMLElement* mapElement)
{
    int tilesetCount = countElements(mapElement, "tileset");
    mTilesets.reserve(tilesetCount);

    const XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
    while (tilesetElement != nullptr) {
        int firstGid = 0;
        if (tilesetElement->QueryIntAttribute("firstgid", &firstGid) != XML_SUCCESS) {
            throw XmlAttributeException("firstgid");
        }

        //  External tileset TSX
        if (tilesetElement->Attribute("source")) {
            std::string source = tilesetElement->Attribute("source");

            std::string fullPath = mPath + source;

            XMLDocument doc;
            if (doc.LoadFile(fullPath.c_str()) != XMLError::XML_SUCCESS) {
                doc.PrintError();
                throw XmlDocumentException(fullPath);
            }

            XMLElement* extTilesetElement = doc.FirstChildElement("tileset");

            mTilesets.emplace_back(firstGid, extTilesetElement);
        } else {
            //  Embedded tileset
            mTilesets.emplace_back(firstGid, tilesetElement);
        }

        tilesetElement = tilesetElement->NextSiblingElement("tileset");
    }
}
}