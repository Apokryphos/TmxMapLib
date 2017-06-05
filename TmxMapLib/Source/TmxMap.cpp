#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/TmxMap.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    TmxMap::TmxMap(const std::string& filename)
    {
        XMLDocument doc;
        if (doc.LoadFile(filename.c_str()) != XMLError::XML_NO_ERROR)
        {
            doc.PrintError();
            throw XmlDocumentException(filename);
        }

        LoadMap(doc.FirstChildElement("map"));
    }

    //  =======================================================================
    int TmxMap::GetHeight() const
    {
        return mHeight;
    }

    //  =======================================================================
    const ImageLayer& TmxMap::GetImageLayer(const int index) const
    {
        return mImageLayers.at(index);
    }

    //  =======================================================================
    const std::vector<ImageLayer>& TmxMap::GetImageLayers() const
    {
        return mImageLayers;
    }

    //  =======================================================================
    int TmxMap::GetImageLayerCount() const
    {
        return mImageLayers.size();
    }

    //  =======================================================================
    const std::vector<LayerBase*>& TmxMap::GetLayersInTmxOrder() const
    {
        return mTmxOrder;
    }

    //  =======================================================================
    const ObjectGroup& TmxMap::GetObjectGroup(const int index) const
    {
        return mObjectGroups.at(index);
    }

    //  =======================================================================
    int TmxMap::GetObjectGroupCount() const
    {
        return mObjectGroups.size();
    }

    //  =======================================================================
    const PropertySet& TmxMap::GetPropertySet() const
    {
        return mProperties;
    }

    //  =======================================================================
    int TmxMap::GetTileHeight() const
    {
        return mTileHeight;
    }

    //  =======================================================================
    const TileLayer& TmxMap::GetTileLayer(const int index) const
    {
        return mTileLayers.at(index);
    }

    //  =======================================================================
    int TmxMap::GetTileLayerCount() const
    {
        return mTileLayers.size();
    }

    //  =======================================================================
    int TmxMap::GetTileWidth() const
    {
        return mTileWidth;
    }

    //  =======================================================================
    const Tileset& TmxMap::GetTileset(const int index) const
    {
        if (index < 0 || index >= mTilesets.size())
        {
            throw std::out_of_range("Index is out of range.");
        }

        return mTilesets[index];
    }

    //  =======================================================================
    const Tileset* TmxMap::GetTilesetByGid(const int gid) const
    {
        for (size_t t = 0; t < mTilesets.size(); ++t)
        {
            int firstGid = mTilesets[t].GetFirstGid();
            int lastGid = firstGid + mTilesets[t].GetTileCount();

            if (gid >= firstGid &&
                gid < lastGid)
            {
                return &mTilesets[t];
            }
        }

        return nullptr;
    }

    //  =======================================================================
    int TmxMap::GetTilesetCount() const
    {
        return mTilesets.size();
    }

    //  =======================================================================
    int TmxMap::GetWidth() const
    {
        return mWidth;
    }

    //  =======================================================================
    void TmxMap::LoadLayers(const XMLElement* mapElement)
    {
        //  Reserve vectors
        int layerCount = CountElements(mapElement, "layer");
        mTileLayers.reserve(layerCount);

        int groupCount = CountElements(mapElement, "objectgroup");
        mObjectGroups.reserve(groupCount);

        int imageLayerCount = CountElements(mapElement, "imagelayer");
        mImageLayers.reserve(imageLayerCount);

        mTmxOrder.reserve(layerCount + groupCount + imageLayerCount);

        int tmxOrder = 0;
        const XMLElement* childElement = mapElement->FirstChildElement();
        while (childElement != nullptr)
        {
            std::string elementName = childElement->Name();

            if (elementName == "layer")
            {
                mTileLayers.emplace_back(tmxOrder++, childElement);
                mTmxOrder.push_back(&mTileLayers[mTileLayers.size() - 1]);
            }
            else if (elementName == "objectgroup")
            {
                mObjectGroups.emplace_back(tmxOrder++, childElement);
                mTmxOrder.push_back(&mObjectGroups[mObjectGroups.size() - 1]);
            }
            else if (elementName == "imagelayer")
            {
                mImageLayers.emplace_back(tmxOrder++, childElement);
                mTmxOrder.push_back(&mImageLayers[mImageLayers.size() - 1]);
            }

            childElement = childElement->NextSiblingElement();
        }
    }

    //  =======================================================================
    void TmxMap::LoadMap(const XMLElement* mapElement)
    {
        if (mapElement == nullptr)
        {
            throw NullArgumentException("mapElement");
        }

        if (mapElement->QueryIntAttribute("width", &mWidth) != XML_NO_ERROR)
        {
            throw XmlAttributeException("width");
        }

        if (mapElement->QueryIntAttribute("height", &mHeight) != XML_NO_ERROR)
        {
            throw XmlAttributeException("height");
        }

        if (mapElement->QueryIntAttribute("tilewidth", &mTileWidth) != XML_NO_ERROR)
        {
            throw XmlAttributeException("tilewidth");
        }

        if (mapElement->QueryIntAttribute("tileheight", &mTileHeight) != XML_NO_ERROR)
        {
            throw XmlAttributeException("tileheight");
        }

        if (mapElement->FirstChildElement("properties"))
        {
            mProperties.LoadProperties(mapElement->FirstChildElement("properties"));
        }

        LoadTilesets(mapElement);
        LoadLayers(mapElement);
    }

    //  =======================================================================
    void TmxMap::LoadTilesets(const XMLElement* mapElement)
    {
        int tilesetCount = CountElements(mapElement, "tileset");
        mTilesets.reserve(tilesetCount);

        const XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
        while (tilesetElement != nullptr)
        {
            int firstGid = 0;
            if (tilesetElement->QueryIntAttribute("firstgid", &firstGid) != XML_NO_ERROR)
            {
                throw XmlAttributeException("firstgid");
            }

            //  External tileset TSX
            if (tilesetElement->Attribute("source"))
            {
                std::string source = tilesetElement->Attribute("source");

                XMLDocument doc;
                if (doc.LoadFile(source.c_str()) != XMLError::XML_NO_ERROR)
                {
                    doc.PrintError();
                    throw XmlDocumentException(source);
                }

                XMLElement* extTilesetElement = doc.FirstChildElement("tileset");

                mTilesets.emplace_back(firstGid, extTilesetElement);
            }
            else
            {
                //  Imbedded tileset
                mTilesets.emplace_back(firstGid, tilesetElement);
            }

            tilesetElement = tilesetElement->NextSiblingElement("tileset");
        }
    }
}