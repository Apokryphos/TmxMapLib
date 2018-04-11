#include "TmxMapLib/Exceptions.h"
#include "TmxMapLib/Frame.h"
#include <tinyxml2.h>

using namespace tinyxml2;

namespace TmxMapLib
{
//  ===========================================================================
Frame::Frame(const tinyxml2::XMLElement* frameElement) {
    this->loadFrame(frameElement);
}

//  ===========================================================================
int Frame::getDuration() const {
    return mDuration;
}

//  ===========================================================================
int Frame::getTileId() const {
    return mTileId;
}

//  ===========================================================================
void Frame::loadFrame(const tinyxml2::XMLElement* frameElement) {
    if (frameElement == nullptr) {
        throw NullArgumentException("frameElement");
    }

    if (frameElement->QueryIntAttribute("tileid", &mTileId) != XML_SUCCESS) {
        throw XmlAttributeException("tileid");
    }

    if (frameElement->QueryIntAttribute("duration", &mDuration) != XML_SUCCESS) {
        throw XmlAttributeException("duration");
    }
}
}