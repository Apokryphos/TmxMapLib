#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Map.h"
#include "TmxMapLib/XmlUtil.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    Map::Map(const std::string& filename)
    :   mWidth(0),
        mHeight(0),
        mTileWidth(0),
        mTileHeight(0),
        mRenderOrder(RenderOrder::RightDown)
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
    int Map::GetHeight() const
    {
        return mHeight;
    }

    //  =======================================================================
    const ImageLayer& Map::GetImageLayer(const int index) const
    {
        return mImageLayers.at(index);
    }

    //  =======================================================================
    const std::vector<ImageLayer>& Map::GetImageLayers() const
    {
        return mImageLayers;
    }

    //  =======================================================================
    int Map::GetImageLayerCount() const
    {
        return mImageLayers.size();
    }

    //  =======================================================================
    int Map::GetLayerCount() const
    {
        return mTmxOrder.size();
    }

    //  =======================================================================
    const std::vector<LayerBase*>& Map::GetLayersInTmxOrder() const
    {
        return mTmxOrder;
    }

    //  =======================================================================
    const ObjectGroup& Map::GetObjectGroup(const int index) const
    {
        return mObjectGroups.at(index);
    }

    //  =======================================================================
    int Map::GetObjectGroupCount() const
    {
        return mObjectGroups.size();
    }

    //  =======================================================================
    const PropertySet& Map::GetPropertySet() const
    {
        return mProperties;
    }

    //  =======================================================================
    RenderOrder Map::GetRenderOrder() const
    {
        return mRenderOrder;
    }

    //  =======================================================================
    int Map::GetTileHeight() const
    {
        return mTileHeight;
    }

    //  =======================================================================
    const TileLayer& Map::GetTileLayer(const int index) const
    {
        return mTileLayers.at(index);
    }

    //  =======================================================================
    const std::vector<TileLayer>& Map::GetTileLayers() const
    {
        return mTileLayers;
    }

    //  =======================================================================
    int Map::GetTileLayerCount() const
    {
        return mTileLayers.size();
    }

    //  =======================================================================
    int Map::GetTileWidth() const
    {
        return mTileWidth;
    }

    //  =======================================================================
    const Tileset& Map::GetTileset(const int index) const
    {
        if (index < 0 || index >= mTilesets.size())
        {
            throw std::out_of_range("Index is out of range.");
        }

        return mTilesets[index];
    }

    //  =======================================================================
    const Tileset* Map::GetTilesetByGid(const int gid) const
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
    int Map::GetTilesetCount() const
    {
        return mTilesets.size();
    }

    //  =======================================================================
    int Map::GetWidth() const
    {
        return mWidth;
    }

    //  =======================================================================
    void Map::LoadLayers(const XMLElement* mapElement)
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
                mTileLayers.emplace_back(this, tmxOrder++, childElement);
                mTmxOrder.push_back(&mTileLayers[mTileLayers.size() - 1]);
            }
            else if (elementName == "objectgroup")
            {
                mObjectGroups.emplace_back(this, tmxOrder++, childElement);
                mTmxOrder.push_back(&mObjectGroups[mObjectGroups.size() - 1]);
            }
            else if (elementName == "imagelayer")
            {
                mImageLayers.emplace_back(this, tmxOrder++, childElement);
                mTmxOrder.push_back(&mImageLayers[mImageLayers.size() - 1]);
            }

            childElement = childElement->NextSiblingElement();
        }
    }

    //  =======================================================================
    void Map::LoadMap(const XMLElement* mapElement)
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

        if (mapElement->Attribute("renderorder"))
        {
            std::string renderOrder = mapElement->Attribute("renderorder");
            if (renderOrder == "right-down")
            {
                mRenderOrder = RenderOrder::RightDown;
            }
            else if (renderOrder == "right-up")
            {
                mRenderOrder = RenderOrder::RightUp;
            }
            else if (renderOrder == "left-down")
            {
                mRenderOrder = RenderOrder::LeftDown;
            }
            else if (renderOrder == "left-up")
            {
                mRenderOrder = RenderOrder::LeftUp;
            }
        }

        LoadTilesets(mapElement);
        LoadLayers(mapElement);
    }

    //  =======================================================================
    void Map::LoadTilesets(const XMLElement* mapElement)
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