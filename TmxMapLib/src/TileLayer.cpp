#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/TileLayer.h"
#include <tinyxml2.h>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
void loadTileCsv(const char* csv, std::vector<unsigned int>& rawGids) {
    assert(csv != nullptr);

    unsigned int rawGid;
    std::stringstream stream(csv);

    while (stream >> rawGid) {
        rawGids.push_back(rawGid);

        if (stream.peek() == ',') {
            stream.ignore();
        }
    }
}

//  ===========================================================================
TileLayer::TileLayer(
    const Map* map,
    const int tmxOrder,
    const XMLElement* layerElement)
    : LayerBase(LayerType::Tile, map, tmxOrder, layerElement) {
    this->loadTileLayer(layerElement);
}

//  ===========================================================================
int TileLayer::getHeight() const {
    return mHeight;
}

//  ===========================================================================
const Tile* TileLayer::getTile(const size_t index) const {
    if (index < mTiles.size()) {
        return &mTiles[index];
    } else {
        return nullptr;
    }
}

//  ===========================================================================
const Tile* TileLayer::getTile(const int x, const int y) const {
    return this->getTile(y * mWidth + x);
}

//  ===========================================================================
int TileLayer::getWidth() const {
    return mWidth;
}

//  ===========================================================================
const std::vector<Tile>& TileLayer::getTiles() const {
    return mTiles;
}

//  ===========================================================================
void TileLayer::loadTileLayer(const XMLElement* layerElement)
{
    if (layerElement == nullptr) {
        throw NullArgumentException("layerElement");
    }

    if (layerElement->QueryIntAttribute("width", &mWidth) != XML_SUCCESS) {
        throw XmlAttributeException("width");
    }

    if (layerElement->QueryIntAttribute("height", &mHeight) != XML_SUCCESS) {
        throw XmlAttributeException("height");
    }

    this->loadTiles(layerElement);
}

//  ===========================================================================
void TileLayer::loadTiles(const XMLElement* layerElement)
{
    if (layerElement == nullptr) {
        throw NullArgumentException("layerElement");
    }

    const XMLElement* dataElement = layerElement->FirstChildElement("data");
    if (dataElement == nullptr) {
        throw XmlElementException("data");
    }

    size_t tileCount = mWidth * mHeight;

    //  Store raw tile GIDs in vector
    std::vector<unsigned int> rawGids;
    rawGids.reserve(tileCount);

    if (dataElement->Attribute("encoding", "csv")) {
        //  Load tile GIDs from the data element's text
        loadTileCsv(dataElement->GetText(), rawGids);
    } else {
        const char* encoding = dataElement->Attribute("encoding");
        if (encoding == nullptr || strlen(encoding) == 0) {
            //  Encoding attribute is missing or empty
            std::cerr << "Missing tile data." << std::endl;
        } else {
            //  Encoding type is not implemented
            std::cerr << "Unsupported tile data encoding: " << encoding << std::endl;
        }
        throw std::runtime_error("Failed to read map tile data.");
    }

    //  Tile GID count should match layer tile count
    if (rawGids.size() != tileCount) {
        std::cerr << rawGids.size() << " of " << tileCount << " tile GIDs read." << std::endl;
        throw std::runtime_error("Failed to read map tile GIDs.");
    }

    //  Create tiles
    mTiles.reserve(tileCount);
    for (int y = 0; y < mHeight; ++y) {
        for (int x = 0; x < mWidth; ++x) {
            mTiles.emplace_back(rawGids[y * mWidth + x], x, y);
        }
    }
}
}