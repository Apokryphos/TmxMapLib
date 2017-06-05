#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Frame.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
    //  =======================================================================
    Frame::Frame(const tinyxml2::XMLElement* frameElement)
    {
        LoadFrame(frameElement);
    }

    //  =======================================================================
    int Frame::GetDuration() const
    {
        return mDuration;
    }

    //  =======================================================================
    int Frame::GetTileId() const
    {
        return mTileId;
    }

    //  =======================================================================
    void Frame::LoadFrame(const tinyxml2::XMLElement* frameElement)
    {
        if (frameElement == nullptr)
        {
            throw NullArgumentException("frameElement");
        }

        if (frameElement->QueryIntAttribute("tileid", &mTileId) != XML_NO_ERROR)
        {
            throw XmlAttributeException("tileid");
        }

        if (frameElement->QueryIntAttribute("duration", &mDuration) != XML_NO_ERROR)
        {
            throw XmlAttributeException("duration");
        }
    }
}